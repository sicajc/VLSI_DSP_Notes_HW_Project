function [Q, R] = qr_cordic(M)
    % Algorithm from VLSI DSP lecture notes, 5-54, modify it using CORDIC algorithm
    N = length(M);
    % Augmenting the matrix I to the left, updating I alongside with A when performing rotation
    Q = eye(N);
    iters_num = 12;

    for k = 1:N

        for i = N:-1:k + 1
            % This needed to be replaced with cordic, vectoring mode.
            % Use vector mode to calculate of givens rotation

            theta = 0;
            % All calculation is reversed, quite strange. (x,y) -> (y,x) ?? Need further discussion and debug.
            [x,y,theta] = cordic_vector_mode(M(i-1, k), M(i, k), theta, iters_num);
            % fprintf('Vector Mode:\n theta = %f , i = %d  \n',theta,i);

            for j = k:N
                % For R
                % This needed to be replaced with cordic, rotation mode

                [tmp1, tmp2, angle] = cordic_rotation_mode(M(i-1,j), M( i,j ), theta, iters_num);
                % fprintf('Rotation Mode:\n x = %f , y = %f , j = %d  \n',tmp1,tmp2,j);

                M(i - 1, j) = tmp1;
                M(i, j) = tmp2;
            end

            for j = 1:N
                % For Q, after calculation, take its transpose to get the correct Q, same for this portion.
                [tmp1, tmp2, angle] = cordic_rotation_mode( Q(i-1,j), Q(i,j), theta, iters_num);


                % tmp1 =  Q(i - 1, j) * cosx + Q(i, j) * sinx;
                % tmp2 = -Q(i - 1, j) * sinx + Q(i, j) * cosx;

                Q(i-1, j) = tmp1;
                Q(i, j) = tmp2;
            end

        end

    end
    R = M;
    Q = Q';
end
