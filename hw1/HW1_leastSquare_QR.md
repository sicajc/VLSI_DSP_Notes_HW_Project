# <strong><font face = "Times New Roman"><p style="text-align: center;">HW1 Least square approximation & QR iterative algorithm</p></font></strong>
## <font face = "Times New Roman"><p style="text-align: center;">VLSI DSP HW1</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">Shun-Linag Yeh, NCHU Lab612</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">3/16 2023</p></font>

### <font face = "Times New Roman"><p style="text-align: center;">[Github Src Code](https://github.com/sicajc/VLSI_DSP_Notes_HW_Project/tree/main/hw1)</p></font>

# INDEX
1. [Least square approximation](#least-square-approximation)
2. [QR iterative algorithm](#qr-iterative-algorithm)
3. [References](#references)


# Least square approximation
## Problem
![](./img/problem1_1.jpg)<br />


## Derivation steps
1. For pseudoinverse uses the pinv matlab function to find the pseudoInverse of A, then approximation x through the equation.
2. For QR decomposition approximation, generate QR using matlab function , using the normal equation (A^t) Ax = (A^t)b, since A = QR, replace A with QR in the normal equation yields , plug the QR into the derived equation to get the solution.
<div style="page-break-after: always;"></div>

## Code
<p align="center">
  <img src="./img/hw1_1.png" width="400" heigh ="400">
</p>



## Result
<p align="center">
  <img src="./img/pseudoInverse_QR_sol.jpg" width="250" heigh ="250">
</p>

<div style="page-break-after: always;"></div>

# QR iterative algorithm
## Problem
<p align="center">
  <img src="./img/problem1_2.jpg" width="300" heigh ="250">
</p>

## Givens rotation
<p align="center">
  <img src="./img/givens_matrix.jpg" width="300" heigh ="250">
</p>

<p align="center">
  <img src="./img/givens_rotation_conditions.jpg" width="300" heigh ="250">
</p>

## Tridiagnalization
1. After computing M' = Q'M using givens rotation through the linear transformation of rotation matrices where Q' is products of a series of Rotation matrices G, we yields an upper triangular matrix that is close to tridiagonal form.
2. Replace the upper symmetrical part of M' with the same result as the lower entries where i<j.
3. We can get triangularized matrix M'',where M'' = Q Q' M

<div style="page-break-after: always;"></div>

## QR Iterative Algorithm
![](img/qr_algorithm.jpg)

## Code
### Main driver
<p align="center">
  <img src="./img/hw1_2_main.png" width="400" heigh ="300">
</p>

<div style="page-break-after: always;"></div>

### Tridiagonalization and QR iterative

<p align="center">
  <img src="./img/tridiagonalized_and_QR.png" width="400" heigh ="300">
</p>

### Givens Rotation
<p align="center">
  <img src="./img/Givens_rotation.png" width="400" heigh ="300">
</p>


<div style="page-break-after: always;"></div>

## Result
### Tridiagonalized matrix
![](./img/tridiagonalized.jpg)

### Eigenvalue matrix after eigen-decomposition
![](./img/qr_after_eigenDecomposition.jpg)

### Eigenvalue decompose using matlab
![](./img/eigen_decompose_using_matlab.jpg)

### Note
1. The result of the Eigen-decomposition differs due to the ordering of the orthnormal basis and the ordering of eigenvectors when calculating the QR matrcies.
2. The eigenvalues are all the same but in different orderings.

<div style="page-break-after: always;"></div>

# Reference

[1] [University of South California, Section 4.2.1: Givens Rotations, Math610 Jim Lambers](https://www.math.usm.edu/lambers/mat610/class0208.pdf)
