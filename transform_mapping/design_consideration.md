1. Profiling in CNN: Used to analyze the data usage of each layers, for future analysis, Agile CNN used this kind of approach.
2. In architectural view, simply selecting which prcesion of fixed point representation to process the data of architecture is a mess, however, someone must do it.
3. The main problem of transforming an architecture is limited mainly by its resource limitations and memory bandwidth.
# dRAM
-  dram IS SLOW SINCE IT USUALLY NEEDS TO GO THROUGH THE PROCESSS OF PRECHARGE -> BURST -> REFRESH -> BURST -> REFRESH STATE.
-  Usual memory cannot support this kind of large bandwith for cnn processing. So something must be done.
-  Usually when doing image processing in CNN, 8-bit representation is enough.
-  Quantization aware training is important when desiging architecture, which would influence numerical performance.

# Quantization
1. Poles and zeros of a transfer function can be affected by quantization, the roots of poles will be affected dramatically if you selecet different quantization scheme which leads to huge change in stabibility.
2. Stabibility is $|w_p|<1$ , also note that since FIR is all-zeros design, it is used extensively in practical design.
3. When designing filters, pole-zero cancellation technique can be utilize to cancel poles and zeroes out which leads to better stability.

# Floating point v.s. fixed point
1. The reason using floating point is due to its dynamic range, however. some application does not need this kind of dynamic range. According to application, prceision and dynamic range must be selected properly.
2. Fixed point is more ammendable is HW design,
3. The Window size: that is where the decimal point lies is crucial when designing HW.
4. For most DSP algorithm, fixed point decimal point matters, this should be a great consideration when you are simulating the behaviour of algoirthm. Extensive simulation should be performed about this before converting it into HW.
5. If this kind of simulation with fixed point is performed, it is called bit-true algorithm format. I.e. we consider the effect of precision and data size when we are in algorithmic level.

# Implementating Arithmetic units. sinx cosx etc...
- 4 approaches are usually used.
1. LUT (Size needed to be considered when using this.) Like 8-bit multiplier can be implemented using LUT.
2. Taylor series, simply build a polynomial equvalence class in HW.
3. Iterative algorithm approximation.
4. CORDIC Algorithm, the design using only add and shifter only, which is simple but trading time for area.
5. Note Vendoes IP might influence portability of your design.

# Recursive algorithms and adaptive algorithm
1. These type of algorithm cannot be pipelined.
2. Pipeling increase the latency of a signal, however, if the signal flows only from 1 way to another, this is actually not important.

# Performing pipeling to recursive algorithm
1. Look ahead transform -> Leads to numerical stability errors.
2. Algorithm relaxation -> Change the delays of needed feedback signals. Make it delay longer.
