from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.optimizers import Adam
import random
import math
import gym
from gym.wrappers.monitoring import Monitor
import numpy as np
import sys

import replay_memory as memory

DEBUG = False
DEBUG_STATES = [
    [0.07216398, 0.42593921, -0.20272785, -1.07227655],
    [0.05467548, 0.2243609, -0.15646592, -0.62437505]]

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
LEARNING_RATE = 0.001

def printQ(agent):
    pred = agent.model.predict(np.array(DEBUG_STATES))
    for o in pred:
        sys.stdout.write(str(o)+" ")
    print(";")
    sys.stdout.flush()

# https://keon.io/deep-q-learning
# https://jaromiru.com/2016/10/03/lets-make-a-dqn-implementation/
class DQNAgent:
    def __init__(self, state_size, action_size):
        self.state_size = state_size
        self.action_size = action_size
        self.memory = memory.BasicReplayMemory(MEMORY_CAPACITY)
        self.gamma = GAMMA # discount rate
        self.learning_rate = LEARNING_RATE

        self.steps = 0
        self.epsilon = EPSILON_MAX
        self.exploration = True
        self.model = self._build_model()

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
        model.add(Dense(24, input_dim = self.state_size, activation='relu'))

        # Hidden layer with 24 nodes
        model.add(Dense(24, activation = 'relu'))

        # Output layer with # of actions: 2 nodes (left, or right)
        model.add(Dense(self.action_size, activation='linear'))

        opt = Adam(lr = self.learning_rate)
        model.compile(loss='mse', optimizer=opt)
        return model

    def remember(self, state, action, reward, next_state, done):
        self.memory.add((state, action, reward, next_state, done))

        if DEBUG and self.steps % 1000 == 0:
            printQ(self)
            
        self.steps += 1
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
        batch_length = len(batch)
        
        # batch update
        none_state = np.zeros(self.state_size)
        states = np.array([ exp[0] for exp in batch ])
        next_states = np.array([ (none_state if exp[3] is None else exp[3]) for exp in batch ])

        state_action_probs = self.model.predict(states)
        next_state_action_probs = self.model.predict(next_states)

        x = np.zeros( (batch_length, self.state_size) )
        y = np.zeros( (batch_length, self.action_size) )

        for i in range(batch_length):
            state, action, reward, next_state, done = batch[i]

            target = state_action_probs[i]
            if done:
                target[action] = reward
            else:
                target[action] = reward + self.gamma * np.amax(next_state_action_probs[i])

            x[i] = state
            y[i] = target

        self.model.fit(x, y, batch_size = batch_size, epochs = 1, verbose = 0)

    def stopExploration(self):
        self.exploration = False

if __name__ == "__main__":
    env = gym.make('CartPole-v0')
    #env = Monitor(env, 'tmp/cart-pole-dqn-2', force=True)

    state_size = env.observation_space.shape[0]
    action_size = env.action_space.n
    agent = DQNAgent(state_size, action_size)
    done = False
    batch_size = BATCH_SIZE

    DEBUG = True

    for e in range(EPISODES):
        if DEBUG and e >= EPISODES - 10:
            agent.stopExploration()

        state = env.reset()
        for time in range(500):
            #env.render()
            
            # act on one input (one state)
            action = agent.act(state)
            next_state, reward, done, _ = env.step(action)
            #print("{}, {}, {}, {}, {}".format(state, action, next_state, reward, done))
            reward = reward if not done else -10

            agent.remember(state, action, reward, next_state, done)
            agent.replay(batch_size)
            state = next_state
            if done:
                #print("episode: {}/{}, score: {}, e: {:.2}".format(e, EPISODES, time, agent.epsilon))
                break

    env.close()
