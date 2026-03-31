# 1. Needleman-Wunsch Global Alignment (C Implementation)

This repository contains three different C-based implementations of the **Needleman-Wunsch Algorithm**. The project demonstrates the progression from basic recursion to optimized Dynamic Programming (Top-Down and Bottom-Up) to find the optimal global alignment between two DNA/protein sequences.

##  Overview

The goal is to align two specific sequences using a global alignment strategy:
- **Sequence A:** `GATCGGGAC`
- **Sequence B:** `CGTACACACTAG`

### Scoring System
The algorithm uses the following scoring parameters:
| Parameter | Score |
| :--- | :--- |
| **Match** | `+1` |
| **Mismatch** | `-1` |
| **Gap (Indel)** | `-2` |

---

##  Implemented Methods

### 1.1 Naive Recursive (`recursive.c`)
- **Approach:** Direct implementation of the mathematical recurrence relation.
- **Complexity:** $O(3^{n+m})$ (Exponential time).
- **Description:** Highly inefficient for long sequences as it recomputes the same subproblems multiple times. It includes a recursive backtracking function to display the alignment.

### 1.2. Top-Down Memoization (`top_down.c`)
- **Approach:** Recursive approach enhanced with a "Memo Table" (2D Array).
- **Complexity:** $O(n \times m)$ (Linear time relative to the product of lengths).
- **Description:** Before computing a score, the program checks if it already exists in the table. This drastically reduces execution time while maintaining the recursive logic.

### 1.3. Bottom-Up Tabulation (`bottom_up.c`)
- **Approach:** Iterative matrix filling.
- **Complexity:** $O(n \times m)$.
- **Description:** This is the standard "Production" version of Needleman-Wunsch. It fills a $(N+1) \times (M+1)$ scoring matrix and then backtracks from the bottom-right corner to the top-left to find the optimal path.
