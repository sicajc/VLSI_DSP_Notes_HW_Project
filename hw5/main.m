clc;
clear;

%================================================================
%  Setting word length and fraction length
%================================================================
lut_coef.WL = 12;
lut_coef.FL = 6;

x_output.WL = 12;
x_output.FL = 6;

y_output.WL = 12;
y_output.FL = 6;

theta_output.WL = 12;
theta_output.FL = 6;

% Broadcasting data types.
T = filterDataType('scaled', lut_coef, x_output, y_output, theta_output);

M = [2 16 -6 -16;
     16 -17 10 -2;
     -6 10 15 -1;
     -16 -2 -1 9];

%================================================================
%  Testing of QR Cordic and QR iteratives
%================================================================
[q, r] = qr_decomposition(M);
[q_f, r_f] = qr_cordic(M);

disp("qr decomposition with double");
disp("Q");
disp(q);
disp("R");
disp(r);

disp("qr cordic with double");
disp("Q")
disp(q_f);
disp("R")
disp(r_f);

%================================================================
%  QR Cordic
%================================================================



% disp("delta calculation");
% disp("Q Compare to Q_fix")
% met_or_not = delta_calculation(q,q_c,0.01)
