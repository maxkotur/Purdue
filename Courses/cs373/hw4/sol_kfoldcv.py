import numpy as np
import sol_probclearn as probclearn
import sol_probcpredict as probpredict
# Input: number of folds k
#        numpy matrix X of features, with n rows (samples), d columns (features)
#        numpy vector y of scalar values, with n rows (samples), 1 column
# Output: numpy vector z of k rows, 1 column
def run(k,X,y):
    (n, d) = np.shape(X)
    z = np.zeros((k, 1))
    for i in range(0,k):
        T = set(range(int(np.floor((n*i)/k)), int(np.floor(((n*(i+1))/k)-1))+1))
        S = set(range(0, n)) - T

        q,mu_pos,mu_neg,sigma2_pos,sigma2_neg = probclearn.run(X[list(S)], y[list(S)])
        
        z[i] = 0
        for t in T:
            if y[t] != probpredict.run(q,mu_pos,mu_neg,sigma2_pos,sigma2_neg,np.array([X[t]]).T):
                z[i] += 1

        z[i] /= len(T)
    return z