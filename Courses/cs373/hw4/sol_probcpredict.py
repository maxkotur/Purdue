import numpy as np
import numpy.linalg as la
import math
# Input: scalar q
#        numpy vector mu_positive of d rows, 1 column
#        numpy vector mu_negative of d rows, 1 column
#        scalar sigma2_positive
#        scalar sigma2_negative
#        numpy vector z of d rows, 1 column
# Output: label (+1 or -1)
def run(q,mu_positive,mu_negative,sigma2_positive,sigma2_negative,z):
    (d,tmp) = np.shape(z)
    if math.log(q/(1-q)) - d/2.0 * math.log(sigma2_positive/sigma2_negative) - 1/(2*sigma2_positive) * la.norm(z - mu_positive)**2 + 1/(2*sigma2_negative) * la.norm(z - mu_negative)**2 > 0:
        return 1.
    else:
        return -1.
    return label
