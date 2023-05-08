# QR LU Least square
## Why using QR but not LU when solving least square solution?
1. Since xin = x + n, n is noise, if you simply solve the equation using Axin = Ax + An, if you use LU, the noise would be amplified. However, if you use QR, the noise would stays the same. Norm2 preserving.
2. Also in QR, eigenvalue can be found more efficiently.

## Typical tips to do when you are given a signal
1. Usually when we try to analyze a signal, we would try to find its AutoCorrelation matrix, the eprform SVD on it to find its Singular Value or eigenvales later we can perform PCA to do further analysis on the signals.
2. ARMA Filter means AutoRegressive Moving average filter, which is a combination of IIR and FIR filter.
3. When designing filter, we are usually focusing on the spec of PassBand, transition band and stop band.
