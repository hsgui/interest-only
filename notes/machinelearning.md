
### [Bias-Variance Dilemma][1]
> The name bias-variance dilemma comes from two terms in statistics: **bias**, which corresponds to underfitting, and **variance**, which corresponds to overfitting.

The model is biased in that it assumes that the data will behave in a certain fashion (linear, quadratic, etc) even though that assumption may not be true. That is, the model that is not complex enough to capture the important features

The model with very high variance uses a very complex curve to get as close to every data point as possible.

> Bias and variance are actually side effects of one factor: **the complexity of our mode**

#### [Bias-Variance Decomposition Derivation][2]
1. Bias term
2. Variance term
3. unavoidable irreducible error term

#### Training and Test Error
* Low complexity will result in poor accuracy (and thus high error) for both training and test data. It's because the model lacks enough complexity to describe the data at all
* High complexity will result in a low training error and a high test error. It's because a complex model will be able to model the training data a bit *too* well, and thus can't generalize to the test data
* The best complexity maybe lie where the test error reaches a minimum.
* Use cross-validation when we have relatively few data points and the algorithms require a fair amount of data

#### High Bias:
* Use a more complex model

#### High variance:
1. **Regularization**: add penality for growing too complex. Essentially, regularization injects "bias" into the model by telling it not to become too complex. Common regularization techniques include lasso or ridge regression, dropout for neural networks, and soft margin SVMs
2. Naive approach is to use more data (which is almost always very hard to come across)
3. **Ensemble learning**: reduce the variance without sacrificing bias. The idea is to have an *ensemble* of multiple classifiers (typically decision trees) trained on random subsets of the trainning data. To actually classify a data point, the ensemble of classifiers all "vote" on a classification

[1]: https://ml.berkeley.edu/blog/2017/07/13/tutorial-4/
[2]: https://en.wikipedia.org/wiki/Bias%E2%80%93variance_tradeoff#Derivation