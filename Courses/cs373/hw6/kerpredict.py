import numpy as np
import K
# Input: numpy vector alpha of n rows, 1 column
# numpy matrix X of features, with n rows (samples), d columns (features)
# X[i,j] is the j-th feature of the i-th sample
# numpy vector y of labels, with n rows (samples), 1 column
# y[i] is the label (+1 or -1) of the i-th sample
# numpy vector z of d rows, 1 column
# Output: label (+1 or -1)
def run(alpha,X,y,z):
    # Your code goes here
    n = np.shape(X)[0]
    d = np.shape(X)[1]
    k = np.zeros(n)
    s = 0
    for j in range(n):
	k[j] = K.run(np.reshape(X[j], (1,-1)),z)
	s += alpha[j]*y[j]*k[j]
    if (s > 0):
	label = 1.0
    else:
	label = -1.0
    return label
