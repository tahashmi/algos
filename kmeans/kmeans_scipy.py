import numpy as np
from scipy.cluster.vq import kmeans, vq, whiten
import matplotlib.pyplot as plt

# 1. Generate 100 points in 3 clusters
np.random.seed(42) # For reproducibility
c1 = np.random.normal(2, 0.5, (33, 2))
c2 = np.random.normal(5, 0.5, (33, 2))
c3 = np.random.normal(8, 0.5, (34, 2))
data = np.vstack((c1, c2, c3))

# 2. Whiten data (normalize)
data_whitened = whiten(data)

# 3. SciPy K-Means
k = 3
# centroids: coordinates of centroids, distortion: sum of squared distances
centroids, distortion = kmeans(data_whitened, k)

# Assign each point to a cluster
idx, _ = vq(data_whitened, centroids)

# 4. Plotting
plt.scatter(data_whitened[idx==0,0], data_whitened[idx==0,1], color='r', label='Cluster 1')
plt.scatter(data_whitened[idx==1,0], data_whitened[idx==1,1], color='g', label='Cluster 2')
plt.scatter(data_whitened[idx==2,0], data_whitened[idx==2,1], color='b', label='Cluster 3')

# Plot centroids
plt.scatter(centroids[:,0], centroids[:,1], color='black', marker='x', s=100, label='Centroids')

plt.title('K-Means using SciPy')
plt.legend()
plt.show()
