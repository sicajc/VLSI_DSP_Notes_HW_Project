clc;
clear;

% A is limited to 8 bits integer. So the range of signed integers should be +127 ~ -128
% Q is limited to 12 bits fix-point value
% R is limited to 12 bits
% NOTE:
% When performing calculation in cordic, the rounding mode here is specified as floor, that is simply perform truncation
% no need for rounding so that the result can be simplified.
% The datapath of the whole cordic architecture is 20 bits for R, 12 bits for Q ; However, the final result is truncated to
% 12 bits only for both R and Q.

%================================================================
%  Setting word length and fraction length
%================================================================
% For R
% Values needed to be optimized for QR cordic
rx_output.WL = 12;
rx_output.FL = 3;

ry_output.WL = 12;
ry_output.FL = 3;
% x_partial, y_partial.
% The register holding partial product when shifting for each iteration.
rx_partial.WL = 20;
rx_partial.FL = 10;

ry_partial.WL = 20;
ry_partial.FL = 10;

% For Q
% Values needed to be optimized for QR cordic
qx_output.WL = 12;
qx_output.FL = 10;

qy_output.WL = 12;
qy_output.FL = 10;

% x_partial, y_partial.
% The register holding partial product when shifting for each iteration.
% 18 8
% 20 10
qx_partial.WL = 12;
qx_partial.FL = 10;

qy_partial.WL = 12;
qy_partial.FL = 10;

%================================================================
%  The range for matrix A -128~127
%================================================================
lower_bound = -128;
upper_bound = 127;
MATRIX_SIZE = 4;
NUM_OF_MATRIX = 300;

% Broadcasting data types.
U = qrDataType('double', rx_partial, ry_partial, rx_output, ry_output);

% Data type for R calculation
T = qrDataType('fixed', rx_partial, ry_partial, rx_output, ry_output);

% Data type for Q calculation
S = qrDataType('fixed', qx_partial, qy_partial, qx_output, qy_output);

%================================================================
%  matrix for testing
%================================================================
M = [-70 55 80 90;
     -112 36 -47 1;
     68 -21 80 34;
     43 -28 74 115];

C = fi([], 1, 8, 0); % Since M is 8 bits.
C;
matrix_i = cast(M, 'like', C);

K = 0.60725334371201;
K = cast(K, 'like',T.x_partial);
bin(K);

%================================================================
%  Testing of QR Cordic
%================================================================
buildInstrumentedMex qr_cordic_opt -o qr_cordic_opt_mex ...
    -args {matrix_i, T, S} -histogram

% [q_d, r_d] = qr_cordic(M, U);
% [q_f, r_f] = qr_cordic_mex(M, T);

% [q_double, r_double] = qr_cordic_opt(M, U, U);
[q_f_opt, r_f_opt] = qr_cordic_opt_mex(matrix_i, T, S);

% q_f_opt = double(q_f_opt);
% r_f_opt = double(r_f_opt);

% [q, r] = qr(M);

% disp("Matlab QR decomposition");
% disp("Q")
% disp(q);
% disp("R")
% disp(r);

% disp("qr cordic opt with double");
% disp("Q")
% disp(q_double);
% disp("R")
% disp(r_double);

% disp("qr cordic opt");
% disp("Q")
% disp(q_f_opt);
% disp("R")
% disp(r_f_opt);

% disp("delta calculation");
% disp("Q Compare to Q_fix");
% [met_or_not, delta_] = delta_calculation(r_double, r_f_opt, 0.01);

%================================================================
%  QR Cordic checking for a random number of matrices
%================================================================
% count = 0;
% for i = 1:NUM_OF_MATRIX
%     % Generating matrix
%     matrix_i = randi([lower_bound,upper_bound],MATRIX_SIZE,MATRIX_SIZE);

%     % Double calculation
%     [q_double, r_double] = qr_cordic_opt(matrix_i, U,U);

%     % Fixed point calculation
%     matrix_i = cast(matrix_i, 'like', C);
%     [q_f_opt, r_f_opt] = qr_cordic_opt_mex(matrix_i, T,S);

%     % Convert back to double for verification
%     q_double = double(q_double);
%     r_double = double(r_double);

%     q_f_opt = double(q_f_opt);
%     r_f_opt = double(r_f_opt);

%     % Should replace the lower triangle with 0, since it is not needed for metrics.
%     r_double = r_double .* (1 - tril(ones(size(r_double))));
%     r_f_opt = r_f_opt .* (1 - tril(ones(size(r_f_opt))));

%     % Generate a bit string to check if met or not?
%     [met_or_not(i), deltar_] = delta_calculation(r_double, r_f_opt, 0.01);
%     [met_or_not(i), deltaq_] = delta_calculation(q_double, q_f_opt, 0.01);

%     deltar(i) = deltar_;
%     deltaq(i) = deltaq_;

% end

% disp("The largest delta of R within is:");
% disp(max(deltar));
% disp("Average delta for R:");
% disp(mean(deltar,'all'));

% disp("The largest delta of Q within is:");
% disp(max(deltaq));
% disp("Average delta Q:");
% disp(mean(deltaq,'all'));

%================================================================
%  Write out golden pattern
%================================================================
matrix_golden = 'C:\Users\User\Desktop\VLSI_DSP_Notes_HW_Project\hw5\pattern\matrix_dat.txt';
q_golden = 'C:\Users\User\Desktop\VLSI_DSP_Notes_HW_Project\hw5\pattern\q_dat.txt';
r_golden = 'C:\Users\User\Desktop\VLSI_DSP_Notes_HW_Project\hw5\pattern\r_dat.txt';

% Writing  pattern
fileID_0 = fopen(matrix_golden, 'wt');
fileID_1 = fopen(q_golden, 'wt');
fileID_2 = fopen(r_golden, 'wt');

% fprintf(fileID_0, '%d \n\n', NUM_OF_MATRIX);

for i = 1:NUM_OF_MATRIX
    % Generating matrix
    matrix_i = randi([lower_bound, upper_bound], MATRIX_SIZE, MATRIX_SIZE);

    % Fixed point calculation
    matrix_i = cast(matrix_i, 'like', C)
    [q_f_opt, r_f_opt] = qr_cordic_opt_mex(matrix_i, T, S);

    q_f_opt = cast(q_f_opt, 'like', S.x_output)
    r_f_opt = cast(r_f_opt, 'like', T.x_output)

    for k = 1:MATRIX_SIZE

        for j = MATRIX_SIZE:-1:1
            matrix_fix_val = matrix_i(j, k);
            matrix_fix_bin = bin(matrix_i(j, k));

            % Append the pattern number at the start of every pattern.
            if j == 4 && k == 1
                fprintf(fileID_0, '%s  //  %f pat# %d (%d,%d) \n', matrix_fix_bin, matrix_fix_val, i, j, k);
            else
                fprintf(fileID_0, '%s  //  %f (%d,%d)\n', matrix_fix_bin, matrix_fix_val, j, k);
            end

        end

    end

    for j = 1:MATRIX_SIZE

        for k = 1:MATRIX_SIZE
            q_fix_val = q_f_opt(j, k);
            q_fix_bin = bin(q_f_opt(j, k));

            r_fix_val = r_f_opt(j, k);
            r_fix_bin = bin(r_f_opt(j, k));

            % the lower half of R should be regarded as zeroes, so instantiate a fixed point zero for them.
            zero_d = 0;
            zero = cast(zero_d, 'like', T.x_output);
            zero = bin(zero);

            % Append the pattern number at the start of every pattern.
            if j == 1 && k == 1
                fprintf(fileID_1, '%s  //  %f pat# %d (%d,%d)\n', q_fix_bin, q_fix_val, i, j, k);
            else
                fprintf(fileID_1, '%s  //  %f (%d,%d)\n', q_fix_bin, q_fix_val, j, k);
            end

            % R matrices, the lower part should all be zeroes.
            if j == 1 && k == 1
                fprintf(fileID_2, '%s  //  %f pat# %d (%d,%d)\n', r_fix_bin, r_fix_val, i, j, k);
            elseif j > k
                fprintf(fileID_2, '%s  //  %f (%d,%d)\n', zero, zero_d, j, k);
            else
                fprintf(fileID_2, '%s  //  %f (%d,%d)\n', r_fix_bin, r_fix_val, j, k);
            end

        end

    end

end

fclose(fileID_0);
fclose(fileID_1);
fclose(fileID_2);

%================================================================
%  Fixed point verification
%================================================================
% Verify results
% Show instrumentatinResults can suggest you the optimal width you should use for the best result
showInstrumentationResults qr_cordic_opt_mex -proposeFL -defaultDT numerictype(1, 12, 6)

% Code generation
codegen qr_cordic_opt ...
    -args {matrix_i, T, S} -config:lib -report
