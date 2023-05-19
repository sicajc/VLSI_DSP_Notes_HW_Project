# <strong><font face = "Times New Roman"><p style="text-align: center;">HW5 QR Cordic Systolic Array design</p></font></strong>
## <font face = "Times New Roman"><p style="text-align: center;">VLSI DSP HW5</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">Shun-Liang Yeh, NCHU Lab612</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">5/18/2023</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">[Github Src Code](https://github.com/sicajc/VLSI_DSP_Notes_HW_Project/tree/main/hw5)</p></font>

<font face = "Times New Roman">

# INDEX
1. [Design Spec & Goal]()
2. [QR Decomposition & QR Cordic Algorithm](#i-fixed-point-discrete-wavelet-filter-design)
3. [Fixed-Point Analysis](#ii-synthesis-result)
4. [Testbench & Golden Model Generation](#iii-acknowledgement)
5. [QR Systolic Array Derivation](#iii-acknowledgement)
6. [Design of Cordic GG & GR](#iii-acknowledgement)
7. [System Architecture](#iii-acknowledgement)
8. [Results](#iii-acknowledgement)
9. [Acknowledgements](#iii-acknowledgement)
10. [References](#iv-references)

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

## Optimized Rotation Mode
<p align="center">
  <img src="./../img/cordic_rotation_mode_optimized.png" width="500" heigh ="300">
</p>

- Rotation mode receive the direction vector generated by vector mode to rotates the (x,y) vector to the desired (x',y'). Since we do this in a Givens rotation manner, we call this mode Givens Rotation(GR).

## Optimized QR Cordic Algorithm
<p align="center">
  <img src="./../img/qr_cordic.png" width="500" heigh ="300">
</p>

- Thus we can change the original QR algorithm into the QR Cordic Algorithm by simply replace the location where angle must be generated and where coordinates (x,y) must be calculated.
- Calculate angle, uses vector mode. Calculate vector uses Rotation mode.
- After we obtained the Correct Cordic Algorithm, we have to convert it into fix-point design.


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

## Criterion Delta
<p align="center">
  <img src="./../img/delta_error.jpg" width="400" heigh ="300">
</p>

- The R matrix generated by fixed point algorithm must not be more than 1% error compared to the double precision R matrix. rij is the R matrix element calculated through double precision. rij_hat is the R matrix element calculate through fixed point algorithm.

- Since the input matrix is 8 bits integers, output matrices are 12 bits for both R & Q. We have 8 variables to search. The partial calculation word length and fraction length for both R & Q. Also the output fraction length for both R & Q. Also the word length and fraction length for K constant.

## Tester for fixed point algorithm

<p align="center">
  <img src="./../img/main_driver_3_checker.png" width="500" heigh ="300">
</p>

- This is the driver algorithm to test the average delta by running through a random number of matrices. To see if the proposed fixed point length meets the criteria or not.

## Result Fixed point Word Length and Fraction Length
<p align="center">
  <img src="./../img/word_length_fixed_point_result.jpg" width="500" heigh ="300">
</p>

<p align="center">
  <img src="./../img/delta_error_result.jpg" width="500" heigh ="300">
</p>

- The optimal word length and fraction length is found using the fixed point designer, and being tested using the delta error calculation.The result was tested by running through 1000 test cases for verification, notice that on average the result delta is within 1 percent, so this proposed fixed-point word length and fraction length meets the criteria.

# IV. Testbench & Golden Model Generation
## Matlab testbench generation
<p align="center">
  <img src="./../img/main_driver_5_testbenches.png" width="500" heigh ="300">
</p>

- The following main loop generates A,Q,R patterns in matlab. Consist of qr_cordic_opt that is the fixed point algorithm we just derived. Send random matrix in to get the desired Q & R. Later write those result in binary format into the data.txt file. So that we can later read these data into the pseudoDRAM within the testbench.

## Generation of A
<p align="center">
  <img src="./../img/pattern_matrix_in.jpg" width="300" heigh ="300">
</p>

- The input matrix A is written out in an column-major reversed scanned order, such that the design can receive the data in a much more efficient manner.

## Generation of R, Q

<p align="center">
  <img src="./../img/pattern_r_golden.jpg" width="300" heigh ="300">
</p>

- Both R matrix & Q matrix are written out to the dat file for comparision in testbench.

## Testbench
<p align="center">
  <img src="./../img/testbench_main_loop.png" width="500" heigh ="300">
</p>

- The following is the testbench main loop for testing my circuit for a random number of test patterns. The reset_task resets the system, qr_feed_data_task feeds the value into circuit for consecutive 16 cycles. Later the testbench would wait for the out_valid signal to be raised. Checks the answer using the pseudoDRAM Q_GOLDEN & R_GOLDEN then delay in a random period of cycles, continue sending in new data into the circuits.

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

- This is the DFG for our design. GG node is the Givens Generation nodes, generating the direction vector then the direction vector get propogated into the GR node which is the Givens Rotation noes.

<p align="center">
  <img src="./../img/DG_Mapping_and_Correspondent.jpg" width="500" heigh ="150">
</p>


<p align="center">
  <img src="./../img/DG_Output_result.jpg" width="500" heigh ="150">
</p>

- The red r11 means that the result r11 would get produced at (1,1,1) node in the cycle 17 since its computation time is 13~16 cycles.
- The yellow number marked within the DG node specified when this node get executed. And after projection you can know exactly when and where this particular computation would take place within your systolic array.
- To mark the scheduling onto the DG, one must first obtained a systolic array design using the scheduling vector s=(-1 1 1).
- Then perform folding to extends the execution cycles of every node. Also at the same time, beware of the dependency when you try to perform folding.
- Specially noted that, each GR would execute for 2 cycles for the first time before they send their first value to the next layer. After sending their first value, they send their value once every clock cycle. This can be spotted within the dependence graph. This is important for the later design of our PE units.

# Design of GG & GR
## GG
<p align="center">
  <img src="./../img/GG_PE.jpg" width="500" heigh ="300">
</p>

- This is the block diagram of Givens Generation Unit. valid_i signal is used to indicate when the GG starts its calculation. At the same time, one should send data through port aij. While calculating, GG generates the one cycle delayed rotation vector di alongside with the one cycle delayed rotates signal. Both of these signals get sent to GR units.

<p align="center">
  <img src="./../img/GG_DETAILS.jpg" width="700" heigh ="600">
</p>

- Details of GG contains a sub-control counter indicating whether GG is rotating, working or multiplying K. When rotating, GG generates di from the cordic iters block. The final (r,0) value after rotation would replace the old (x,y), the result would be (0,r) = (x,y).

<p align="center">
  <img src="./../img/GG_CORDIC_ITERS.jpg" width="700" heigh ="600">
</p>

- Each of this sub-block represents an iteration in cordic. The boundary condition of determining whether the input value is 0 must be hanndled. Each iter sub-block generates a correspondent di signal during rotation. And the shift amount for both shifter is determined by the number of block also the value of counter.

<p align="center">
  <img src="./../img/gg0_r.jpg" width="700" heigh ="600">
</p>



### Down Sampler
<p align="center">
  <img src="./img/downSampler.png" width="500" heigh ="300">
</p>


### UpSampler

<p align="center">
  <img src="./img/upSampler.png" width="500" heigh ="300">
</p>

<div style="page-break-after: always;"></div>


### PSNR
<p align="center">
  <img src="./img/psnr.png" width="500" heigh ="300">
</p>


### DWT octave
<p align="center">
  <img src="./img/dwt_octave.png" width="800" heigh ="300">
</p>

<div style="page-break-after: always;"></div>

### IDWT octave

<p align="center">
  <img src="./img/idwt_octave.png" width="400" heigh ="300">
</p>


### Main driver
<p align="center">
  <img src="./img/main_driver.png" width="300" heigh ="300">
</p>


<div style="page-break-after: always;"></div>

### Data Type
<p align="center">
  <img src="./img/filter_data_Type.png" width="500" heigh ="300">
</p>

<div style="page-break-after: always;"></div>

# Result
## Fixed Point statistical report
### Fixed Point Width length and fraction length

<p align="center">
  <img src="./img/fix_point_table.jpg" width="300" heigh ="300">
</p>


### Filter Coefficients
<p align="center">
  <img src="./img/filter_coef.jpg" width="300" heigh ="300">
</p>

### Level 1 output
<p align="center">
  <img src="./img/lv1_output_graph.jpg" width="300" heigh ="300">
</p>

- In the fixed point designer, it tells you the range for your calculation also suggest you the length of the fix-point and fraction length.

<div style="page-break-after: always;"></div>


### Level 2 output

<p align="center">
  <img src="./img/lv2_output_graph.jpg" width="300" heigh ="300">
</p>

### Level 3 output

<p align="center">
  <img src="./img/lv3_output_graph.jpg" width="300" heigh ="300">
</p>

## Original image

<p align="center">
  <img src="../../hw2/img/filtered_result/original.jpg" width="300" heigh ="300">
</p>

<div style="page-break-after: always;"></div>


## DWT result
<p align="center">
  <img src="../../hw2/img/filtered_result/dwt_Result.jpg" width="450" heigh ="450">
</p>

## Restored image
<p align="center">
  <img src="./img/fix_point_result.jpg" width="450" heigh ="450">
</p>

<div style="page-break-after: always;"></div>

### PSNR
<p align="center">
  <img src="./img/psnr_result.jpg" width="600" heigh ="500">
</p>

- The result is close to 50db, tuning any further result in a distortion or making the restoration lower than 50db.

### Note
1. Fix point designer is a powerful tool for analysis.
2. High frequency components are important for image reconstruction, thus the length for the filter coefficients are important for high-frequency restoration.
3. The low frequency components are the most important for main image reconstruction.
<div style="page-break-after: always;"></div>


# II. Synthesis Result
- Synthesize the word length for adders and filter's registers results according to the matlab simulation into gate-level circuit.

# Multipler

<p align="center">
  <img src="./img/mult.png" width="450" heigh ="450">
</p>

<p align="center">
  <img src="./../verilog/synthesis_result/mult_area.jpg" width="450" heigh ="450">
</p>

<div style="page-break-after: always;"></div>


# Adder
<p align="center">
  <img src="./img/adder.png" width="450" heigh ="450">
</p>

<p align="center">
  <img src="./../verilog/synthesis_result/adder_area.jpg" width="450" heigh ="450">
</p>

<div style="page-break-after: always;"></div>


# Registers

<p align="center">
  <img src="./img/register.png" width="450" heigh ="450">
</p>


## lv1
<p align="center">
  <img src="./../verilog/synthesis_result/register_lv1_area.jpg" width="450" heigh ="450">
</p>

<div style="page-break-after: always;"></div>

## lv2
<p align="center">
  <img src="./../verilog/synthesis_result/register_lv2_area.jpg" width="450" heigh ="450">
</p>

## lv3
<p align="center">
  <img src="./../verilog/synthesis_result/register_lv3_area.jpg" width="450" heigh ="450">
</p>


<div style="page-break-after: always;"></div>


# III. Acknowledgement

- I would like to ackowledge Prof. Huang for the design of the HW; also EECS undergraduate Chao Hsin-Tsai , EECS undergraduate Kuan-Ting Du, EECS graduate Shuan Yu Lin and my EECS graduate seniors Mo Shuan Kuma, Hun Rei Chang for their assistent throughout the research, design and implementation of this homework. Without them, this design cannot become a reality.

# IV. References

[1] [ECE 4760, Adams/Land, Fixed Point arithmetic , Spring 2021](https://vanhunteradams.com/FixedPoint/FixedPoint.html)

[2] [Best Practices for Converting MATLAB Code to Fixed Point Using Fixed-Point Designer](https://www.youtube.com/watch?v=pXXNORqY1uU&t=1983s)

[3] [VLSI DSP 2023, Lecture Handouts, Ch5 Mapping Algorithms Onto Array Structures 5-54~5-60, Y.T Hwang]()

[4] [EE 5324 – VLSI Design II , Kia Bazargan , University of Minnesota , Part IX: CORDIC Algorithms](http://socdsp.ee.nchu.edu.tw/class/download/vlsi_dsp_102/night/DSP/EE5324-CORDIC.pdf)

[5] [UMN EE-5329 VLSI Signal Processing Lecture-15 (Spring 2019),Systolic Architecture Design , Prof. Keshab Parhi](https://www.youtube.com/watch?v=RBvmsQaP04s&list=PLT1QAv48lhQKpQnhLroOgr-uJUmZ4WvKq&index=15)

[6] [2021_Spring_NCTU_ICLAB Lab03,Sudoku, Testbench and Pattern, mirkat1206](https://github.com/mirkat1206/2021_Spring_NCTU_ICLAB/tree/main/Lab03)

[7] [Rounding Numbers without Adding a Bias, Gisselquist Technology,LLC 2017](https://zipcpu.com/dsp/2017/07/22/rounding.html)
