import numpy as np
import numpy.linalg as la
# Input: number of features F
# numpy matrix X, with n rows (samples), d columns (features)
# Output: numpy vector mu, with d rows, 1 column
# numpy matrix Z, with d rows, F columns
def run(F,X):
    X = np.copy(X)
    n = np.shape(X)[0]
    d = np.shape(X)[1]
    mu = np.zeros((d,1))
    for i in range(d):
        mu[i] = (1.0/n)*sum(X[:,i])
    for t in range(n):
        for i in range(d):
            X[t][i] -= mu[i]
    U, s, Vt = la.svd(X, False)
    g = s[0:F]
    for i in range(F):
        if g[i] > 0:
            g[i] = 1/g[i]
    W = Vt[0:F, 0:d]
    Z = np.dot(np.transpose(W),np.diag(g))
    return (mu, Z)