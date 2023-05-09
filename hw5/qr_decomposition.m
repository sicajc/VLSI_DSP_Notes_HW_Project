%================================================================
%  Main Driver
%================================================================
% M = [2 16 -6 -16;
%      16 -17 10 -2;
%      -6 10 15 -1;
%      -16 -2 -1 9];

% [Q, R] = qr_decomposition(M);

% disp("Givens rotation QR");
% disp(Q);
% disp(R);


% [Q_m, R_m] = qr(M);
% disp("Matlab QR");
% disp(Q_m);
% disp(R_m);

%================================================================
%  Function
%================================================================
function [Q, R] = qr_decomposition(M_in)
    % Algorithm from VLSI DSP lecture notes, 5-54, modify it using CORDIC algorithm
    M = M_in;
    N = length(M);
    % Augmenting the matrix I to the left, updating I alongside with A when performing rotation
    Q = eye(N);

    for k = 1:N
        for i = N:-1:k + 1
            % This needed to be replaced with cordic, vectoring mode.
            theta = atan(M(i, k) / M(i - 1, k));

            for j = k:N
                % For R
                % This needed to be replaced with cordic, rotation mode.
                tmp1 = M(i - 1, j) * cos(theta) + M(i, j) * sin(theta);
                tmp2 = -M(i - 1, j) * sin(theta) + M(i, j) * cos(theta);

                M(i - 1, j) = tmp1;
                M(i, j) = tmp2;
            end

            for j = 1:N
                % For Q, after calculation, take its transpose to get the correct Q, same for this portion.
                tmp1 = Q(i - 1, j) * cos(theta) + Q(i, j) * sin(theta);
                tmp2 = -Q(i - 1, j) * sin(theta) + Q(i, j) * cos(theta);

                Q(i - 1, j) = tmp1;
                Q(i, j) = tmp2;
            end
        end

    end

    Q = Q';
    R = M;
end
