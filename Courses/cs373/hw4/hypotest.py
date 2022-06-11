import numpy as np
import math
from scipy.stats import t
# Input: numpy vector a of scalar values, with k rows, 1 column
# numpy vector b of scalar values, with k rows, 1 column
# scalar alpha
# Output: reject (0 or 1)
def run(a,b,alpha):
    # Your code goes here
    k = np.shape(a)[0]
    a = a.flatten()
    b = b.flatten()
    u1 = (1/float(k))*sum(a)
    u2 = (1/float(k))*sum(b)
    o1 = (1/float(k))*sum(pow((a-u1),2))
    o2 = (1/float(k))*sum(pow((b-u2),2))
    x = ((u1-u2)*math.sqrt(float(k)))/(math.sqrt(o1+o2))
    v = math.ceil(((pow((o1+o2),2))*(float(k)-1))/(pow(o1,2)+pow(o2,2)))
    if x > t.ppf(1-alpha, v):
        reject = 1
    else:
        reject = 0
    return reject
