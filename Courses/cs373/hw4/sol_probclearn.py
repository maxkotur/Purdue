import numpy as np
import numpy.linalg as la
# Input: numpy matrix X of features, with n rows (samples), d columns (features)
#            X[i,j] is the j-th feature of the i-th sample
#        numpy vector y of labels, with n rows (samples), 1 column
#            y[i] is the label (+1 or -1) of the i-th sample
# Output: scalar q
#        numpy vector mu_positive of d rows, 1 column
#        numpy vector mu_negative of d rows, 1 column
#        scalar sigma2_positive
#        scalar sigma2_negative
def run(X,y):
    (n,d) = np.shape(X)
    k_positive = 0
    k_negative = 0
    mu_positive = np.zeros((d,1))
    mu_negative = np.zeros((d,1))
    for t in range(0, n):
        if y[t] == 1:
            k_positive = k_positive + 1
            mu_positive = mu_positive + np.array([X[t]]).T
        else:
            k_negative = k_negative + 1
            mu_negative = mu_negative + np.array([X[t]]).T

    q = (k_positive+0.0) / n
    mu_positive = mu_positive / k_positive
    mu_negative = mu_negative / k_negative
    sigma2_positive = 0
    sigma2_negative = 0
    for t in range(0, n):
        if y[t] == 1:
            sigma2_positive = sigma2_positive + la.norm(X[t] - mu_positive.T)**2
        else:
            sigma2_negative = sigma2_negative + la.norm(X[t] - mu_negative.T)**2

    sigma2_positive = sigma2_positive / (d * k_positive)
    sigma2_negative = sigma2_negative / (d * k_negative)   
    return q, mu_positive, mu_negative, sigma2_positive, sigma2_negative
