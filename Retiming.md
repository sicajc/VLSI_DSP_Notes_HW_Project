# Retiming
## Art of moving delays around.
1. Ideas of node retiming can be generalized into cutset retiming.
2. Valid cutset retiming means we can remove the $ith$ delays of a certain cutset input, then attach  $ith$ delay to the output. We call this a valid retiming.
3. DFG graph and graph algorithm concepts are used extensively here.
4. Remove incoming edge delays by 1, add 1 outgoing delay to output edge.

# Pipeling v.s. Retiming.
0. Moving existing delays around a feedbackward cutset(Retiming), pipelining introduces delays around a feedforward cutset.
1. Pipeling algorithm is consulted if we want to perform operation on feed-forward cutset
2. Retiming is consulted if we want to perform opeartion on feed-back cutset.
3. Retiming does not change number of delays in a certain loop.
4. We must make sure that the delay in every loop must remain the same.
5. Retiming algorithm should not change the loop bound and the number of delays in each loop.
6. Retiming reduces critical path by not changing latency.
7. Pipeling reduces cirtical path by increasing latency.
> In retiming, feedbackback cutset is consulted, in pipelining feedforward cutset is consulted.


# Retiming algorithm
1. Retiming variable i needs to be found to perform valid retiming on the circuit.
2. You can verify that the sum of all delays conserved after retiming, so the loop bound and $T_{\infin}$ is preserved.
3. $w_r(U->V)$ = delays from node U to V.


# How retiming can lead to equivalent data-flow graph?
0. Consider a FIR filer. What is the tranposed form and direct form relationship between Retiming technique?
1. Associativity property of add.
2. By rearranging the adders position then apply retiming to the circuit, we can restructure the circuit.
3. We can thus get the transposed data broadcasting form.
4. We can also derive hybrid form from retiming technique.

# Hybrid form
![Hybrid_form](pictures/hybrid_form_from_retiming_cutset.png)
0. Consider an FIR filter, find its tranposed form, direct form and its hybrid form.
1. Instead of retiming on all delays, retiming only on the partial part of circuit.
2. Associativity property of arithmetics are also exploited.

# Reducing critical path using Retiming technique.
![](pictures/2_order_biquad_iir_filter.png)
![](pictures/2_order_biquad_iir_filter_retimed.png)
1. Consider a biquad IIR filter, try to apply pipeling technique and retiming technique onto it to reduce the critical paths.
2. We can actually move registers into multiplications after analysis.
3. We can apply pipeling technique and retiming technique together s.t. we can reduce the critical path.

# Cutset retiming
1. We try to draw the cutset boundary, then the input register should be equal to the output registers before and after retiming.
2. Retiming cutsets used drawn to find where the registers we should insert after retiming.
3. Combining retiming and pipelining techniques, circuit architecture critical path can be reduced.
4. Retiming does not change number of delays in a path that used to be.
5. However, path delays get changed.

# Interleaving retiming
![](pictures/biquad_filter_retiming_example.png)
Consider 3-way interleaving
1. Now we want to process 3 time series with the same datapath at the same time period.
2. Multiple cutsets can be drawn as long as it obeys the input output boundary rule.
3. Retiming can greatly reduce critical path.
4. Note sample period is the time for system to finish process 1 sample, thus $x_0,x_1$ and so on thus if it is interleaved, the sample period increases by a factor of N-way interleaving factor N.
5. Usually pipeline arithmetic units are implemented for DSP  algorithm to allow dc or retiming technique of the circuit to be used.
6. Redo the 3-way interleaving biquad filter example to achieve a clock period of $5/6$
7. When solving problems, multiple delays within a delay block can be seperated to further utilize the techniques.
# Note whenever you introduce pipelining cutset
1. If you are sampling the sequence in an odd even manner, after inserting the pipeline, original sample even becomes odd, odd becomes even. This must be realised and noticed!

# Tips when doing retiming
1. First spot the critical path, then imagine where should we add the delay.
2. Draw the possible delays onto the graph.
3. We can actually simply expand the delay out onto a loop, the result would still be valid.
4. Redistribute the delays onto the feedback loop within a circuit is a valid operation.
5. Then consider the compound loop, the delays must still stay the same before and after the retiming. That is the sum of the delays within each subloops MUST STAY THE SAME. Before and after retiming!
6. Note if we were to retime the circuit by hand, every loop bound must remains the same before and after retiming.
7. Usually the retiming problem is solved by program, however, pipelining have to be inserted by human hands.
8. Node conservation and cutset conservation of input output registers must be conserved!
9. The arithmetic units can be selected in a way that allows pipelining.
10. Dummy delays can be introduce at the input output to help analyze the system.
11. So when designing system, add the correct number of delays to the circuit then allows the synthesis tool to perform retiming on the system to possibly yield the best results.
12. Associatity properties can be exploited combine with retiming cutset, an optimized circuit can be derived.
