from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.optimizers import Adam
import random
import math
import gym
from gym.wrappers.monitoring import Monitor
from keras import backend as K
import numpy as np
import tensorflow as tf

import replay_memory as memory

DEBUG = False

EPISODES = 2000

MEMORY_CAPACITY = 100000
BATCH_SIZE = 64

# the exploration rate
EPSILON_MAX = 1.00
EPSILON_MIN = 0.01

# decay speed of epsilon - the exploration rate
LAMBDA = 0.001

# the default discount rate
GAMMA = 0.99
LEARNING_RATE = 0.00025

UPDATE_TARGET_FREQUENCY = 1000

HUBER_LOSS_DELTA = 1.0

# https://keon.io/deep-q-learning
# https://jaromiru.com/2016/10/03/lets-make-a-dqn-implementation/
# https://jaromiru.com/2016/10/21/lets-make-a-dqn-full-dqn/
# 1. Target network; 2. Error clipping

def huber_loss(y_true, y_pred):
    error = y_true - y_pred

    condition = K.abs(error) < HUBER_LOSS_DELTA
    l2 = 0.5 * K.square(error)
    l1 = HUBER_LOSS_DELTA * (K.abs(error) - 0.5 * HUBER_LOSS_DELTA)

    loss = tf.where(condition, l2, l1)

    return K.mean(loss)

class DQNAgent:
    def __init__(self, state_size, action_size):
        self.state_size = state_size
        self.action_size = action_size
        self.memory = memory.PrioritizedReplayMemory(MEMORY_CAPACITY)
        self.gamma = GAMMA # discount rate
        self.learning_rate = LEARNING_RATE

        self.steps = 0
        self.epsilon = EPSILON_MAX
        self.exploration = True
        self.model = self._build_model()
        self.target_model = self._build_model()

    def _build_model(self):
        ''' Neural Net for Deep-Q learning model
        The model takes the state as input and output the Q-value for each possible action
        This kind of model has the advantage, that if we want to perform
        a Q-value update or pick the action with the highest Q-value, we only have to do
        one forward pass through the network and have all Q-values for all actions available
        immediately
        cite: https://www.intelnervana.com/demystifying-deep-reinforcement-learning/
        '''
        model = Sequential()

        # 'Dense' is the basic form of a neural network layer
        # Input Layer of state size(4) and hidden layer with 24 nodes
        model.add(Dense(64, input_dim = self.state_size, activation='relu'))

        # Hidden layer with 24 nodes
        # model.add(Dense(24, activation = 'relu'))

        # Output layer with # of actions: 2 nodes (left, or right)
        model.add(Dense(self.action_size, activation='linear'))

        opt = Adam(lr = self.learning_rate)
        model.compile(loss=huber_loss, optimizer=opt)
        return model

    def updateTargetModel(self):
        self.target_model.set_weights(self.model.get_weights())

    def remember(self, state, action, reward, next_state, done):
        sample = (state, action, reward, next_state, done)
        x, y, errors = self._getTargets([(0, sample)])
        self.memory.add(errors[0], sample)

        self.steps += 1

        # add target model and update the target model weigths
        if self.steps % UPDATE_TARGET_FREQUENCY == 0:
            print("update target model. step: {}".
                  format(self.steps))
            self.updateTargetModel()

        self.epsilon = EPSILON_MIN + (EPSILON_MAX - EPSILON_MIN) * math.exp(-LAMBDA * self.steps)

    def act(self, state):
        # act on one input (one state)
        if self.exploration and np.random.rand() < self.epsilon:
            return random.randrange(self.action_size)
        state = state.reshape(1, self.state_size)
        act_values = self.model.predict(state)
        
        # get the action with largest Q value
        return np.argmax(act_values[0])

    def replay(self, batch_size):
        batch = self.memory.sample(batch_size)
        x, y, errors = self._getTargets(batch)

        # update errors
        for i in range(len(batch)):
            idx = batch[i][0]
            self.memory.update(idx, errors[i])

        self.model.fit(x, y, batch_size = batch_size, epochs = 1, verbose = 0)

    def _getTargets(self, batch):
        none_state = np.zeros(self.state_size)
        states = np.array( [exp[1][0] for exp in batch] )
        next_states = np.array( [exp[1][3] for exp in batch] )

        state_action_probs = self.model.predict(states)
        next_state_action_probs_current = self.model.predict(next_states)
        next_state_action_probs_target = self.target_model.predict(next_states)

        batch_length = len(batch)

        x = np.zeros( (batch_length, self.state_size) )
        y = np.zeros( (batch_length, self.action_size) )
        errors = np.zeros(batch_length)

        for i in range(batch_length):
            state, action, reward, next_state, done = batch[i][1]

            target = state_action_probs[i]
            oldVal = target[action]
            if done:
                target[action] = reward
            else:
                # double DQN
                # action is calculated from current network
                # Q value is calculated from target network
                maxAction = np.argmax(next_state_action_probs_current[i])
                target[action] = reward + self.gamma * next_state_action_probs_target[i][maxAction]

            x[i] = state
            y[i] = target
            errors[i] = abs(oldVal - target[action])
        return (x, y, errors)

    def stopExploration(self):
        self.exploration = False

class RandomAgent:
    def __init__(self, action_size):
        self.action_size = action_size
        self.memory = memory.PrioritizedReplayMemory(MEMORY_CAPACITY)

    def act(self, state):
        return random.randint(0, self.action_size - 1)

    def remember(self, state, action, reward, next_state, done):
        error = abs(reward)
        self.memory.add(error, (state, action, reward, next_state, done))

    def replay(self):
        pass
    
if __name__ == "__main__":
    env = gym.make('CartPole-v0')

    state_size = env.observation_space.shape[0]
    action_size = env.action_space.n
    agent = DQNAgent(state_size, action_size)
    done = False
    batch_size = BATCH_SIZE

    DEBUG = False

    randomAgent = RandomAgent(action_size)
    while randomAgent.memory.isFull() == False:
        state = env.reset()
        for time in range(500):
            action = randomAgent.act(state)
            next_state, reward, done, _ = env.step(action)
            randomAgent.remember(state, action, reward, next_state, done)
            state = next_state
            if done:
                break
    print("Finish to full the random agent memory")
    agent.memory = randomAgent.memory
    randomAgent = None

    env = Monitor(env, 'tmp/cart-pole-ddqn-2', force=True)
    for e in range(EPISODES):
        if DEBUG and e >= EPISODES - 10:
            agent.stopExploration()

        state = env.reset()
        for time in range(500):
            #env.render()
            
            # act on one input (one state)
            action = agent.act(state)
            next_state, reward, done, _ = env.step(action)

            agent.remember(state, action, reward, next_state, done)
            agent.replay(batch_size)
            state = next_state
            if done:
                print("episode: {}/{}, score: {}, e: {:.2}"
                      .format(e, EPISODES, time, agent.epsilon))
                break

    env.close()
