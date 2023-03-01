# Noble Identity
1. Upsampling identity actually has associativity.
2. $X(z)H(z) = H(z)X(z)$ associativity preserved.
3. If delays slots exist within HW, we can compute multiple time series within the same hardware. This can be utlize when the system has a certain delay, lets say 4, then we can try to compute 4 time series at the same time.

# Iteration Period Bound
1. $T_{\infty} = max{all loop bound}$
2. Loop_bound = Loop computation time/#delays in the loop$
3. Sometimes it is useul to first know the bound of the system before restructuring your architecture. The bound is the limit of pipelining and parrallization

# Longest Path method(LPM)
1. Consider an all-pole,4th order IIR filter.
2. After finding the loop bound of all path, we take the max of it, we would call this max loop bound as a critical loop.
3. Slack can be then found by subtracting other loop bounds by this critical loop bound.

# Analysis method
0. DFG can be used for this kind of analysis and calculation.
1. Now transform each delays into nodes.
- Compute the longest path from node i to node j s.t. the path does not contain any delay element.
2. Retransform the block diagram into nodes of delays, also arrows with the delays assigned to it.
3. If we cannot reach a certain node, we marked it as -1.
4. Then we can get the $L^1$ delay matrix
5. For 4th delay, we would like to compute all the way to $L^4$
6. To compute $L^2$ with $L^1$, $L^2_{ij} = max_k(L^1_{ik} + L^1_{kj})$
7. If you encounter -1, the path does not exist, so we dont have to consider it.
8. Then $L^3$ can be computed from $L^1$ and $L^2$
9. $T_{\infin} = max(L^1_{ii}/1,L^2_{ii}/2,L^3_{ii}/3,L^n_{ii}/n...)$ of each iteration can be found by analyzing the diagonal of the matrix L.
10. The $L^3$ means the maximum delays from a certain node to another node after passing 3 delays.
11. $L^n$ is the longest path from node to another node after 4 delays.

# Computing this bound
1. It originally cost $O(d^4)$, by exploiting the already used parts of your calculation, we can reduce it to $O(d^3logd)$
2. We use Bellman Fords's algorithm to calculate shortest path. Single source multiple output shortest algorithm.
3. We are trying to find the shortest path from 1 node to all other node.

# Bit width error
1. Must beware of the bit width error.
2. Use explicit signed number to indicate that it is signed value, s.t. auto sign extension can be made by the synthesis tool.

# Maximum Cycle mean algorithm
1. To calculate maximum cycle, multiply -1 to all weights.
2. S.t. we can create a searching maximum algorithm use minimum algorithm then multiply negaitive weight to it.
3. First multiply all the weights with -1, then find the minimum on this new loop delays, multiply by -1, it becomes the maximum.
