# IIR v.s. FIR
1. IIR filters are usually considered for better design performance, however when designing IIR filters, poles must be considered and ensured that the pole is within the ROC.

# Adaptive filter
1. Coefficient updating filters, the coefficients changes according to the inputs, however even if the coefficient you trained converges, the whole system stabilbility might not converges, i.e. the bias for whole system performance is still large.

# Feedback Network.
1 Note feedback network cannot be pipelined!

# LMS
1. $\hat{d}(n)$ is an estimated value which is time varying.
2. In the LMS or adaptive filter, loop is usually the bottleneck, due to the value that it cannot be pipeliend since it is a feedback network.
3. $e_f(n|m)$ where n is the time period, m is the stage. So $e_f(n-1|m)$ means the time instance n-1 in m stage.


# FFT
1. N-point FFT, the N means the resolution of your signals. N trys to partition the $2\pi$ circle into N parts. Then try to decompose the signals in a discrete manner into these $2\pi/N$ components.
2. The resolution of f is defined as $f/N$.
3. Decimation in time means the output is time and it is not in the ascending order.
4. Decimation in frequency means the output is frequency and not in ascending order but actually in an order that can be correct using bit-reversed algorithm.
5. $w_N^0$ is known as the critical factor. We usually represent FFT algroithm using Trellis diagram.
6. FFT must compute the high-f component and low-f components at the same time(Uniform transform), however sometimes we only want low-f components yet does not want high-f part to reduce the computation complexity.How to solve it? Use DCT
7. When building hardware for FFT, we would actually first analyze how many butterflies we need, and we would try to reuse those butterflies.
8. Due to the natural of DFT algorithm, the signals get replicated in a period of time. There might exist a cutoff edge between the original signal and the replicated signal, this contributes a high-f component to the spectrum, which is bad.

# Algorithm analysis
1. Must consider Precision, Complexity of algorithm, Parrallizability, Resources constraints and Area.
2. Symmetry exists in lots of AI and DSP algorithm.
3. Usually DSP algorithm are bounded by resources and Memory bandwidth.

# DCT(Real part only FFT)
1. Computes only the low-f part of signals.
2. However, quantization and truncation problem has to be considered using DCT.

# DWT(Filter banks)
1. DWT ultilizes filter banks to allow multiple coeffcients access and multiple filters to compute at the same time.
2. Large SRAM can be divided into small banks to allow parallel access of memory data.
