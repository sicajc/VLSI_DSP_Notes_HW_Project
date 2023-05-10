clc;
clear;

%================================================================
%  Setting word length and fraction length
%================================================================
lut_coef.WL = 12;
lut_coef.FL = 5;

theta_output.WL = 12;
theta_output.FL = 4;

% Only thing needed for optimized qr_cordic. (x,y)
x_output.WL = 12;
x_output.FL = 9;

y_output.WL = 12;
y_output.FL = 9;

%================================================================
%  The range for matrix A 1~1/4
%================================================================
lower_bound = 1/4;
upper_bound = 1;
range = upper_bound - lower_bound;
MATRIX_SIZE = 4;
NUM_OF_MATRIX = 300;

% Broadcasting data types.
T = qrDataType('fixed', lut_coef, x_output, y_output, theta_output);
% T = qrDataType('fixed', lut_coef, x_output, y_output, theta_output);

U = qrDataType('double', lut_coef, x_output, y_output, theta_output);
%================================================================
%  Randomly generate the matrix of value between 1~1/4
%================================================================
M = [0.25 0.36 0.6 0.88;
     0.76 0.55 0.52 0.28;
     0.6 0.33 0.45 0.25;
     0.86 0.45 0.28 0.92];

%================================================================
%  Run Random QR decomposition
%================================================================
M = cast(M, 'like', T.x_output);

%================================================================
%  Testing of QR Cordic
%================================================================
buildInstrumentedMex qr_cordic_opt -o qr_cordic_opt_mex ...
    -args {M, T} -histogram

% [q_d, r_d] = qr_cordic(M, U);
% [q_f, r_f] = qr_cordic_mex(M, T);

[q_d_opt,r_d_opt] = qr_cordic_opt(M,U);
[q_f_opt,r_f_opt] = qr_cordic_opt_mex(M,T);

% q_f = double(q_f);
% r_f = double(r_f);

q_f_opt = double(q_f_opt);
r_f_opt = double(r_f_opt);


disp("qr cordic opt with double");
disp("Q")
disp(q_d_opt);
disp("R")
disp(r_d_opt);


disp("qr cordic opt");
disp("Q")
disp(q_f_opt);
disp("R")
disp(r_f_opt);


% disp("delta calculation");
% disp("Q Compare to Q_fix")
% met_or_not = delta_calculation(q_d_opt, q_f_opt, 0.01)

%================================================================
%  QR Cordic checking for a random number of matrices
%================================================================
% delta = 0;
% wrong_entries = 0;
% count = 1;
for i = 1:NUM_OF_MATRIX
    % Generating matrix
    matrix_i = range*rand(MATRIX_SIZE,MATRIX_SIZE) + lower_bound;

    % Double calculation
    [q_d_opt,r_d_opt] = qr_cordic_opt(matrix_i,U);

    % Fixed point calculation
    matrix_i = cast(matrix_i,'like',T.x_output);
    [q_f_opt, r_f_opt] = qr_cordic_opt_mex(matrix_i,T);

    % Convert back to double for verification
    q_f_opt = double(q_f_opt);
    q_d_opt = double(q_d_opt);

    % Generate a bit string to check if met or not?
    [met_or_not(i),delta_] = delta_calculation(r_d_opt, r_f_opt, 0.01);

    delta(i) = delta_;

    % if delta_ > 0.05
    %     wrong_entries(count) = i;
    %     count = count + 1;
    % end

end

% wrong_entries



%================================================================
%  Write out golden pattern
%================================================================
matrix_golden = 'C:\Users\User\Desktop\VLSI_DSP_Notes_HW_Project\hw5\pattern\matrix_dat.txt';
q_golden = 'C:\Users\User\Desktop\VLSI_DSP_Notes_HW_Project\hw5\pattern\q_dat.txt';
r_golden = 'C:\Users\User\Desktop\VLSI_DSP_Notes_HW_Project\hw5\pattern\r_dat.txt';

% Writing  pattern
fileID_0 = fopen(matrix_golden, 'wt');
fileID_1 = fopen(q_golden, 'wt');
fileID_2 = fopen(r_golden,'wt');

% fprintf(fileID_0, '%d \n\n', NUM_OF_MATRIX);

for i = 1: NUM_OF_MATRIX
    % Generating matrix
    matrix_i = range*rand(MATRIX_SIZE,MATRIX_SIZE) + lower_bound;

    % Fixed point calculation
    matrix_i = cast(matrix_i,'like',T.x_output);
    [q_f_opt, r_f_opt] = qr_cordic_opt_mex(matrix_i,T);
    for j = 1:MATRIX_SIZE
        for k = 1:MATRIX_SIZE
            matrix_fix_val = matrix_i(j,k);
            matrix_fix_bin = bin(matrix_i(j,k));

            q_fix_val = q_f_opt(j,k);
            q_fix_bin = bin(q_f_opt(j,k));

            r_fix_val = r_f_opt(j,k);
            r_fix_bin = bin(r_f_opt(j,k));

            if j == 1 && k == 1
                fprintf(fileID_0,'%s  //  %f pat# %d \n', matrix_fix_bin,matrix_fix_val,i);
                fprintf(fileID_1,'%s  //  %f pat# %d \n', q_fix_bin,q_fix_val,i);
                fprintf(fileID_2,'%s  //  %f pat# %d \n', r_fix_bin,r_fix_val,i);
            else
                fprintf(fileID_0,'%s  //  %f \n', matrix_fix_bin,matrix_fix_val);
                fprintf(fileID_1,'%s  //  %f \n', q_fix_bin,q_fix_val);
                fprintf(fileID_2,'%s  //  %f \n', r_fix_bin,r_fix_val);
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
    -args {M, T} -config:lib -report
