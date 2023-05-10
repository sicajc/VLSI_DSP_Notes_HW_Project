function d = cordic_vector_mode_opt(x, y, iters_num,T)
    % Vectoring mode
    % Description: Vectoring mode uses linear rotation s.t. y approach to 0 iteratively
    % Input:  vector (x,y) rotates it with the angle z
    % Output: Value after rotation (x,y) also the angle of tan(y/x)
    % Goal is trying to nullify y accumulating the angle when rotating.

    % Turning into fixed point
    x_result = cast(x,'like',T.x_output);
    y_result = cast(y,'like',T.y_output);
    x_new    = cast(x,'like',T.x_output);
    d        = zeros(1,iters_num);

    for i = 1:iters_num
        % Z is the current angle, and also the angle I want to shift toward to.
        if sign(x * y) > 0
            % Since it is at the first dimension, we shoudl shift in a clockwise manner.
            % Since we are trying to obtain the angle, we must first add when we are rotating.
            x_new(:) = x + bitsra(y, i - 1);
            y(:)     = y - bitsra(x, i - 1);
            x(:) = x_new;
            d(i) = 0;
        else
            % Otherwise shift in a CounterClockwise(CC) manner
            x_new(:) = x - bitsra(y, i - 1);
            y(:) = y + bitsra(x, i - 1);
            x(:) = x_new;
            d(i) = 1;
        end

    end

    x_result = x;
    y_result = y;
end