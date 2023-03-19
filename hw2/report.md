# <strong><font face = "Times New Roman"><p style="text-align: center;">HW2 LMS Filter and DCT Filter design</p></font></strong>
## <font face = "Times New Roman"><p style="text-align: center;">VLSI DSP HW2</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">Shun-Linag Yeh, NCHU Lab612</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">3/18 2023</p></font>

# INDEX
1. [Adaptive FIR Low pass filter](#adaptive-fir-low-pass-filter)
2. [Discrete Wavelet transform](#discrete-wavelet-transform)
3. [References](#references)


# Adaptive FIR Low pass filter
## Problem
<p align="center">
  <img src="./img/problem_1.jpg" width="600" heigh ="400">
</p>

<div style="page-break-after: always;"></div>

# Derivation steps
### Adaptive Filter specification
<p align="center">
  <img src="./img/adaptive_filter_structure.jpg" width="400" heigh ="400">
</p>

1. x(n) is the input signal, wn(z) is the adaptive filter block with coefficients of wn.
2. d_hat(n) is the generated system response and d(n) is the desired signal.
3. e(n) is the error between d_hat(n) and d(n)
4. The adaptive algorithm block determines which kind of policy we should use to find the suitable filter coefficients. In this HW, LMS algorithm is chosen.

### The adaptive FIR filter
<p align="center">
  <img src="./img/desired_signal_generation_fir_filter.jpg" width="400" heigh ="400">
</p>

<p align="center">
  <img src="./img/fir_filter_structure.png" width="400" heigh ="400">
</p>

- The desired output is genereated through the p-tap FIR filter design, where wn is the coefficients that gets updated on the fly.

<div style="page-break-after: always;"></div>

### Error function
<p align="center">
  <img src="./img/error.jpg" width="400" heigh ="400">
</p>

- Error function simply is the difference between the desired signal and the generated system response.

- Ultimate goal is to minimize the autocorrelation between error vector and input signal.



### LMS algorithm
<p align="center">
  <img src="./img/lms_algorithm.jpg" width="400" heigh ="400">
</p>

- mu is the step sizes for the algorithm, which governs the variability of the coefficients in each iteration.
- e(n)X*(n) is the factor of auto-correlation between the input signal and the error function.

### RMS(Root mean square)
<p align="center">
  <img src="./img/RMS.jpg" width="400" heigh ="400">
</p>

- Root mean square used to find the norm of the error vector, we hope that this value be as small as possible s.t. the system is converged.

<div style="page-break-after: always;"></div>

# Code
### Adaptive Filters
<p align="center">
  <img src="./img/adaptive_filter_design.png" width="400" heigh ="400">
</p>

### RMS
<p align="center">
  <img src="./img/root_mean_square.png" width="400" heigh ="400">
</p>



<div style="page-break-after: always;"></div>

### Main drivers
<p align="center">
  <img src="./img/code_main_driver_1.png" width="600" heigh ="400">
</p>

<p align="center">
  <img src="./img/code_main_driver_2.png" width="600" heigh ="400">
</p>

<div style="page-break-after: always;"></div>

# Results
## Adaptive Filter Response n=100, mu = 0.01, sampleSteps = 1 and RMS over time
<p align="center">
  <img src="./img/adaptive_filter_response_normal_mu.jpg" width="400" heigh ="400">
</p>

### Filter Coefficients over time
<p align="center">
  <img src="./img/coefficients_plot.jpg" width="400" heigh ="400">
</p>

### Converged steps
<p align="center">
  <img src="./img/converged_steps.jpg" width="400" heigh ="400">
</p>

<div style="page-break-after: always;"></div>

### 64-point FFT spectrum
<p align="center">
  <img src="./img/fft_system_response.jpg" width="400" heigh ="400">
</p>

- The response is indeed a Low-Pass filter response.

## Adaptive Filter Response n=3000, mu = 0.0001, samepleSteps = 25 and RMS over time
<p align="center">
  <img src="./img/adaptive_filter_response_smaller_mu.jpg" width="400" heigh ="400">
</p>

### Filter Coefficients over time
<p align="center">
  <img src="./img/coefficients_plot_smaller_mu.jpg" width="400" heigh ="400">
</p>

<div style="page-break-after: always;"></div>

### Converged steps
<p align="center">
  <img src="./img/smaller_mu_converged_steps.jpg" width="400" heigh ="400">
</p>

- Notice the changing of the RMS value responses more drmatically due to smaller step difference. Also it takes longer and more sample points for it to converge.


### RMS with large sample size n = 10000
<p align="center">
  <img src="./img/rms_nLarge_result.jpg" width="400" heigh ="400">
</p>

- The convergence bias is found, the filter cannot converge any further, it keeps on oscillating between within the convergence bias.



### Note
- Due to the fact that sample sizes are large for smaller mu, plotting all of the signals makes analysis hard, thus samples_steps is defined s.t. only a certain multiple of signal sample_steps are selected for plotting.

- The latest 16 prediction errors should be selected for caculation, selecting more than that might yield the wrong results, and the filter would never converge.

<div style="page-break-after: always;"></div>

# Discrete Wavelet transform
## Problem

<p align="center">
  <img src="./img/problem2_filter_spec.jpg" width="300" heigh ="300">
</p>

<p align="center">
  <img src="./img/filter_spec_problem.jpg" width="300" heigh ="300">
</p>

- Goal is to build a DWT filter by adopting the (9/7) filters composed of high pass and low pass components.

## Problem a

<p align="center">
  <img src="./img/problem2_a.jpg" width="300" heigh ="300">
</p>

## Problem b

<p align="center">
  <img src="./img/problem2_b.jpg" width="300" heigh ="300">
</p>

<p align="center">
  <img src="./img/problem2_example.jpg" width="300" heigh ="300">
</p>


# Derivation steps
## Wavelet transform
<p align="center">
  <img src="./img/wavelet_fourier.jpg" width="300" heigh ="300">
</p>

- For a fourier transform, the orthnormal basis is selected as e^j2piFt as analyzing function, however for the wavelet has orthonormal basis of wavelet analyzing fuction phi(t).
- Fourier transform ouputs frequency, yet wavelet outputs a translation and scaled autocorrelation of the input.


<p align="center">
  <img src="./img/wavelet_time_frequency.jpg" width="300" heigh ="300">
</p>

- Wavelet would has better time localization for high frequency yet worse time localization for low frequency.
- Wavelet is used to tackle with problem of time and frequency resolution since you cannot have both great time resolution and frequency resolution at the same time. Wavelet is the balance between time and frequency resolution.
- It is extensively used for compressing images.


## 3-level DWT transform

<p align="center">
  <img src="./img/three_level_DWT.jpg" width="300" heigh ="250">
</p>


## 3-level IDWT transform

<p align="center">
  <img src="./img/three_level_IDWT.jpg" width="300" heigh ="250">
</p>


## Symmetric extension scheme

<p align="center">
  <img src="./img/symmetric_extension.jpg" width="300" heigh ="250">
</p>


## PSNR(Peak signal to noise ratio) and MSE(Mean square error)

<p align="center">
  <img src="./img/PSNR_MSE.jpg" width="300" heigh ="250">
</p>


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
