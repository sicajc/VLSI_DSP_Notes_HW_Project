# Folding transformation
1. After unfolding, is it possible to fold the transformation back?
2. If we fold things back, many possible solutions exists.
3. An ordered folding set should be defined. $S_0 = {A_ij} \forall i,j$
4. N is the Folding factor = number of operations mapped onto the same HW resources.
5. The concept of folding ordered sets.
6. A very powerful technique to design time-multiplexing datapath.
7. From the retransform of system(unfolding) dataflow graph, we can design time-multiplexing datapath using folding technique.

# Mapping from DFG algorithm to HW
1. $U-> H_U$, $V->H_v$
2. lth iteration of node U is executed at ti e Nl+u
3. lth iteration of node V is executed at Nl+v by l+v
4. $U_l -> V_{l+w}$. l+w iterations of V is executed at N(l+w)+v
5. architecture data flow graph and algorithmic data flow graph.
6. Thus from node U to V, $H_U$ gets pipelined by u cycles then $D_F(U->V)$
7. The number of folded delays cannot be negatives.
8. However, sometimes the delay can be negative for a lot of architectures.

# Set notation
1. (S1|3) meaning it maps to folding set S1 and being the 3rd element of the folding set.

# To get to the folded architecture
1. We must make sure $D_f<0$ does not exists, but how to ensure that? Try to do retiming to prevent this from happening
## Retiming
1. Feasibility, constraint $r(U)-r(v)<=w(U->V)$
2. Sometimes from the folding constraint, the folded datapath might not be realizable.

## Folding constraints.
1. Also we would force the floor function if it is not an integer value.