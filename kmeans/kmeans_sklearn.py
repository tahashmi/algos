import numpy as np
from scipy.cluster.vq import vq, whiten
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

# 1. Generate 100 points in 3 clusters
np.random.seed(42) # For reproducibility
c1 = np.random.normal(2, 0.5, (33, 2))
c2 = np.random.normal(5, 0.5, (33, 2))
c3 = np.random.normal(8, 0.5, (34, 2))
data = np.vstack((c1, c2, c3))

# 2. Whiten data (normalize)
data_whitened = whiten(data)

# 3. Initialize the model
# n_clusters: Number of groups to form
# init: 'k-means++' speeds up convergence by smart centroid placement
kmeans = KMeans(n_clusters=3, init='k-means++', random_state=100)

# 4. Fit the model and predict clusters
labels = kmeans.fit_predict(data_whitened)

# 5. Access results
centroids = kmeans.cluster_centers_


# Assign each point to a cluster
idx, _ = vq(data_whitened, centroids)

# 6. Plotting
plt.scatter(data_whitened[idx==0,0], data_whitened[idx==0,1], color='r', label='Cluster 1')
plt.scatter(data_whitened[idx==1,0], data_whitened[idx==1,1], color='g', label='Cluster 2')
plt.scatter(data_whitened[idx==2,0], data_whitened[idx==2,1], color='b', label='Cluster 3')

# Plot centroids
plt.scatter(centroids[:,0], centroids[:,1], color='black', marker='x', s=100, label='Centroids')

plt.title('K-Means using sklearn')
plt.legend()
plt.show()
