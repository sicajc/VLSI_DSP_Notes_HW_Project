from typing import Tuple
ITERS_NUM = 12
def cordic_vector(x:float,y:float,angle:float,iters_num:int=ITERS_NUM) -> Tuple:
    """Cordic vectoring mode

    Args:
        x (float): x coordinate of vector
        y (float): y coordinate of vector
        angle (float): The angle of this vector w.r.t x-axis
        iters_num (int): The number of iterations for cordic algorithm.

    Returns:
        Tuple: The rotated new x,y coordinates
    """
    x_rot,y_rot,angle = 0,0,0

    alpha = [45, 26.565, 14.0362, 7.12502, \
             3.57633, 1.78991, 0.895174, 0.447614, 0.223811, 0.111906, 0.055953, 0.027977]

    for i in range(ITERS_NUM):
        if x*y >0:
            x_rot = x + y/2
            y     = y - x/2
            x     = x_rot
            angle = angle + alpha[i]
        else:
            x_rot = x - y/2
            y     = y + x/2
            x     = x_rot
            angle = angle - alpha[i]

    x_rot = x
    y_rot = y

    return (x_rot,y_rot)


def cordic_vector_unrolled(x:float,y:float,angle:float,iters_num:int=ITERS_NUM) -> Tuple:
    """Cordic vectoring mode

    Args:
        x (float): x coordinate of vector
        y (float): y coordinate of vector
        angle (float): The angle of this vector w.r.t x-axis
        iters_num (int): The number of iterations for cordic algorithm.

    Returns:
        Tuple: The rotated new x,y coordinates
    """
    x_rot,y_rot,angle = 0,0,0

    alpha = [45, 26.565, 14.0362, 7.12502, \
             3.57633, 1.78991, 0.895174, 0.447614, 0.223811, 0.111906, 0.055953, 0.027977]

    # Implement this using binary cnts, requires registers to hold values over iterations
    for i in range(2):
        for j in range(6): # Implement this through combinational unrolling.
            idx = i*6+j
            if x*y >0:
                x_rot = x + y/2
                y     = y - x/2
                x     = x_rot
                angle = angle + alpha[idx]
            else:
                x_rot = x - y/2
                y     = y + x/2
                x     = x_rot
                angle = angle - alpha[idx]

    x_rot = x
    y_rot = y

    return (x_rot,y_rot)


x = 1
y = 1

x_rot , y_rot = cordic_vector(x=1,y=1,angle=45,iters_num=ITERS_NUM)
print(f"({x},{y}) rotates to ({x_rot},{y_rot})")

x_rot , y_rot = cordic_vector_unrolled(x=1,y=1,angle=45,iters_num=ITERS_NUM)
print(f"({x},{y}) rotates to ({x_rot},{y_rot})")
