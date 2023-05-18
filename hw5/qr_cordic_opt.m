function [Q, R] = qr_cordic_opt(M,T,S)
    % Algorithm from VLSI DSP lecture notes, 5-54, modify it using CORDIC algorithm
    N = length(M);
    % Augmenting the matrix I to the left, updating I alongside with A when performing rotation
    Q = eye(N);


    tmp1 = 0;
    tmp2 = 0;

    % Turning into fixed point
    M_        = cast(M, 'like',T.x_partial);

    R         = cast(M_,'like',T.x_output);
    Q         = cast(Q,'like' ,S.x_output);

    tmp1 = cast(tmp1,'like',T.x_partial);
    tmp2 = cast(tmp2,'like',T.y_partial);
    d=0;

    iters_num = 12;
    for k = 1:N

        for i = N:-1:k
            % This needed to be replaced with cordic, vectoring mode.
            % Use vector mode to calculate of givens rotation

            % The boundary condition of cordics. While N = 4, the input value is 0.

            if i == 4
                if k ~= N % The boundary condition for r44, do not rotate it anymore!
                    [r,d] = cordic_vector_mode_opt(M_(i,k), 0, iters_num,T);
                    M_(i,k) = r;
                end
            else
                [r,d] = cordic_vector_mode_opt(M_(i, k), M_(i+1, k), iters_num,T);
                % fprintf('Entry: (%d,%d)',i,k);
                M_(i,k) = r;
                M_(i+1,k) = 0;
            end

            % disp("After Vector mode");
            % M_


            % fprintf('Vector Mode:\n theta = %f , i = %d  \n',theta,i);

            for j = k+1:N
                % For R
                % This needed to be replaced with cordic, rotation mode
                % The boundary conditions.
                if i == N
                    if  k ~= N
                        [tmp1,tmp2] = cordic_rotation_mode_opt(M_(i,j), 0,d, iters_num,T);
                        M_(i, j) = tmp1;
                    end
                else
                    [tmp1,tmp2] = cordic_rotation_mode_opt(M_(i, j), M_(i+1, j),d, iters_num,T);
                    % fprintf('Entry: (%d,%d)',i,j);
                    % disp("Rotation mode Result x:");
                    % tmp1
                    % bin(tmp1)
                    M_(i, j) = tmp1;

                    % disp("Rotation mode Result y:");
                    % tmp2
                    % bin(tmp2)
                    M_(i+1, j) = tmp2;

                end

                % [tmp1, tmp2] = cordic_rotation_mode_opt(M_(i,j), M_( i+1,j ), d, iters_num,T);
                % fprintf('Rotation Mode:\n x = %f , y = %f , j = %d  \n',tmp1,tmp2,j);
            end

            % disp("After Rotations");
            % M_;

            if k == N
                break;
            end

            for j = 1:N
                if i == 4
                    d;
                    [tmp1,tmp2] = cordic_rotation_mode_opt(Q(i,j), 0,d, iters_num,S);
                    % tmp1
                    % bin(tmp1)
                    Q(i, j) = tmp1;
                else
                    [tmp1,tmp2] = cordic_rotation_mode_opt(Q(i, j), Q(i+1, j),d, iters_num,S);
                    Q(i, j) = tmp1;
                    Q(i+1, j) = tmp2;
                end

                % For Q, after calculation, take its transpose to get the correct Q, same for this portion.
                % [tmp1, tmp2] = cordic_rotation_mode_opt( Q(i-1,j), Q(i,j), d, iters_num,S);
            end
            M_;
            Q;
        end
    end
    Q;
    R(:) = M_;
    Q(:) = Q;
end
