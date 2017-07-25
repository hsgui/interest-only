import gym
import numpy as np
import _pickle as pickle

H = 200 # number of hidden layer neurons

gamma = 0.99 # discount factor for reward
# every how many episodes to do a param update?
batch_size = 10

learning_rate = 1e-3
# decay factor for RMSProp leaky sum of grad^2
decay_rate = 0.99

resume = True
render = True
train = False

# model initialization
D = 80 * 80 # input dimensionality

model_path = 'trained-models/pong-pg-1.model'
if resume:
    model = pickle.load(open(model_path, 'rb'))
else:
    model = {}
    # "Xavier" initialization
    model['W1'] = np.random.randn(H, D) / np.sqrt(D)
    model['W2'] = np.random.randn(H) / np.sqrt(H)

# update buffers that add up gradients over a batch
grad_buffer = { k : np.zeros_like(v) for k, v in model.items() }

# rmsprop memory
rmsprop_cache = { k: np.zeros_like(v) for k, v in model.items() }
    
def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-x))

def preprocess(I):
    """ preprocess 210 * 160 * 3 uint8 frame into 6400 (80 * 80) 1D float vector"""
    #crop
    I = I[35:195]
    # downsample by factor of 2
    I = I[::2, ::2, 0]
    # erase background (background type 1)
    I[I == 144] = 0
    # erase background (background type 2)
    I[I == 109] = 0
    # everything else (paddles, ball) just set to 1
    I[ I != 0] = 1
    return I.astype(np.float).ravel()
    
def policy_forward(x):
    # compute hidden layer neuron activations
    # np.dot: for 2-D arrays, it's equivalent to matrix multiplication
    #  for 1-D arrays to inner product of vectors
    h = np.dot(model['W1'], x)

    # ReLU nonlinearity: threshold at 0
    h[h < 0] = 0
    logp = np.dot(model['W2'], h)

    # p is the probability of taking action 2
    # h is the hidden state
    p = sigmoid(logp)
    return p, h

def discount_rewards(r):
    """"
    take 1D float array of rewards and compute discounted reward
    """
    discounted_r = np.zeros_like(r)
    running_add = 0
    for t in reversed(range(0, r.size)):
        # reset the sum, this was a game boundary (pong specific)
        # for pong game, most of the time, the rewards are 0
        # And we will get +1 if we win or -1 otherwise
        if r[t] != 0: running_add = 0
        running_add = running_add  * gamma + r[t]
        discounted_r[t] = running_add

    return discounted_r

def policy_backward(eph, epdlogp):
    """
    backward pass. 
    eph: N * H,  is array of intermediate hidden states
    epdlogp: N * 1
    """
    # dW2: H
    dW2 = np.dot(eph.T, epdlogp).ravel()
    # dh: N * H
    dh = np.outer(epdlogp, model['W2'])
    # backpropagate relu
    dh[eph <= 0] = 0
    # dW1: H * D
    dW1 = np.dot(dh.T, epx)
    return {'W1': dW1, 'W2': dW2}
    
env_key = "Pong-v0"
env = gym.make(env_key)

observation = env.reset()
# used in computing the difference frame
prev_x = None

xs, hs, dlogps, drs = [], [], [], []

running_reward = None
episode_number = 0
reward_sum = 0

while True:
    if render: env.render()

    # preprocess the observation, set input to network to be different image
    cur_x = preprocess(observation)
    x = cur_x - prev_x if prev_x is not None else np.zeros(D)
    prev_x = cur_x

    # forward the policy network and sample an action from the returned probability
    # x is a vector of 6400 (80 * 80) elements
    # aprob is a scalar value, h is a vector of 200 (hidden units) elements
    # aprob is a probability of moving UP
    aprob, h = policy_forward(x)
        
    # roll the dice
    action = 2 if np.random.uniform() < aprob else 3

    # step the environment and get new measurements
    observation, reward, done, info = env.step(action)
    reward_sum += reward
    if done and (not train):
        episode_number += 1
        running_reward = reward_sum if running_reward is None else running_reward * 0.99 + reward_sum * 0.01
        print("reseting env. ep %d, episode reward total was %f. running mean: %f" % (episode_number, reward_sum, running_reward))

        reward_sum = 0
        observation = env.reset()
        prev_x = None

        continue

    # record various intermeidates ( needed later for backprob)
    xs.append(x) # observation
    hs.append(h) # hidden state
    y = 1 if action == 2 else 0 # a "fake label"

    # http://cs231n.github.io/neural-networks-2/#losses
    dlogps.append(y - aprob)

    # record reward (has to be done after call step() to get reward for prevous action)
    drs.append(reward)

    if done: # an episode finished
        episode_number += 1

        # stack together all inputs, hidden states, action gradients, and rewards for this episode
        # epx.shape: N * 6400
        epx = np.vstack(xs)
        # eplog.shape: N * 200
        eph = np.vstack(hs)
        # eplogp.shape: N * 1
        epdlogp = np.vstack(dlogps)
        # epr.shape: N * 1
        epr = np.vstack(drs)
        # reset array memory
        xs, hs, dlogps, drs = [], [], [], []

        # compute the discounted reward backwards through time
        discounted_epr = discount_rewards(epr)
        # standardize the rewards to be unit normal
        # it could help control the gradient estimator variance
        discounted_epr -= np.mean(discounted_epr)
        discounted_epr /= np.std(discounted_epr)

        # modulate the gradient with advantage
        epdlogp *= discounted_epr
        grad = policy_backward(eph, epdlogp)
        # accumulate grad over batch
        for k in model: grad_buffer[k] += grad[k]

        # perform rmsprop parameter update every batch_size episodes
        if episode_number % batch_size == 0:
            print("update the model...")
            for k, v in model.items():
                g = grad_buffer[k] # gradient
                rmsprop_cache[k] = decay_rate * rmsprop_cache[k] + (1 - decay_rate) * g**2
                model[k] += learning_rate * g / (np.sqrt(rmsprop_cache[k]) + 1e-5)
                # reset batch gradient buffer
                grad_buffer[k] = np.zeros_like(v)

        # boring book-keeping
        running_reward = reward_sum if running_reward is None else running_reward * 0.99 + reward_sum * 0.01
        print("reseting env. ep %d, episode reward total was %f. running mean: %f" % (episode_number, reward_sum, running_reward))
        if episode_number % 100 == 0:
            print("Save model...")
            pickle.dump(model, open(model_path, 'wb'))

        reward_sum = 0
        observation = env.reset()
        prev_x = None

    # Pong has either +1 or -1 reward exactly when game ends.
    #if reward != 0:
        #print("ep %d: game finished, reward: %f" % (episode_number, reward) + ('' if reward == -1 else ' !!!!!'))
