# <strong><font face = "Times New Roman"><p style="text-align: center;">HW5 QR Cordic Systolic Array design</p></font></strong>
## <font face = "Times New Roman"><p style="text-align: center;">VLSI DSP HW5</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">Shun-Liang Yeh, NCHU Lab612</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">5/18/2023</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">[Github Src Code](https://github.com/sicajc/VLSI_DSP_Notes_HW_Project/tree/main/hw5)</p></font>

<font face = "Times New Roman">

# INDEX
1. [Design Specification & Goal](#i-design-specification-and-goal)
2. [QR Decomposition & QR Cordic Algorithm](#ii-qr-decomposition--qr-cordic-algorithm)
3. [Fixed-Point Analysis](#iii-fixed-point-qr-cordic-design)
4. [Testbench & Golden Model Generation](#iv-testbench--golden-model-generation)
5. [QR Systolic Array Derivation](#v-qr-cordic-hardware-design)
6. [QR Cordic Hardware Implementation](#vi-hardware-implementation)
7. [Simulation Result](#vii-simulation-result)
8. [Acknowledgements](#viii-acknowledgement)
9.  [References](#ix-references)

# I. Design Specification and Goal
## Problem

<p align="center">
  <img src="./../img/problem1.jpg" width="500" heigh ="500">
</p>

- Goal is to design a hardware QR factorization module, capable of generating the Q matrix and R matrix for a given NxN A matrix, i.e. A = QR

<p align="center">
  <img src="./../img/problem2.jpg" width="500" heigh ="500">
</p>

- Using the above QR factorization scheme we can get our Q & R matrix through a series of givens rotations, just like what we did in HW1

<p align="center">
  <img src="./../img/problem_structure_of_design.jpg" width="500" heigh ="500">
</p>

- The systolic array structure is listed above, left triangular PE arrays calculate the R matrix while right hand side calculate the Q matrix.

<p align="center">
  <img src="./../img/hardware_design_guidelines_1.jpg" width="500" heigh ="500">
</p>

<p align="center">
  <img src="./../img/hardware_design_guidelines_2.jpg" width="500" heigh ="500">
</p>

- As suggested, each PE should calculate their result using only 4 cycles, where 3 cycles are used for rotation and the last cycle used for the multiplication of K constants.


<p align="center">
  <img src="./../img/problem_IO.jpg" width="500" heigh ="500">
</p>

- Input is an 8-bit integer, value between 128~ -127, while we have to output the Q & R matrices in 12-bit outputs.

<div style="page-break-after: always;"></div>

# II. QR Decomposition & QR Cordic Algorithm
## QR Decomposition
<p align="center">
  <img src="./../img/QR_algorithm.jpg" width="500" heigh ="300">
</p>

- According to the algorithm provided within the handout, we can generate the matlab QR algorithm model with slight modification.

<p align="center">
  <img src="./../img/qr_decomposition_double.png" width="500" heigh ="300">
</p>

- The algorithm is modified to allow it for computing the Q and R matrices.

<div style="page-break-after: always;"></div>

## The Cordic Algorithm
<p align="center">
  <img src="./img/../../img/cordic_basics.jpg" width="500" heigh ="300">
</p>

<p align="center">
  <img src="./../img/iterative_cordic.jpg" width="500" heigh ="300">
</p>

- The basic idea is trying to rotates an (x,y) vector to (x',y') using the cosine and sine function, by approaching the desire angle iteratively. Approaching the desired angle in a number of iterations.

<p align="center">
  <img src="./../img/cordic_rotation.jpg" width="500" heigh ="300">
</p>

- After Understanding the Cordic Algorithm, one can try to code it out in matlab for verification.
## Rotation Mode
<p align="center">
  <img src="./../img/kappa.jpg" width="500" heigh ="300">
</p>

- The correct K must be found for the correct iteration numbers, for our case, we have to find K_12. Thus we have to first calculation what K_12 is.

<p align="center">
  <img src="./../img/cordic_algorithm_1.jpg" width="500" heigh ="300">
</p>

- Above is the pseudoCode for cordic rotation mode, we can implement it in matlab code below.

<p align="center">
  <img src="./../img/cordic_rotation_mode_normal.png" width="500" heigh ="300">
</p>

- Rotation mode rotates the vector (x,y) by a certain angle to another new vector (x',y').

- The normal rotation mode uses a look up table to search for the angle needed for each iteration, above implements the cordic psuedoCode in matlab.

<div style="page-break-after: always;"></div>

## Vector Mode
<p align="center">
  <img src="./../img/cordic_vector_mode_normal.png" width="500" heigh ="300">
</p>

- The normal Vector mode also uses a look up table for approaching desired angle, however, the condition for rotation differs from the one presented in rotation mode. Simply changing the condition allows for conversion from rotation mode into vector mode.

- However, the above two implementation is not optimized for hardware design, since a huge LUT must be stored to provide the angle. Also, the rotation mode has to wait for the angle produced by vector mode which is a waste of time. Consequently, some optimization must be performed on the algorithm above.

# Optimizing Cordic Algorithm
<p align="center">
  <img src="./../img/problem_structure_of_design_opt.jpg" width="500" heigh ="300">
</p>

- Due to the hardware structure provided above , we notice that the vector mode(gray node) in red box has to rotates the same amount of degree as other rotation mode(white node), thus we can further optimize by simply propogate the direction vector generated by Vector Mode to other Rotation Mode.

## Optimized Vector Mode
<p align="center">
  <img src="./../img/cordic_vector_mode_optimized.png" width="500" heigh ="300">
</p>

- Notice that now we does not need an LUT to store the angle alpha. However, we still need to send out the direction vector out such that the rotation mode rotates as vector mode did. Thus Vector Mode simply generates the direction of rotation. Since we do this in a Givens Rotation manner, we call this mode Givens Generation(GG).

<div style="page-break-after: always;"></div>

## Optimized Rotation Mode
<p align="center">
  <img src="./../img/cordic_rotation_mode_optimized.png" width="500" heigh ="300">
</p>

- Rotation mode receive the direction vector generated by vector mode to rotates the (x,y) vector to the desired (x',y'). Since we do this in a Givens rotation manner, we call this mode Givens Rotation(GR).

<div style="page-break-after: always;"></div>

## Optimized QR Cordic Algorithm
<p align="center">
  <img src="./../img/qr_cordic.png" width="400" heigh ="300">
</p>

- Thus we can change the original QR algorithm into the QR Cordic Algorithm by simply replace the location where angle must be generated and where coordinates (x,y) must be calculated.
- Calculate angle, uses vector mode. Calculate vector uses Rotation mode.
- After we obtained the Correct Cordic Algorithm, we have to convert it into fix-point design.

<div style="page-break-after: always;"></div>

# III. Fixed-point QR Cordic Design
## Fixed point representation
<p align="center">
  <img src="./../../hw3/report/img/fixed_point_representation.jpg" width="500" heigh ="300">
</p>

<p align="center">
  <img src="./../../hw3/report/img/fixed_point_mult.jpg" width="500" heigh ="300">
</p>

- Fixed point representation is less expensive and easy to implement in hardware design. For more info please refer to HW3 DWT fixed point design.

## Matlab Fixed-Point Designer

<p align="center">
  <img src="./../../hw3/report/img/matlab_fixed_point_designer.jpg" width="400" heigh ="300">
</p>

- Using the matlab fixed-point designer I can convert the original QR cordice algorithm into a fixed point one, then find the best fixed point word length and fraction length for my design to meet the criterion.

<div style="page-break-after: always;"></div>

# Criterion Delta
<p align="center">
  <img src="./../img/delta_error.jpg" width="400" heigh ="300">
</p>

- The R matrix generated by fixed point algorithm must not be more than 1% error compared to the double precision R matrix. rij is the R matrix element calculated through double precision. rij_hat is the R matrix element calculate through fixed point algorithm.

- Since the input matrix is 8 bits integers, output matrices are 12 bits for both R & Q. We have 8 variables to search. The partial calculation word length and fraction length for both R & Q. Also the output fraction length for both R & Q. Also the word length and fraction length for K constant.

## Tester for fixed point algorithm

<p align="center">
  <img src="./../img/main_driver_3_checker.png" width="400" heigh ="300">
</p>

- This is the driver algorithm to test the average delta by running through a random number of matrices. To see if the proposed fixed point length meets the criteria or not.

<div style="page-break-after: always;"></div>

## Fixed point Word Length & Fraction Length Result
<p align="center">
  <img src="./../img/word_length_fixed_point_result.jpg" width="500" heigh ="300">
</p>

<p align="center">
  <img src="./../img/delta_error_result.jpg" width="500" heigh ="300">
</p>

- The optimal word length and fraction length is found using the fixed point designer, and being tested using the delta error calculation.The result was tested by running through 1000 test cases for verification, notice that on average the result delta is within 1 percent, so this proposed fixed-point word length and fraction length meets the criteria.

<div style="page-break-after: always;"></div>

# IV. Testbench & Golden Model Generation
## Matlab testbench generation
<p align="center">
  <img src="./../img/main_driver_5_testbenches.png" width="500" heigh ="300">
</p>

- The following main loop generates A,Q,R patterns in matlab. Consist of qr_cordic_opt that is the fixed point algorithm we just derived. Send random matrix in to get the desired Q & R. Later write those result in binary format into the data.txt file. So that we can later read these data into the pseudoDRAM within the testbench.

<div style="page-break-after: always;"></div>

## Generation of A
<p align="center">
  <img src="./../img/pattern_matrix_in.jpg" width="200" heigh ="400">
</p>

- The input matrix A is written out in an column-major reversed scanned order, such that the design can receive the data in a much more efficient manner.

## Generation of R, Q

<p align="center">
  <img src="./../img/pattern_r_golden.jpg" width="200" heigh ="400">
</p>

- Both R matrix & Q matrix are written out to the dat file for comparision in testbench.

<div style="page-break-after: always;"></div>

## Testbench
<p align="center">
  <img src="./../img/testbench_main_loop.png" width="400" heigh ="300">
</p>

- The following is the testbench main loop for testing my circuit for a random number of test patterns. The reset_task resets the system, qr_feed_data_task feeds the value into circuit for consecutive 16 cycles. Later the testbench would wait for the out_valid signal to be raised. Checks the answer using the pseudoDRAM Q_GOLDEN & R_GOLDEN then delay in a random period of cycles, continue sending in new data into the circuits.

<div style="page-break-after: always;"></div>

# V. QR Cordic Hardware Design
## Single Assignment Form
<p align="center">
  <img src="./../img/SA_Form.jpg" width="1000" heigh ="300">
</p>

- We must first understand the Single Assignment form in the handout to understand how the suggested design is derived. We can notice that each nodes is a rotation of x,y. The result is then stored into nx,ny.

<p align="center">
  <img src="./../img/dg_node_calculation.jpg" width="150" heigh ="150">
</p>

- Each of this nodes, represents a calculation nodes, which forms the fundamental calculation for our 3 dimensional DG construction.
- We can draw out the correspondent dependence graph using this SA form. Thus perform further derivation for our systolic array.

<div style="page-break-after: always;"></div>

## QR Dependence graph
<p align="center">
  <img src="./../img/dg_graph.jpg" width="500" heigh ="150">
</p>

- The handout suggest a dependence graph which you can see is a pyramid like structure; however, this dependence graph is actually incorrect in a sense that the stacked k=2,3,4 should not be moving away from the i,j axes. The stacked k=2,3,4 should be move toward j axes. Otherwise, an incorrect DG might be created.

<p align="center">
  <img src="./../img/DG_Mapping_and_Correspondent.jpg" width="500" heigh ="150">
</p>

- a) is the Correct dependence graph, notice that the stacked k=2 is different than the stacked k=2 suggested in the handout, however, only by doing so we can created a reasonable DG.

- b) After performing the projection through d, we can get the triangular systolic array.

- c) Corresponent to k=1, which is the lowest part of our triangular systolic array DFG design.
- d) k=3 maps to the highest portion of the triangular systolic array DFG.
- e) Beware of the dg of k=4, since it is r44 in the R matrix, from the algorithm we know that, r44 is already created alongside with r34 in DG graph (1,4,3)=(i,j,k). Thus r44 would actually resides in the y value of DG node(1,4,3). As a result, k=4 is actually a redundant node thus can be removed.

- Note that Q matrices dependence graph can be derived in a similiar manner,thus trivial. Notice that k=4 is also redundent for Q because no rotation is needed to be performed for k=4 DG of Q. The derivation of dependence graph is left as an exercise for the reader.

## Scheduling & Correspondence of DG & DFG
<p align="center">
  <img src="./../img/DFG_NUMBER_MAPPING.jpg" width="500" heigh ="150">
</p>

- This is the DFG for our design. GG node is the Givens Generation nodes, generating the direction vector then the direction vector get propogated into the GR node which is the Givens Rotation nodes.

<p align="center">
  <img src="./../img/DG_Mapping_and_Correspondent.jpg" width="800" heigh ="150">
</p>


<p align="center">
  <img src="./../img/DG_Output_result.jpg" width="500" heigh ="150">
</p>

- The red r11 means that the result r11 would get produced at (1,1,1) node in the cycle 17 since its computation time is 13~16 cycles.
- The yellow number marked within the DG node specified when this node get executed. And after projection you can know exactly when and where this particular computation would take place within your systolic array.
- To mark the scheduling onto the DG, one must first obtained a systolic array design using the scheduling vector s=(-1 1 1).
- Then perform folding to extends the execution cycles of every node. Also at the same time, beware of the dependency when you try to perform folding.
- Specially noted that, each GR would execute for 2 cycles for the first time before they send their first value to the next layer. After sending their first value, they send their value once every clock cycle. This can be spotted within the dependence graph. This is important for the later design of our PE units.

<div style="page-break-after: always;"></div>

# VI. Hardware Implementation
## System Architecture
<p align="center">
  <img src="./../img/system_and_pattern.jpg" width="500" heigh ="300">
</p>

- The graph shows the system of Testbed, input matrix would be sent out from pattern.v to QR CORDIC. The QR CORDIC would send out_r & out_q data after they finish their computation. The testbench would compare the value with golden model during the output phase of the circuit.

<p align="center">
  <img src="./../img/Cordic_system.jpg" width="200" heigh ="200">
</p>

- The following is the detailed system architecture of QR CORDIC module. The input buffer is implemented for sending in the data into the Cordic systolic array architecture in the correct moment and the correct PEs. FIFO is implemented by pure shift registers. Later after the computation of QR, output would be send out to pattern through out_r and out_q registers.

<div style="page-break-after: always;"></div>

# Design of GG
## GG PE Block diagran
<p align="center">
  <img src="./../img/GG_PE.jpg" width="500" heigh ="300">
</p>

- This is the block diagram of Givens Generation Unit. valid_i signal is used to indicate when the GG starts its calculation. At the same time, one should send data through port aij. While calculating, GG generates the one cycle delayed rotation vector di alongside with the one cycle delayed rotates signal. Both of these signals get sent to GR units.

<div style="page-break-after: always;"></div>

## Structure of GG

<p align="center">
  <img src="./../img/GG_DETAILS.jpg" width="500" heigh ="500">
</p>

- Details of GG contains a sub-control counter indicating whether GG is rotating, working or multiplying K. When rotating, GG generates di from the cordic iters block. The final (r,0) value after rotation would replace the old (x,y), the result would be (0,r) = (x,y).

## Structure of iteration

<p align="center">
  <img src="./../img/GG_CORDIC_ITERS.jpg" width="500" heigh ="500">
</p>

- Each of this sub-block represents an iteration in cordic. The boundary condition of determining whether the input value is 0 must be handled. Each iter sub-block generates a correspondent di signal during rotation. And the shift amount for both shifter is determined by the number of block also the value of counter.

<div style="page-break-after: always;"></div>

# Design of GR
## GR PE block diagram
<p align="center">
  <img src="./../img/GR_PE.jpg" width="500" heigh ="300">
</p>

- Vector di is sent in alongside with rotates signal to start the rotation.
- di & rotation signal must also get propogate to the next GR for pipelined rotation.
- valid_i signal is sent in alongside with aij to tell GR when to start the computation.
- rij is sent out alongside with valid_o to allow the computation of higher dimension PEs from k=1 ~ k=2.
- Additional x,y ports allows debugging and easier value extraction after the whole computation.

<div style="page-break-after: always;"></div>

## Structure of GR

<p align="center">
  <img src="./../img/GR_DETAILS.jpg" width="500" heigh ="300">
</p>

- GR is different than GG in some aspects, first it receive each direction vector from the previous GG or GR. Secondly, it needs two multipliers for the update of x,y due to the fact that both (x,y) is needed for the next full rotation.
- The valid_o signal can only be sent after 2 full rotation, thus it is controlled by the Twice_f register. Indicating whether the PE has already rotates two full iterations or not.

## Structure of Iteration
<p align="center">
  <img src="./../img/GR_CORDIC_ITERS.jpg" width="500" heigh ="300">
</p>

- GR receive the direction vector from other PEs to rotates to its desired direction. Compare to GG, it does not need to generate the direction vector.

<div style="page-break-after: always;"></div>

# VII. Simulation Result

## GG timing waveform

<p align="center">
  <img src="./../img/gg0_r.jpg" width="1000" heigh ="600">
</p>

- a) Sends in the valid_i signal & value to tell GG starts working.
- b) 4 iterations of givens rotation result.
- c) Works for the next 4 consecutive cycles generating rotation direction d & the rotates signal to GR.
- d) This is actually not needed, simply used for debugging wire.
- e) The output final result of this PE.

## GR Timing Waveform

<p align="center">
  <img src="./../img/gr0_r.jpg" width="1000" heigh ="300">
</p>

- a) Sends in the valid_i signal & value to tell GG starts working.
- b) 4 cycles of computation, 12 iterations for generating the new x,y
- c) Generate valid_o only after two full rotations for the first time.
- d) After the first time generate valid_o after each full rotation.
- e) The output final result of this PE.

# Execution Cycle of a Pattern
<p align="center">
  <img src="./../img/cordic_timing_inputs.jpg" width="1000" heigh ="300">
</p>

- Data of Matrix A is sent in through 16 consecutive cycles.

<p align="center">
  <img src="./../img/simulation_result_consecutive_stage.jpg" width="1000" heigh ="300">
</p>

- This is the waveform of pattern No.35.
- a) The input stage
- b) The calculation stage where computation has been taken place. After the computation is done, output is being sent out to the output stage.
- c) Output R & Q is being sent out the the testbench and compare with the golden model in the next 16 consecutive clock cycles.

<p align="center">
  <img src="./../img/final_testbench_result.jpg" width="600" heigh ="300">
</p>

- After passing through 1000 patterns, total latency and average pattern latency is calculated. Notice that each QR takes 30 cycles to compute. While each consecutive QR algorithm takes 16 cycles due to the I/O limit. That is if we only have a single port, we must first read in and order the data for 16 cycles. Thus requires a 16 cyles latency for data reordering. This might be solved if we can have more bandwidth.



## Note
- During debug, a mysterious 1 bit error drove me crazy, I eventually found out that it is caused by the boundary condition when generating the direction vector.
- While debugging, expecting which value would be produced beforehead is a powerful method while debugging, this can only be achieved with the correct algorithm and the support of high level language.
- DG is important for systolic archtiecture derivation, one must trust math!
- Note when tuning for matlab fimath fixed point computation method, one should remember to use Floor and Full Precision calculation. Otherwise simulation mismatch might occurs.

# VIII. Acknowledgement

- I would like to ackowledge Prof. Huang for the design of the HW; also EECS undergraduate Chao Hsin-Tsai , EECS undergraduate Kuan-Ting Du, EECS graduate Shuan Yu Lin and my EECS graduate seniors Mo Shuan Kuma, Hun Rei Chang for their assistent throughout the research, design and implementation of this homework. Without them, this design cannot become a reality.

<div style="page-break-after: always;"></div>

# IX. References

[1] [ECE 4760, Adams/Land, Fixed Point arithmetic , Spring 2021](https://vanhunteradams.com/FixedPoint/FixedPoint.html)

[2] [Best Practices for Converting MATLAB Code to Fixed Point Using Fixed-Point Designer](https://www.youtube.com/watch?v=pXXNORqY1uU&t=1983s)

[3] [VLSI DSP 2023, Lecture Handouts, Ch7 Mapping Algorithms Onto Array Structures 5-54~5-60, Y.T Hwang](http://socdsp.ee.nchu.edu.tw/class/download/vlsi_dsp_102/day/Ch07_mapping.pdf)

[4] [EE 5324 – VLSI Design II , Kia Bazargan , University of Minnesota , Part IX: CORDIC Algorithms](http://socdsp.ee.nchu.edu.tw/class/download/vlsi_dsp_102/night/DSP/EE5324-CORDIC.pdf)

[5] [UMN EE-5329 VLSI Signal Processing Lecture-15 (Spring 2019),Systolic Architecture Design , Prof. Keshab Parhi](https://www.youtube.com/watch?v=RBvmsQaP04s&list=PLT1QAv48lhQKpQnhLroOgr-uJUmZ4WvKq&index=15)

[6] [2021_Spring_NCTU_ICLAB Lab03,Sudoku, Testbench and Pattern, mirkat1206](https://github.com/mirkat1206/2021_Spring_NCTU_ICLAB/tree/main/Lab03)

[7] [Rounding Numbers without Adding a Bias, Gisselquist Technology,LLC 2017](https://zipcpu.com/dsp/2017/07/22/rounding.html)
