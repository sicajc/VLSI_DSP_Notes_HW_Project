m = [2 16 -6 -16 3 15 -6 -19;
     16 -17 10 -2 7 8 3 5;
     -6 10 15 -1 -15 -18 9 -8;
     -16 -2 -1 9 0 0 0 18;
     3 7 -15 0 14 19 -12 11;
     15 8 -18 0 19 10 -8 -17;
     -6 3 9 0 -12 -8 15 20;
     -19 5 -8 18 11 -17 20 20];

M = [2 16 -6 -16;
     16 -17 10 -2;
     -6 10 15 -1;
     -16 -2 -1 9];
M2 = M;

max_iters = 20000;

n = size(M);
n = n(1, 1);
disp(M);
matrix_entry_upper = M(2, 1);
matrix_entry_lower = M(3, 1);
[c, s] = givensrotation(matrix_entry_upper, matrix_entry_lower);

givens_coef = [c, s];
% Givens rotation result
disp("The given's rotation's coefs of these entires is:")
disp(givens_coef);

% Build givens matrix.
G = [c -s;
     s c];

disp("The given's rotation matrix of these entires is:")
disp(G);

% Create Identity
I = eye(n);

disp("Identity matrix as:")
disp(I);

% Insert rotation matrix into identity
disp("The given's rotation matrix of of size n is:")
I(2:3, 2:3) = G;
G = I;
disp(G);
% Tranpose G
G_t = G.';

% Apply given's rotation to matrix M
M = G_t * M;
disp("M after applying given's rotation");
disp(M);

[M_tilda, Q, R] = tridiagonal_and_QR(m);
disp("Tridiagonalized matrix");
disp(M_tilda);
% disp("QR using givens rotation:")
% disp(Q);
% disp(R);

% disp("QR using matlab:")
% [q, r] = qr(m)
% disp(q);
% disp(r);

M = QR_eigen_decompose(m, max_iters);
disp("M after QR_eigen_decompose");
disp(M);

[V, D] = eig(m);
disp("M after eigen_decomposition through matlab function");
disp(D);

function M = QR_eigen_decompose(A, n)
    M = A;

    for i = 1:n
        %[Q,R] = qr(M);
        [M_tilda, Q, R] = tridiagonal_and_QR(M);
        M = R * Q;
    end

end

% qrgivens.m
function [M_tilda, Q, R] = tridiagonal_and_QR(A)
    [m, m] = size(A);
    Q = eye(m);
    R_close = A;
    R = A;

    % QR
    for j = 1:m

        for i = m:-1:(j + 1)
            G = eye(m);
            [c, s] = givensrotation(R(i - 1, j), R(i, j));
            G([i - 1, i], [i - 1, i]) = [c -s; s c];
            %Near Upper triangular matrix
            if i >= j + 2
                R_close = G' * R_close;
            end

            R = G' * R;
            %disp(G');
            %The orthogonal matrix s.t. M_tilda = QM
            Q = G' * Q;
            %disp(Q)
        end

    end

    for i = 1:m

        for j = 1:m

            if j > i
                R_close(i, j) = R_close(j, i);
            end

        end

    end

    M_tilda = R_close;

    % Since inverse is Q transposed!
    Q = Q';
end

% Givens rotation
function [c, s] = givensrotation(a, b)
    %Input two entries a,b outputs the coefficient of givens rotation matrix.
    if b == 0
        c = 1;
        s = 0;
    else

        if abs(b) > abs(a)
            r = a / b;
            s = 1 / sqrt(1 + r ^ 2);
            c = s * r;
        else
            r = b / a;
            c = 1 / sqrt(1 + r ^ 2);
            s = c * r;
        end

    end

end
