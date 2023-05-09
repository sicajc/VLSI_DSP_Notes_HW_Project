function [x_result, y_result, angle] = cordic_rotation_mode(x, y, angle, iters_num)
    % Rotation mode
    % Description: Rotation mode using Linear rotation and multiplied by a constant K = 0.607252935 for stretching
    % Input:  vector (x,y) rotates it with the angle z
    % Output: vector (xcos(z),ysin(z))
    % Enables shift add multiply instead of calculation trigonemetric function
    % tan(a^i) = 2^(-i), thus tan(a^i) is simply shift.
    % Try to approach the desirable angle, we multiply the cos(a^i) only after the complete rotation.
    % Simply multiply K = 0.607252935 after the rotations. See if the angle difference approach to zero.

    alpha = [45, 26.565, 14.0362, 7.12502, 3.57633, 1.78991, 0.895174, 0.447614, 0.223811, 0.111906, 0.055953, 0.027977];
    K = 0.607252935;

    for i = 1:iters_num
        % Z is the current angle, and also the angle I want to shift toward to.
        if angle > 0
            x_new = x - bitsra(y, i - 1);
            y = y + bitsra(x, i - 1);
            x = x_new;
            angle = angle - alpha(i);
        else
            x_new = x + bitsra(y, i - 1);
            y = y - bitsra(x, i - 1);
            x = x_new;
            angle = angle + alpha(i);
        end

    end

    x_result = x*K;
    y_result = y*K;
end