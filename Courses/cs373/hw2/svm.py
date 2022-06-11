import numpy as np
import cvxopt as co
# Input: numpy matrix X of features, with n rows (samples), d columns (features)
# X[i,j] is the j-th feature of the i-th sample
# numpy vector y of labels, with n rows (samples), 1 column
# y[i] is the label (+1 or -1) of the i-th sample
# Output: numpy vector theta of d rows, 1 column
def run(X,y):
    # Your code goes here
    numRows = X.shape[1]
    H = np.identity(numRows)
    f = np.zeros((1,numRows))
    f = np.reshape(f,numRows,)
    A = -y*X
    b = np.full((1,X.shape[0]), -1.0)
    b = np.reshape(b,X.shape[0])
    theta = np.array(co.solvers.qp(co.matrix(H,tc='d'),co.matrix(f,tc='d'),co.matrix(A,tc='d'),co.matrix(b,tc='d'))['x'])
    return theta