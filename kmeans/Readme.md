# K-Means Clustering: Three Implementation Approaches

This repository contains three distinct implementations of the K-Means clustering algorithm, demonstrating the transition from fundamental logic to optimized production-level libraries.

---

## 1. Pure Python (From Scratch)
A foundational implementation using only the Python Standard Library (`math` and `random`). This version is ideal for understanding the mechanics of the algorithm without the "black box" of external libraries.

* **Logic:** Uses a manual loop for the Assignment and Update phases.
* **Distance:** Implements **Euclidean Distance** using standard Python list comprehensions.
* **Key Feature:** Includes manual handling for empty clusters by re-sampling random points from the dataset to ensure $k$ clusters are maintained.

## 2. SciPy Vector Quantization (`scipy.cluster.vq`)
An implementation leveraging the SciPy library, which is built for scientific and technical computing. This version is more efficient and introduces data preprocessing.

* **Data Whitening:** Uses the `whiten` function to normalize the features, ensuring each dimension has unit variance—a critical step for distance-based clustering.
* **Efficiency:** Utilizes optimized C-based routines for `kmeans` and `vq` (Vector Quantization).
* **Use Case:** Excellent for signal processing and applications where rapid normalization and clustering are required.

## 3. Scikit-learn (`sklearn.cluster`)
The industry-standard implementation using the `KMeans` class. This is the most robust version and is suitable for production machine learning workflows.

* **k-means++:** Uses an advanced initialization technique to select starting centroids that are far apart, leading to faster and more stable convergence.
* **API:** Follows the familiar `.fit()` and `.predict()` paradigm.
* **Optimization:** Highly parallelized and includes parameters to handle multiple initializations (`n_init`) to find the global optimum.

---

## Getting Started

### Prerequisites
You will need Python 3.x and the following libraries:
```bash
pip install numpy scipy scikit-learn matplotlib
