# <strong><font face = "Times New Roman"><p style="text-align: center;">HW4 Systolic Array Mapping & Mapping of Vector Quantization</p></font></strong>
## <font face = "Times New Roman"><p style="text-align: center;">VLSI DSP HW4</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">Shun-Liang Yeh, NCHU Lab612</p></font>
### <font face = "Times New Roman"><p style="text-align: center;">4/29 2023</p></font>

### <font face = "Times New Roman"><p style="text-align: center;">

# INDEX
1. [Dependence Graph Mapping](#dependence-graph-mapping)
2. [Problems & Solution](#problem--solution)
3. [References](#references)


# I. Dependence graph mapping
## Linear schedule Checking
<p align="center">
  <img src="./permissible_linear_schedule.jpg" width="400" heigh ="400">
</p>

- From the selected Scheduling Vector and Projection vector, check two conditions.
- Check whether the inner product of scheduling vector s and projection vector d is not equal to zero.
- Check whether the inner product of scheduling vector and every edges on DG is equal or greater then zero.

## Projection Procedure
<p align="center">
  <img src="./projection_procedure.jpg" width="400" heigh ="400">
</p>

- Select a suitable processor vector P s.t. the inner product of processor vector P and projection vector d is 0.

## Space time transform
<p align="center">
  <img src="./space_time_transform_1.jpg" width="400" heigh ="400">
</p>

<p align="center">
  <img src="./space_time_transform_2.jpg" width="400" heigh ="400">
</p>

- From the derived s , d , P derive a transform matrix T for the N-th dimension DG graph.

- Start mapping every edges on the dependence graph according to the transform matrix T to get its space-time mapping results.

- From the mapping results of N-1 space-time dimension, sketch the edges on this new transformed space according to the mapping results.

- For more step by step algorithmic mapping examples, I suggest watching the lecture by Parhi, the video link is in the references.

<div style="page-break-after: always;"></div>

# II. Problem & Solution
## Q1
### a)
<p align="center">
  <img src="./q1_a.jpg" width="500" heigh ="250">
</p>

<p align="center">
  <img src="./q1_ans.jpg" width="500" heigh ="250">
</p>

### b)
<p align="center">
  <img src="./q1_b.jpg" width="500" heigh ="250">
</p>

<p align="center">
  <img src="./q1_ans_b_1.jpg" width="500" heigh ="250">
</p>

<p align="center">
  <img src="./q1_ans_b_2.jpg" width="500" heigh ="250">
</p>



### c)
<p align="center">
  <img src="./q1_c.jpg" width="500" heigh ="250">
</p>

<p align="center">
  <img src="./q1_ans_c_1.jpg" width="500" heigh ="250">
</p>

<p align="center">
  <img src="./q1_ans_c_2.jpg" width="500" heigh ="250">
</p>

## Q2
<p align="center">
  <img src="./q2.jpg" width="500" heigh ="250">
</p>

<div style="page-break-after: always;"></div>

<p align="center">
  <img src="./q2_a.jpg" width="500" heigh ="250">
</p>

<p align="center">
  <img src="./q2_ans_a.jpg" width="500" heigh ="250">
</p>


<p align="center">
  <img src="./q2_b.jpg" width="500" heigh ="250">
</p>

<p align="center">
  <img src="./q2_c.jpg" width="500" heigh ="250">
</p>

<p align="center">
  <img src="./q2_ans_bc.jpg" width="500" heigh ="250">
</p>

<div style="page-break-after: always;"></div>

### Note
1. Though when deriving the high level architecture for systolic array, only the edges needed to be used, however; the schedule of inputs and outputs are also important during implementation.
2. While transforming from algorithm to DG, beware of the indices, also try to check whether the indices you assigned make sense by going through some examples.


# III. References

[1] [VLSI DIGITAL SIGNAL PROCESSING SYSTEMS DESIGN AND IMPLEMENTATION, CH7 Systolic Archtiecture design, Prof. Keshab Parhi, p189~p212](https://www.amazon.com/VLSI-Digital-Signal-Processing-Systems/dp/0471241865)

[2] [VLSI DIGITAL SIGNAL PROCESSING SYSTEMS DESIGN AND IMPLEMENTATION, CH7 Systolic Archtiecture design, exercises 11, Prof. Keshab Parhi, p215](https://www.amazon.com/VLSI-Digital-Signal-Processing-Systems/dp/0471241865)

[3] [UMN EE-5329 VLSI Signal Processing Lecture-15 (Spring 2019),Systolic Architecture Design , Prof. Keshab Parhi](https://www.youtube.com/watch?v=RBvmsQaP04s&list=PLT1QAv48lhQKpQnhLroOgr-uJUmZ4WvKq&index=15)

[4] [UMN EE-5329 VLSI Signal Processing Lecture-16 (Spring 2019),Systolic Architecture Design, Space-Time Mapping , Prof. Keshab Parhi](https://www.youtube.com/watch?v=dTynhUdydws&t=1622s)

[5] [Computer Architecture - Lecture 27: Systolic Arrays (ETH Zürich, Fall 2020), Prof. Onur Mutlu](https://www.youtube.com/watch?v=8zbh4gWGa7I&t=2161s)
