​import random
import math
import matplotlib.pyplot as plt

# 1. Generate 100 points in 3 clusters
random.seed(42) # For reproducibility
cluster1 = [[random.gauss(2, 0.5), random.gauss(2, 0.5)] for _ in range(33)]
cluster2 = [[random.gauss(5, 0.5), random.gauss(5, 0.5)] for _ in range(33)]
cluster3 = [[random.gauss(8, 0.5), random.gauss(2, 0.5)] for _ in range(34)]
data = cluster1 + cluster2 + cluster3

# 2. Euclidean distance function
def euclidean_distance(p1, p2):
    return math.sqrt(sum((p1[i] - p2[i])**2 for i in range(len(p1))))

# 3. K-Means Algorithm
def k_means(data, k=3, iterations=10):
    # Initialize centroids randomly from data points
    centroids = random.sample(data, k)
   
    for _ in range(iterations):
        # Assignment step
        clusters = [[] for _ in range(k)]
        for point in data:
            distances = [euclidean_distance(point, c) for c in centroids]
            closest_idx = distances.index(min(distances))
            clusters[closest_idx].append(point)
           
        # Update step
        new_centroids = []
        for i in range(k):
            if not clusters[i]: # Handle empty cluster
                new_centroids.append(random.choice(data))
                continue
           
            # Calculate mean of cluster
            new_centroid = [
                sum(p[j] for p in clusters[i]) / len(clusters[i])
                for j in range(len(data[0]))
            ]
            new_centroids.append(new_centroid)
        centroids = new_centroids
       
    return centroids, clusters

# Run algorithm
k = 3
centroids, clusters = k_means(data, k)

# 4. Plotting
colors = ['r', 'g', 'b']
for i in range(k):
    # Plot points
    x = [p[0] for p in clusters[i]]
    y = [p[1] for p in clusters[i]]
    plt.scatter(x, y, color=colors[i], label=f'Cluster {i+1}')
    # Plot centroids
    plt.scatter(centroids[i][0], centroids[i][1], color='black', marker='x', s=100)

plt.title('K-Means from Scratch (No NumPy)')
plt.legend()
plt.show()
