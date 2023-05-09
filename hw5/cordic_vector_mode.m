function [x_result, y_result, angle] = cordic_vector_mode(x, y, angle, iters_num)
    % Vectoring mode
    % Description: Vectoring mode uses linear rotation s.t. y approach to 0 iteratively
    % Input:  vector (x,y) rotates it with the angle z
    % Output: Value after rotation (x,y) also the angle of tan(y/x)
    % Goal is trying to nullify y accumulating the angle when rotating.
    alpha = [45, 26.565, 14.0362, 7.12502, 3.57633, 1.78991, 0.895174, 0.447614, 0.223811, 0.111906, 0.055953, 0.027977];

    for i = 1:iters_num
        % Z is the current angle, and also the angle I want to shift toward to.
        if -sign(x * y) > 0
            % Because in vector mode, di is defined as -sign(x,y), deriving this from the rotation matrix.
            % Since counterclockwise rotation is of (c  s) however, my version uses clockwise rotation, thus should be (c -s)
            %                                       (-s c),                                                            (s  c).
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

    x_result = x;
    y_result = y;
end