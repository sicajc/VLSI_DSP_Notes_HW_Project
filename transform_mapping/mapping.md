# Mapping
1. For sequential algorithm, cannot express parrallelsim or data dependecy.

# Graph representation.
1. This helps us transform sequential representation to HW representation.
2. One technique is using Dependence graph representation to represent the whole behaviour of algorithm.
3. DFG is also used however, DFG is only used to represent the behaviour of 1 iteration.
4. DG is used extensively in systolic array design, which needs to show all the computation performed within the algorithm also the data dependecies hidden within the algorithm.
5. We usually represent the algorithm with time added into it for better DG conversion.
6. After drawing out DG, parrallelsim can be found and exploited. Any DG analyzer?
7. Block diagram, DG, DFG and SFG are used extensively in VLSI dsp system analysis and design.

# Drawing DG
1. First draw the axes of your varaible, for example (i,j) = (x,y) coordinates.
2. Adds the nodes or processing units onto the graph.
3. Connect the dots and then analyze the data flow.
4. Note each difference or position of a node can be represented by a vector!
5. Thus we can find a difference between two vectors, it is also a vector!
6. Thus any linear algebra technique can be used on thsi graph analysis.
7. When doing HW mapping, HW allocation and scheduling are important!
8. Then from the DG you can derive a variety of architecture.