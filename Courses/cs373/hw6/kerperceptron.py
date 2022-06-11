import numpy as np
import K
# Input: number of iterations L
# numpy matrix X of features, with n rows (samples), d columns (features)
# X[i,j] is the j-th feature of the i-th sample
# numpy vector y of labels, with n rows (samples), 1 column
# y[i] is the label (+1 or -1) of the i-th sample
# Output: numpy vector alpha of n rows, 1 column
# number of iterations that were actually executed (iter+1)
def run(L,X,y):
    # Your code goes here
    n = np.shape(X)[0]
    d = np.shape(X)[1]
    alpha = np.zeros((n,1))
    for iter in range(L):
        all_points_classified_correctly = True
        for t in range(n):
	    k = np.zeros(n)
            s = 0
	    for j in range(n):
		k[j] = K.run(np.reshape(X[j], (1,-1)),np.reshape(X[t], (1,-1)))
		s += alpha[j]*y[j]*k[j]
	    if (y[t]*s <= 0):
                alpha[t] += 1
                all_points_classified_correctly = False
        if(all_points_classified_correctly):
            break        
    return alpha, iter+1
