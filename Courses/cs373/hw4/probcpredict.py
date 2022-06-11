import numpy as np
import math
import numpy.linalg as la
# Input: scalar q
# numpy vector mu_positive of d rows, 1 column
# numpy vector mu_negative of d rows, 1 column
# scalar sigma2_positive
# scalar sigma2_negative
# numpy vector z of d rows, 1 column
# Output: label (+1 or -1)
def run(q,mu_positive,mu_negative,sigma2_positive,sigma2_negative,z):
    # Your code goes here
    z = z.flatten()
    mu_positive = mu_positive.flatten()
    mu_negative = mu_negative.flatten()
    numRows = np.shape(z)[0]
    if math.log(q/(1.0-q)) - (numRows/2.0)*math.log(sigma2_positive/sigma2_negative) - (1.0/(2.0*sigma2_positive))*np.power(la.norm(z - mu_positive),2) + (1.0/(2.0*sigma2_negative))*np.power(la.norm(z - mu_negative),2) > 0:
        label = 1.0
    else:
        label = -1.0
    return label