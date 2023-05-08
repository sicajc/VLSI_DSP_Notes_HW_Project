M = [2 16 -6 -16;
     16 -17 10 -2;
     -6 10 15 -1;
     -16 -2 -1 9];
M2 = M;

max_iters = 20000;

N = length(M);
disp(M);

M_result = QR_eigen_decompose(M)



function M = QR_eigen_decompose(M)
    % Algorithm for VLSI DSP lecture notes
    N = length(M)
    for k = 1:N

        for i = N - 1:k
            theta = atan(M(i + 1, k) / M(i, k))

            for j = k:N
                tmp1 = M(i, j) * cos(theta) + M(i + 1, j) * sin(theta)
                tmp2 = -M(i, j) * sin(theta) + M(i + 1, j) * cos(theta)
                M(i, j) = tmp1
                M(i + 1, j) = tmp2

            end

        end

    end

end
