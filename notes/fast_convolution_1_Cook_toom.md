# Fast convolution
1. We can represent FIR or IIR system using state-space representation.
2. Naming each nodes as a new x_i(n), i.e. x_1(n),x_2(n).....
3. In large system, this is how the computer solve for the transfer function
4. y(n) is the combinations of these predefined states.
5. This state representation can be written in matrix form.

# Cook-Toom Algorithm
1. The core is the lagrange interpolation, to find the closest function that approach a bunch of points.
2. Cook-toom algorithm consider an n-point sequence of system impulse response h={h1,h2,...hn} and L-point sequence x={x1,x2,...,x_l-1}. Linear convolution can be expresdded as polynomial multiplication as s(p) = h(p)x(p).
3. Thus the polynomial can be uniquely determined by their values.

1. Selecting the correct b_i, plug the b_i into h(b_i) and x(b_i)
2. Then compute s(b_i) = h(b_i)x(b_i)
3. Compute s(p) using lagrange interpolation.


# Use of signal flow graph
1. Signal flow graph is a great way of visualization complex math formula, and can be use as a representation before HW implementation. A more elegant way of representing circuits.
2.

## Goal
1. It can reduce the multiplication complexity by trading some of the mult with adders.