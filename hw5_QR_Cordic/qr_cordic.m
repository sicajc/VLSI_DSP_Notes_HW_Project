function [Q, R] = qr_cordic(M,T)
    % Algorithm from VLSI DSP lecture notes, 5-54, modify it using CORDIC algorithm
    N = length(M);
    % Augmenting the matrix I to the left, updating I alongside with A when performing rotation
    Q = eye(N);
    x = 0;
    y = 0;
    tmp1 = 0;
    tmp2 = 0;

    % Turning into fixed point
    Q = cast(Q,'like',T.x_output);
    x = cast(x,'like',T.x_output);
    y = cast(y,'like',T.y_output);
    tmp1 = cast(tmp1,'like',T.x_output);
    tmp2 = cast(tmp2,'like',T.y_output);

    iters_num = 12;
    for k = 1:N
        for i = N:-1:k + 1
            % This needed to be replaced with cordic, vectoring mode.
            % Use vector mode to calculate of givens rotation
            theta = 0;
            % Fixed point
            theta = cast(theta,'like',T.theta_output);
            [x_,y_,theta] = cordic_vector_mode(M(i-1, k), M(i, k), theta, iters_num,T);
            % fprintf('Vector Mode:\n theta = %f , i = %d  \n',theta,i);
            for j = k:N
                % For R
                % This needed to be replaced with cordic, rotation mode


                [tmp1, tmp2, angle] = cordic_rotation_mode(M(i-1,j), M( i,j ), theta, iters_num,T);
                % fprintf('Rotation Mode:\n x = %f , y = %f , j = %d  \n',tmp1,tmp2,j);

                M(i - 1, j) = tmp1;
                M(i, j) = tmp2;
            end
            for j = 1:N
                % For Q, after calculation, take its transpose to get the correct Q, same for this portion.
                [tmp1, tmp2, angle] = cordic_rotation_mode( Q(i-1,j), Q(i,j), theta, iters_num,T);

                Q(i-1, j) = tmp1;
                Q(i, j) = tmp2;
            end
        end
    end
    R = M;
    Q = Q';
end
