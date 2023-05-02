# Systolic array design.
## Single assignment form
0. From the algorithm spot the loops hidden inside.
1. Derive its single assignment code form from the algorithm
2. We definitely want the data to be reused and propogate through PEs. Localize DG design.
3. $y_{j}^{k}$ means the variable is assigned once at the y(j,k) index on the DG graph. All variables should has its node on the DG when you are expanding out the algorithm.
## DG Drawing.
1. DG derivation from math formula, it can be a graph of multidimensional nodes.
2. Four Fundamental vectors for mapping. $d$ projection, $e$ edges , $P$ processor allocation matric, $s$ scheduling vector.
3. 2 Criterions must be met, first $P^Td = 0$ also $s^Td\not ={0}$, also $<s,e> >= 0$.
4. To get the delay edges and how the processor would be mapped into construct a table and then map the edges you want to observe onto the table by performing inner product.

## I/O port mapping
1. From the transformation matrix you just derived, you can derive the correct I/O sequence to be send into the system.
2. $<s,d>$ is defined as pipeline period, which indicates period of the sequence.

## I/O interior mapping
1. To send in the data at the right time and right place, contour is drawn and extends out, perpendicular to the projection vector.
2. Within the I/O bound, you should add additional registers as delays to ensure data arrival in the correct time.

## Experience when deriving
0. We dont like spiral communication, so we usually keept output data pointing downward.
1. Seperate the FIR and IIR portion out when drawing DG for algorithm, later connecting them together.
2. Usually the signal that needs to be feedback should be of Forward Reccurrence, i.e. the output direction is pointing downwards.
3. Also note that we want REGULAR Dependence graph, PE should be kept as regular as possible.
4. When drawing DG of multi-dimensional, we would usually draw layer by layer to reduce complexity.
5. If you want ditribute DG for elements, you can project the DG parts by parts.
6. When projecting, you should make sure that you do not gets infinite PE, which is not permissible.
7. When drawing even more complex DG, first expands the equations, spots for output patterns, note we want the most recently produced output to be placed downward to realise feedback in DG.
8. DG node should be clearly specified after you derive the DG graph.

## Node drawing.
1. You can actually use different colours to indicate different path type. Like you can indicate odd clock path, even clock path and odd&even clock path using different color.
2. You can also indicate datapath wires using different colours, control path colours using different colours.
3. Mark the processing elements and registers with name or numbers to know where you are processing.
4. A timing diagram and life-cycle diagram can be derive to indicate how many registers can be saved.
5. Symmetry can be exploited when deriving DG.

## Multi-projection
1. Remove all delays, get instant graph, we would also want the delay D to be replaced by a multiple of tau time delays.
2. When deriving second projection, you can actually also use time-space projection scheme, however, the delays must be compensated by the contour like you have drawn.
3. After the projection, remember to add those delays back.
