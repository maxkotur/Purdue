import numpy as np
# Input: numpy vector theta of d rows, 1 column
# numpy vector x of d rows, 1 column
# Output: label (+1 or -1)
def run(theta,x):
    # Your code goes here
    theta = theta.reshape((1,-1))
    if np.dot(theta,x) > 0:
        label = 1.0
    else:
        label = -1.0
    return label
