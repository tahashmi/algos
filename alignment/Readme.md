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

##  Implemented Methods

### 1.1 Naive Recursive
- **Approach:** Direct implementation of the mathematical recurrence relation.
- **Complexity:** $O(3^{n+m})$ (Exponential time).
- **Description:** Highly inefficient for long sequences as it recomputes the same subproblems multiple times. It includes a recursive backtracking function to display the alignment.

### 1.2. Top-Down Memoization
- **Approach:** Recursive approach enhanced with a "Memo Table" (2D Array).
- **Complexity:** $O(n \times m)$ (Linear time relative to the product of lengths).
- **Description:** Before computing a score, the program checks if it already exists in the table. This drastically reduces execution time while maintaining the recursive logic.

### 1.3. Bottom-Up Tabulation
- **Approach:** Iterative matrix filling.
- **Complexity:** $O(n \times m)$.
- **Description:** This is the standard "Production" version of Needleman-Wunsch. It fills a $(N+1) \times (M+1)$ scoring matrix and then backtracks from the bottom-right corner to the top-left to find the optimal path.

---
# 2. Smith-Waterman Local Alignment (C Implementation)

This repo also implements the **Smith-Waterman Algorithm** for local sequence alignment using three different programming paradigms in C.

## Algorithm Purpose
Unlike Needleman-Wunsch (Global), Smith-Waterman identifies the most similar **sub-regions** between two sequences. It is widely used for identifying conserved domains or motifs.

### Scoring
- **Match:** `+1`
- **Mismatch:** `-1`
- **Gap:** `-2`
- **Floor:** `0` (Scores never drop below zero)

## Implementation Methods

### 2.1. **Naive Recursive**: 
Calculates the local alignment score by exploring all paths. Extremely slow for sequences > 10 chars.
### 2.2. **Top-Down (Memoization)**: 
Uses a 2D cache to store sub-alignment scores, significantly optimizing the recursive approach.
### 2.3. **Bottom-Up (Tabulation)**: 
The standard iterative matrix-filling approach. It finds the global maximum in the table and backtracks until it hits a zero.

[Global Alignment App - Needleman-Wunsch global alignment algorithm](https://bioboot.github.io/bimm143_W20/class-material/nw/)

[Needleman-Wunsch Online Tool](https://needleman-wunsch.com/)

[Freiburg RNA Tools, Teaching - Smith-Waterman](https://rna.informatik.uni-freiburg.de/Teaching/index.jsp?toolName=Smith-Waterman)

[An Analysis of Pairwise Sequence Alignment Algorithm Complexities: Needleman-Wunsch, Smith-Waterman, FASTA, BLAST and Gapped BLAST](https://biochem218.stanford.edu/Projects%202004/Chan.pdf)

