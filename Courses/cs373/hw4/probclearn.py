import numpy as np
import numpy.linalg as la
# Input: numpy matrix X of features, with n rows (samples), d columns (features)
# X[i,j] is the j-th feature of the i-th sample
# numpy vector y of labels, with n rows (samples), 1 column
# y[i] is the label (+1 or -1) of the i-th sample
# Output: scalar q
# numpy vector mu_positive of d rows, 1 column
# numpy vector mu_negative of d rows, 1 column
# scalar sigma2_positive
# scalar sigma2_negative
def run(X,y):
    # Your code goes here
    kplus = 0
    kminus = 0
    mu_positive = 0
    mu_negative = 0
    numRows = np.shape(X)[0]
    numCols = np.shape(X)[1]
    for i in range(numRows):
        if y[i] == 1.0:
            kplus += 1.0
            mu_positive += X[i]
        else:
            kminus += 1.0
            mu_negative += X[i]
    q = kplus/numRows
    mu_positive *= (1.0/kplus)
    mu_negative *= (1.0/kminus)
    sigma2_positive = 0
    sigma2_negative = 0
    for i in range(numRows):
        if y[i] == 1.0:
            sigma2_positive += np.power(la.norm(X[i] - mu_positive),2)
        else:
            sigma2_negative += np.power(la.norm(X[i] - mu_negative),2)
    sigma2_positive *= (1.0/(numCols*kplus))
    sigma2_negative *= (1.0/(numCols*kminus))
    mu_positive = mu_positive.reshape((-1,1))
    mu_negative = mu_negative.reshape((-1,1))
    return q, mu_positive, mu_negative, sigma2_positive, sigma2_negative