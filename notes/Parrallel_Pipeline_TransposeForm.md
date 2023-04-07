# Reducing critical paths
1. We can reduce it by exploting cutset.
2. Use transpose form.

# Transpose form
1. From signal flow graph, we can derive its transpose form.
2. Simply reverse the direction of the signal flow, replace x->y,y->x.
3. Note from DSP course, the circuit is equivalent to the orignal structure after this transformation.
4. The difference equation would stay the same!
5. The CRITICAL path can sometimes be reduced using this technique.
6. Then we can simply redraw the graph, to get a clearer view of our transformed circuit.
7. Summing note is the same as fan out node simply in different persepctive.

# Summing bits after additions and multiplications
1. a*b actually only need $w_b+w_b-1$ bits

# Transpose form drawback
1. You might need more area in increased D_ffs.
2. The problem of Fan out. The capacitive load becomes larger thus leads to larger area and power.

# Relieving it by using Hybrid form
1. Inputs can have less fan out, at the same time critical path is not that large.
2. Ways is by distributing the sum and multiplication and D_ffs into the upper portion of circuit and to the lower bottom of the circuit, instead of putting them all into the upper portion of the circuit. This is the architecture that is used in very high speed digital filter.
3. Fan out problem wants to be prevented!Otherwise, speed goes down.

# Interleaving transformations circuit
1. Using same datapath to interleave multiple computations.
2. An example would be we would like to use the same datapath for in-phase and quadrature phase computations.
3. Ways to do so
- Replace each dealays by M delays, M = level of interleaving
- Interleave the corresponding samples at the input.

# Communication perspective
1. Consider in-phase transform and quadrature transform.
2. So simply replace each delays by 2 delays. Since we have in-phase and quadrature phase.
3. Then send in (interleave the inputs) of in-phase signal and quadrature signals.
4. To analyze the circuit, use multiple clock cycle pipelined diagram
5. By first setting up the fanout and summing nodes of the circuit as node A,node B,node C....
6. Interleaving 2 time series in sequence.

# Switches(Mux)
1. 2l, 2l+1 means feeding signals in an odd even way.
2. 4l,4l+1,4l+2,4l+3 meaning feeding signals in a period of T=4
3. We can draw the switch to input the signals in time series.

# Reducig power consumption by pipelining
1. $i = cV_{dd}/T = k(V_{dd}-V_t)^{\alpha}$ the current due to VLSI technology. MOSFET
2. Thus $T = cV_{dd}/k(V_{dd}-V_t)^\alpha$
3. Now we want to reduce the supply voltage $V_{dd}$
4. $V_{dd}$ -> $\beta V_{dd}$, where $\beta < 1$ Meaning we would like to reduce the $V_{dd}$
5. Total power consumption $P_{total} = C_{total} V_{dd}^2 f$
6. $P_{total_pipe} = C_{total_pipe} V_{dd}^2f = \beta ^2 P_{total}$
7. Thus pipelining can actually be used to reduce the power consumption, also reduce the critical path capacitances. And thus reduce the ${V_dd}$
8. Capacitances on the critical path are reduces due to pipelining.
# Reduce power using Parrallel processing
1. Consider 3 parrallel datapath.
2. Reduce the clock frequency in total, $T_{clock} = 3T$, whole goal is to reduce the total clock speed. In parrallel processing $f$->$f/L$, L is the number of parrallelism.
3. $LT = c*\beta v_{dd}/k(\beta v_{dd}-v_t)^2$, L factor is used to reduce the clock frequency in total, thus power is reduced.

# Expander
1. Insert $x-1$ zeroes after each inputs. An upper arrow with $x$ and a number N.
2. Consider the Z-transform of the expander sequence.
3. Expander power the factor of Z-transform
4. I.e. $x(z) -> x(z^m)$ with an M-expander.

# Parrallel and pipelining arhitecture
1. Usually, chances of parrallism can be found by drawing out the sequences in different time line.
2. To build a series to parrallel converter, different sampling rate can be used for such implementation.
3. Due to the switch in different sampling rate, clock domain crossing is needed for such circuit.
4. Switches 4l+3 means a period T=4, and this is the 3rd sample of this period.
