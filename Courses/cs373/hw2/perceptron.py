import numpy as np
# Input: maximum number of iterations L
# numpy matrix X of features, with n rows (samples), d columns (features)
# X[i,j] is the j-th feature of the i-th sample
# numpy vector y of labels, with n rows (samples), 1 column
# y[i] is the label (+1 or -1) of the i-th sample
# Output: numpy vector theta of d rows, 1 column
# number of iterations that were actually executed (iter+1)
def run(L,X,y):
    # Your code goes here
    numRows = X.shape[1]
    theta = np.zeros((1,numRows))
    theta = np.reshape(theta,numRows,)
    for i in range(0, L):
        iter = np.int(i)
        all_points_classified_correctly = np.bool(True)
        count = np.int(0)
        for j in y:
            if j*(np.dot(X[count],theta)) <= 0:
                temp = np.array(j*X[count])
                theta = np.add(theta,temp)
                all_points_classified_correctly = np.bool(False)
            count += 1
        if all_points_classified_correctly == np.bool(True):
            break
    theta = theta.reshape((-1,1))
    return theta, iter+1
