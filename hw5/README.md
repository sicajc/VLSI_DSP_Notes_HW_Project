## Algorithm
1. Understand QR givens rotation again.
2. Understand CORDIC Rotations. Generation mode and rotation modes.

## Matlab code for Givens roation algorithm
1. Gemerate A=QR algorithm where Products of $Q_nQ_{n-1}..Q_n[A|I] = [R|Q]$
2. Understand the iteration number. What does it mean by iteration number?
3. The word length should be 12 bits. So the possible pattern range of A should be first specified.
4. You should have more than 1 test pattern. Other test pattern must also works. Randomly generates the matrix of A then do QR factorization on it.

## Turning the design into fixed-point
1. Using fixed-point designer to find the optimal design after running through multiple QR factorizations.
2. Find the optimal fraction and integer length for your algorithm.
3. Set an error tolerance to be $\delta < 0.1%$, ask for the $\delta$ value.

## Rederive HW from lecture notes
1. From lecture notes, rederive the QR factorization's DG and its linear mapping matrix T.
2. From the matrix T, find the I/O scheduling of your design, then draw the timing table from your derived matrix T.
3. Determine the I/O scheduler boundary for your design, extends the projection vector and scheduling vector out!

## CORDIC HW
1. Understand CORDIC again, rewrite the algorithm that fits CORDIC.
2. Build out a 4 iteration Givens rotations HW out.
3. Rederive the timing diagram fitting this 4 iterations HW design.

## Systolic architecture
1. Code the systolic architecture verilog out from your design.
2. Generate the testbench for you circuit.
3. The result should meet the SPEC you just specified.