import numpy as np
import probclearn
import probcpredict
# Input: number of bootstraps B
# numpy matrix X of features, with n rows (samples), d columns (features)
# numpy vector y of scalar values, with n rows (samples), 1 column
# Output: numpy vector z of B rows, 1 column
def run(B,X,y):
    # Your code goes here
    n = np.shape(X)[0]
    d = np.shape(X)[1]
    z = z = np.zeros((B,1))
    for i in range(B):
        u = np.zeros(n)
        S = []
        for j in range(n):
            k = np.random.randint(n)
            u[j] = k
            if k not in S:
                S.append(k)
        T = range(0,n)
        T = [x for x in T if x not in S]
        Xt = np.zeros((n, d))
        yt = np.zeros((n, 1))
        for j in range(n):
            for l in range(d):
                Xt[j][l] = X[int(u[j])][l]
            yt[j] = y[int(u[j])]
        q, mu_positive, mu_negative, sigma2_positive, sigma2_negative = probclearn.run(Xt, yt)
        z[i] = 0
        for j in T:
            if y[j] != probcpredict.run(q, mu_positive, mu_negative, sigma2_positive, sigma2_negative, X[j]):
                z[i] += 1
        z[i] /= len(T)
    return z
