import numpy as np
import sol_probclearn as probclearn
import sol_probcpredict as probcpredict
# Input: number of bootstraps B
#        numpy matrix X of features, with n rows (samples), d columns (features)
#        numpy vector y of scalar values, with n rows (samples), 1 column
# Output: numpy vector z of B rows, 1 column
def run(B,X,y):
    (n, d) = np.shape(X)
    z = np.zeros((B, 1))
    for i in range(0,B):
        u = [0] * n
        S = set()
        for j in range(0,n):
            k = np.random.randint(0,n)
            u[j] = k
            S.add(k)
        
        T = set(range(0,n)) - S

        q,mu_pos,mu_neg,sigma2_pos,sigma2_neg = probclearn.run(X[u], y[u])

        z[i] = 0
        for t in T:
            if y[t] != probcpredict.run(q,mu_pos,mu_neg,sigma2_pos,sigma2_neg,np.array([X[t]]).T):
                z[i] += 1

        z[i] /= len(T)
    return z