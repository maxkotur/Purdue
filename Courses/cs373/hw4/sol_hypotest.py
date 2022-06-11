import numpy as np
from scipy.stats import t
# Input: numpy vector a of scalar values, with k rows, 1 column
#        numpy vector b of scalar values, with k rows, 1 column
#        scalar alpha
# Output: reject (0 or 1)
def run(a,b,alpha):
  k = a.size
  mu1 = np.mean(a)
  mu2 = np.mean(b)
  sigma12 = np.var(a)
  sigma22 = np.var(b)
  x = (mu1 - mu2) * np.sqrt(k) / np.sqrt(sigma12 + sigma22)
  v = np.ceil((sigma12 + sigma22)**2 * (k-1) / (sigma12**2 + sigma22**2))
  if x > t.ppf(1-alpha, v):
    reject = 1
  else:
    reject = 0

  return reject
