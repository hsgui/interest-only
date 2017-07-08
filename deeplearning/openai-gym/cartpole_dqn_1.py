from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.optimizers import Adam
import random
import gym
from gym.wrappers.monitoring import Monitor
import numpy as np
from collections import deque

DEBUG = False

# https://keon.io/deep-q-learning
class DQNAgent:
    def __init__(self, state_size, action_size):
        self.state_size = state_size
        self.action_size = action_size
        self.memory = deque(maxlen=2000)
        self.gamma = 0.95 # discount rate
        self.epsilon = 1.0 # exploration rate
        self.epsilon_min = 0.01
        self.epsilon_decay = 0.995
        self.learning_rate = 0.001
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

        model.compile(loss='mse',
                      optimizer=Adam(lr = self.learning_rate))
        return model

    def remember(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))

    def act(self, state):
        # act on one input (one state)
        if self.exploration and np.random.rand() <= self.epsilon:
            return random.randrange(self.action_size)
        act_values = self.model.predict(state)
        # get the action with largest Q value
        return np.argmax(act_values[0])

    def replay(self, batch_size):
        minibatch = random.sample(self.memory, batch_size)
        for state, action, reward, next_state, done in minibatch:
            target = reward
            if not done:
                target = reward + self.gamma * np.amax(self.model.predict(next_state)[0])
            target_f = self.model.predict(state)
            target_f[0][action] = target
            self.model.fit(state, target_f, epochs = 1, verbose = 0)
        if self.epsilon > self.epsilon_min:
            self.epsilon *= self.epsilon_decay

    def stopExploration(self):
        self.exploration = False

if __name__ == "__main__":
    env = gym.make('CartPole-v0')
    env = Monitor(env, 'tmp/cart-pole-dqn-1', force=True)

    state_size = env.observation_space.shape[0]
    action_size = env.action_space.n
    agent = DQNAgent(state_size, action_size)
    done = False
    batch_size = 32

    EPISODES = 2000
    DEBUG = False

    for e in range(EPISODES):
        if DEBUG and e >= EPISODES - 10:
            agent.stopExploration()

        state = env.reset()
        state = np.reshape(state, [1, state_size])
        for time in range(500):
            # env.render()
            
            # act on one input (one state)
            action = agent.act(state)
            next_state, reward, done, _ = env.step(action)
            reward = reward if not done else -10
            next_state = np.reshape(next_state, [1, state_size])
            agent.remember(state, action, reward, next_state, done)
            state = next_state
            if done:
                print("episode: {}/{}, score: {}, e: {:.2}"
                      .format(e, EPISODES, time, agent.epsilon))
                break

        if len(agent.memory) > batch_size:
            agent.replay(batch_size)
    env.close()
