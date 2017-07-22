## Reinforcement Learning
### Setup
* Install ActiveTcl 8.6 for python 3.5
* The code comes from: http://ai.berkeley.edu/reinforcement.html
* It needs to run for python 3.5

### Reinforcement Learning courses
<http://www0.cs.ucl.ac.uk/staff/d.silver/web/Teaching.html>

<http://www.wildml.com/2016/10/learning-reinforcement-learning/>

<http://ai.berkeley.edu/reinforcement.html>

<http://rll.berkeley.edu/deeprlcourse/>

### Temporal Differences
<http://artint.info/html/ArtInt_264.html>

### Exploration and Exploitation
<http://artint.info/html/ArtInt_266.html>

### Evaluating Reinforcement Learning Algorithms
<http://artint.info/html/ArtInt_267.html>

## Deep Reinforcement Learning
* [Demysitifying Deep RL](https://www.intelnervana.com/demystifying-deep-reinforcement-learning/)
* [Error clipping on DQN](https://stackoverflow.com/questions/36462962/loss-clipping-in-tensor-flow-on-deepminds-dqn)
* [DQN](https://jaromiru.com/2016/10/21/lets-make-a-dqn-full-dqn/)
* [DDQN](https://jaromiru.com/2016/11/07/lets-make-a-dqn-double-learning-and-prioritized-experience-replay/)

### Policy Gradients
#### Best ever introduction
* [Pong from Pixels from Karpathy](http://karpathy.github.io/2016/05/31/rl/)

#### Score function
* [score function gradient estimator](http://blog.shakirm.com/2015/11/machine-learning-trick-of-the-day-5-log-derivative-trick/)
* [what is score function](https://en.wikipedia.org/wiki/Score_(statistics))

## Open AI - Gym
### Cart Pole
* Basic DQN: [Commit](https://github.com/hsgui/interest-only/commit/819b9a491d78a746a8eec12331b5c74718eb62d7), [Evaluation](https://gym.openai.com/evaluations/eval_ytHZ89GTZaDudD6Hz3gQ)
* DQN with batch training: [commit](https://github.com/hsgui/interest-only/commit/2e96517ae4c64f823208e3b83a7ca5dec1b163c6), [Evaluation](https://gym.openai.com/evaluations/eval_4xNlDFtTzqyDFwyZ2dRdA)
* DQN with target network and error clipping: [Commit](https://github.com/hsgui/interest-only/commit/b72edb82a9881b91a242ed95b9ef80be62c3b9c9), [Evaluation](https://gym.openai.com/evaluations/eval_C3Z8la1MSmANS7ntDJSeQ)
* Stable DDQN with prioritized experimence replay: [Commit](https://github.com/hsgui/interest-only/commit/4721a7cc6e6e64e6e901ba76163aafca8209bc43), [Evaluation](https://gym.openai.com/evaluations/eval_gkvRqPAoTTO9Z2wirXGLtw)