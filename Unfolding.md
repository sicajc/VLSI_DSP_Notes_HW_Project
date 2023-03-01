# Unfolding
1. Generalization of parrallel processing (Loop unrolling)
2. Similar to loop unrolling.
3. Unfolding factor J = 3 meaning replacing each node from DFG you find with 3 replicated but different time series signals.
4. $A->A_0,A_1,A_2$ etc.....
5. 3 unfolded data flow graph, A_0 start sends signal 0,3,6,9. A_1 start sends signals 1,4,7,10
6. After determining the unfolding factor, we would need to redraw the DFG to analyze the system again.
7. Expanding them out to observe the system clearly.
8. The unfolded DFG can be obtained from the orignal DFG.
9. For a J-unfolded DFG, $T_{\infin}=JT_{\infin}$
10. The unfolded factor must be in match as the maximum common product with the iteration bound.

# Unfolding a digital filter
1. First assign the nodes.
2. Then draw out the flow graph, connecting the necessary components and arithmetic units together.
3. By drawing the DFG then consider the signal needed by each nodes, note the time must be considered to derive the correct delay for each weight of your vertex.
4. By marking the sequence to process on the node, unfolding graph can be derived more easily to prevent mistakes.