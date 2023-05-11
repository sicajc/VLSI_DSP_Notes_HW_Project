function [x_result, y_result, angle] = cordic_vector_mode(x, y, angle, iters_num,T)
    % Vectoring mode
    % Description: Vectoring mode uses linear rotation s.t. y approach to 0 iteratively
    % Input:  vector (x,y) rotates it with the angle z
    % Output: Value after rotation (x,y) also the angle of tan(y/x)
    % Goal is trying to nullify y accumulating the angle when rotating.
    alpha = [45, 26.565, 14.0362, 7.12502, 3.57633, 1.78991, 0.895174, 0.447614, 0.223811, 0.111906, 0.055953, 0.027977];

    % Turning into fixed point
    alpha = cast(alpha,'like',T.lut_coef);
    x_result = cast(x,'like',T.x_output);
    y_result = cast(y,'like',T.y_output);
    angle    = cast(angle,'like',T.theta_output);
    x_new    = cast(x,'like',T.x_output);

    for i = 1:iters_num
        % Z is the current angle, and also the angle I want to shift toward to.
        if sign(x * y) > 0
            % Since it is at the first dimension, we shoudl shift in a clockwise manner.
            % Since we are trying to obtain the angle, we must add when we are rotating.
            x_new(:) = x + bitsra(y, i - 1);
            y(:)     = y - bitsra(x, i - 1);
            x(:) = x_new;
            angle(:) = angle + alpha(i);
        else
            % Otherwise shift in a counter clockwise manner
            x_new(:) = x - bitsra(y, i - 1);
            y(:) = y + bitsra(x, i - 1);
            x(:) = x_new;
            angle(:) = angle - alpha(i);
        end

    end

    x_result = x;
    y_result = y;
end