# <strong><font face = "Times New Roman"><p style="text-align: center;">HW6 Retiming, Unfolding and Folding</p></font></strong>
## <font face = "Times New Roman"><p style="text-align: center;">VLSI DSP HW6</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">Shun-Liang Yeh, NCHU Lab612</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">6/09/2023</p></font>

<font face = "Times New Roman">

# INDEX
1. [Problem & Solution](#i-problem--solutions)
2. [References](#iv-references)

# I. Problem & Solutions
## Q1

<p align="center">
  <img src="./img/Q1.jpg" width="500" heigh ="500">
</p>

- Remember that you can do retiming and pipelining, not just simply perform piplining. The concept of pipelining feedforward cutsets and retiming feedback cutset is important.
- The art of retiming means moving the delays around the circuit, remember to draw out the retiming contour to ensure that you are doing the correct retiming.

<p align="center">
  <img src="./img/S__4841481.jpg" width="300" heigh ="500">
</p>


<div style="page-break-after: always;"></div>

## Q2
<p align="center">
  <img src="./img/Q2.jpg" width="500" heigh ="300">
</p>

<p align="center">
  <img src="./img/Unfolding_algorithm.jpg" width="600" heigh ="300">
</p>

### a) J=2
<p align="center">
  <img src="./img/dsp_vlsi_ans/q2_a_j2.jpg" width="300" heigh ="300">
</p>

### a) J=5
<p align="center">
  <img src="./img/dsp_vlsi_ans/q2_a_j5.jpg" width="200" heigh ="300">
</p>

### b) J=2
<p align="center">
  <img src="./img/dsp_vlsi_ans/q2_b_j2.jpg" width="200" heigh ="300">
</p>

### b) J=5
<p align="center">
  <img src="./img/dsp_vlsi_ans/q2_b_j5.jpg" width="200" heigh ="300">
</p>

- Unfolding algorithm can be used to achieve the minimal Sampling period, the iteration bound however cannot be changed using unfolding.
- If the iteration bound of the circuit is not an integer, unfolding the circuit might help achieve the minimal sampling period at the cost of more HWs.
- Dummy nodes can be added to simplify the process of Unfolding a circuit.

<div style="page-break-after: always;"></div>

## Q3
<p align="center">
  <img src="./img/Q3.jpg" width="600" heigh ="300">
</p>

### First perform Unfolding with J = 2
<p align="center">
  <img src="./img/S__4841480.jpg" width="300" heigh ="300">
</p>


### Perform the Retiming to achieve critical path of T = 6

<p align="center">
  <img src="./img/S__4841479.jpg" width="300" heigh ="300">
</p>

<div style="page-break-after: always;"></div>

## Q4

<p align="center">
  <img src="./img/Q4.jpg" width="500" heigh ="300">
</p>


<p align="center">
  <img src="./img/folding_prelimnary.jpg" width="300" heigh ="300">
</p>

<p align="center">
  <img src="./img/folding_edges.jpg" width="300" heigh ="300">
</p>

<div style="page-break-after: always;"></div>

### a)
<p align="center">
  <img src="./img/S__4841478.jpg" width="500" heigh ="300">
</p>

### b)
- By high level programming language, we can verify that all the permutations of the folding set is not valid.

<div style="page-break-after: always;"></div>

### c) d)
<p align="center">
  <img src="./img/Register_minimization_in_folding.jpg" width="500" heigh ="300">
</p>


<p align="center">
  <img src="./img/S__4841476.jpg" width="500" heigh ="300">
</p>

<div style="page-break-after: always;"></div>

### e)
<p align="center">
  <img src="./img/folding_of_filter.jpg" width="500" heigh ="300">
</p>

<p align="center">
  <img src="./img/folding_result_register_min.jpg" width="400" heigh ="300">
</p>

<div style="page-break-after: always;"></div>

### Note
1. While doing register minimization, remember to mark the Src Node, Destination node and their correspondent sets to simplify the operations of mapping.
2. Remember where the input and output ports are.
3. Switches are switche in time instance Nl+v
4. Tin and Tout might varies in different architecture.
5. When drawing the linear lifetime table, remember to draw until the next iteration starts to overlap with the past data.


# II. References

[1] [UMN EE-5329 VLSI Signal Processing Lecture-11 (Spring 2019),Folding Transformation of Data flow Graph , Prof. Keshab Parhi](https://www.youtube.com/watch?v=_XMtfQkcbtM&list=PLT1QAv48lhQKpQnhLroOgr-uJUmZ4WvKq&index=11)

[2] [UMN EE-5329 VLSI Signal Processing Lecture-10 (Spring 2019), , Unfolding of Data-Flow Graphs with Switches and Digit-Serial Design , Prof. Keshab Parhi](https://www.youtube.com/watch?v=nbxykpXfnps&list=PLT1QAv48lhQKpQnhLroOgr-uJUmZ4WvKq&index=10)

[3] [VLSI DSP 2023, Lecture Handouts, Ch8 Folding 8-5 ~ 8-38, Y.T Hwang](http://socdsp.ee.nchu.edu.tw/class/download/vlsi_dsp_101/night/DSP/Ch8_folding.pdf)

[4] [VLSI DSP 2023, Lecture Handouts, Ch6 Unfolding 7-4, Y.T Hwang](http://socdsp.ee.nchu.edu.tw/class/download/vlsi_dsp_102/night/DSP/Ch6_unfolding.pdf)
