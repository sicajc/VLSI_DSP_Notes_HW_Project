function [r,d] = cordic_vector_mode_opt(x, y, iters_num,T)
    % Vectoring mode
    % Description: Vectoring mode uses linear rotation s.t. y approach to 0 iteratively
    % Input:  vector (x,y) rotates it with the angle z
    % Output: Value after rotation (x,y) also the angle of tan(y/x)
    % Goal is trying to nullify y accumulating the angle when rotating.

    % Beware the boundary condition!!! The first qr cordic starts from the N+1 rows. Thus the first operation
    % Is (x,0) -> (r,0)!!
    K = 0.60725334371201;
    % Turning into fixed point
    % The partial result during calculation
    r = 0;
    x = cast(x,'like',T.x_partial);
    y = cast(y,'like',T.y_partial);
    r = cast(r,'like',T.x_partial);
    x_new     = cast(x, 'like', T.x_partial);
    K        = cast(K, 'like' , T.x_partial);
    % bin(K);

    % The result of each stage.
    d        = zeros(1,iters_num);
    for i = 1:iters_num
        % Z is the current angle, and also the angle I want to shift toward to.
        if sign(x * y) >= 0
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

   r(:) = x*K;
end