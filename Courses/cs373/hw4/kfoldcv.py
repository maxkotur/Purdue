import numpy as np
import probclearn
import probcpredict
# Input: number of folds k
# numpy matrix X of features, with n rows (samples), d columns (features)
# numpy vector y of scalar values, with n rows (samples), 1 column
# Output: numpy vector z of k rows, 1 column
def run(k,X,y):
    # Your code goes here
    n = np.shape(X)[0]
    d = np.shape(X)[1]
    z = np.zeros((k,1))
    for i in range(k):
        num = n*(i+1)/k
        T = range((n*i)/k, num)
        S = range(0,n)
        s = [x for x in S if x not in T]
        Xt = np.zeros((len(s), d))
        yt = np.zeros((len(s), 1))
        m = 0
        for l in s:
            Xt[m] = X[l]
            yt[m] = y[l]
            m += 1
        q, mu_positive, mu_negative, sigma2_positive, sigma2_negative = probclearn.run(Xt, yt)
        z[i] = 0
        j = 0
        for j in T:
            if y[j] != probcpredict.run(q, mu_positive, mu_negative, sigma2_positive, sigma2_negative, X[j]):
                z[i] += 1
        z[i] /= len(T)
    return z
