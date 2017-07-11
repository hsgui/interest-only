import random

class BasicReplayMemory:
    samples = []

    def __init__(self, capacity):
        self.capacity = capacity

    def add(self, sample):
        if len(self.samples) > self.capacity:
            self.samples.pop(0)

        self.samples.append(sample)

    def sample(self, n):
        n = min(n, len(self.samples))
        return random.sample(self.samples, n)

    def isFull(self):
        return len(self.samples) >= self.capacity
