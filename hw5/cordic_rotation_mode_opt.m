function [x_result, y_result] = cordic_rotation_mode_opt(x, y, d,iters_num, T)
    % Rotation mode
    % Description: Rotation mode using Linear rotation and multiplied by a constant K = 0.607252935 for stretching
    % Input:  vector (x,y) rotates it with the angle z
    % Output: vector (xcos(z),ysin(z))
    % Enables shift add multiply instead of calculation trigonemetric function
    % tan(a^i) = 2^(-i), thus tan(a^i) is simply shift.
    % Try to approach the desirable angle, we multiply the cos(a^i) only after the complete rotation.
    % Simply multiply K = 0.607252935 after the rotations. See if the angle difference approach to zero.

    K = 0.60725334371201; % This is Products of K_12

     % Turning into fixed point
     x_result = cast(x,'like',T.x_output);
     y_result = cast(y,'like',T.y_output);
     x_new = cast(x,'like',T.x_output);
     K     = cast(K,'like',T.x_output);

    for i = 1:iters_num
        % Z is the current angle, and also the angle I want to shift toward to.
        if d(i) == 0
            % If angle is above 0, I would like to rotate in a clockwise manner
            x_new(:) = x + bitsra(y, i - 1);
            y(:) = y - bitsra(x, i - 1);
            x(:) = x_new;
        else
            % Otherwise, rotate counter clockwise.
            x_new(:) = x - bitsra(y, i - 1);
            y(:) = y + bitsra(x, i - 1);
            x(:) = x_new;
        end

    end

    x_result = x * K;
    y_result = y * K;
end
