import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

# Assuming 'data_whitened' is your dataset
wcss = []
k_range = range(1, 11)

for k in k_range:
    # Use k-means++ for more stable results across iterations
    kmeans = KMeans(n_clusters=k, init='k-means++', random_state=42, n_init=10)
    kmeans.fit(data_whitened)
    
    # Inertia is the WCSS for the fitted model
    wcss.append(kmeans.inertia_)

# Plotting the results to find the "elbow"
plt.figure(figsize=(8, 5))
plt.plot(k_range, wcss, marker='o', linestyle='--', color='b')
plt.title('Elbow Method for Optimal k')
plt.xlabel('Number of Clusters (k)')
plt.ylabel('WCSS (Inertia)')
plt.xticks(k_range)
plt.grid(True)
plt.show()
