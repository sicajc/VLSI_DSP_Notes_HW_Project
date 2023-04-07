# Design flow
1. Understand fix-point representation and its tradeoff in rounding errors.
2. Change the original DWT into variable fixed-point representation.
3. Test it, do a sanity-check and check with others.
4. Specify the constraints and weight of the fitness function for my setup.
5. Learn and use GA solver provided by Matlab toolbox.
6. From the derived fix-point word-length, build the adders, multipliers and registers out using design compiler.