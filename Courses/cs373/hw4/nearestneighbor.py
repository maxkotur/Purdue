import numpy as np
import numpy.linalg as la
# Input: numpy matrix X of features, with n rows (samples), d columns (features)
# X[i,j] is the j-th feature of the i-th sample
# numpy vector y of labels, with n rows (samples), 1 column
# y[i] is the label (+1 or -1) of the i-th sample
# numpy vector z of d rows, 1 column
# Output: label (+1 or -1)
def run(X,y,z):
    # Your code goes here
    z = z.flatten()
    c = 0
    b = la.norm(z - X[0])
    numRows = np.shape(X)[0]
    for i in range(numRows):
        if  la.norm(z - X[i]) < b:
            c = i
            b = la.norm(z - X[i])
    label = y[c]
    label = label[0]
    return label
