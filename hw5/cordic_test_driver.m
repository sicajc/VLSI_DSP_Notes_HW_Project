% Rotation mode want z approach to 0
% 3 types of cordic algorithm, each types has 2 modes.(rotation mode) turns the vector(1,0) to the desired angle you want,
% another mode
% cordic(x,y,z)
% (Rotation mode)  z is the angle we want to rotate, returns the rotated (x = cos(phi),y=sin(phi))
% 3 types, Circular rotation, Linear rotation and hyperbolic rotation.
clear;
clc;
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

ITERS_NUM = 12;

% Data type for R calculation
T = qrDataType('fixed', rx_partial, ry_partial,rx_output, ry_output);

% Data type for Q calculation
S = qrDataType('fixed', qx_partial, qy_partial,qx_output, qy_output);


%================================================================
%  Testing cordic modules
%================================================================
x = 5;
y = 0;
angle = 0; % Set x=3,y=4 . Expect 53.

d = cordic_vector_mode_opt(x, y, ITERS_NUM,T);
% fprintf('Vector Mode:\n x = %f , y = %f',x_result,y_result);

d

% x = 3;
% y = 4;
% angle = 37; % Target angle 37 angle, starting from x=3,y=4,angle 53. expect x=0,y=5

% [x_result, y_result, angle_result] = cordic_rotation_mode(x, y, angle, ITERS_NUM);
% fprintf('Rotation Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);

x = -6;
y = -16;
angle = 69.4326; % Target angle 37 angle, starting from x=-6,y=-16,angle 69.4326. expect x=-17.088,y=-0.003378
[x_result, y_result] = cordic_rotation_mode_opt(x, y, d, ITERS_NUM,T);
fprintf('Rotation Mode:\n x = %f , y = %f \n',x_result,y_result);




%================================================================
%  Testing QR cordic
%================================================================

% M = [0.25 0.36 0.6 0.88;
% 0.76 0.55 0.52 0.28;
% 0.6 0.33 0.45 0.25;
% 0.86 0.45 0.28 0.92];

% [q,r]     = qr_decomposition(M);
% [q_c,r_c] = qr_cordic(M,U);

% disp("qr decomposition with double");
% disp("Q");
% disp(q);
% disp("R");
% disp(r);

% disp("qr cordic with double");
% disp("Q")
% disp(q_c);
% disp("R")
% disp(r_c);

%================================================================
%  Testing QR cordic opt
%================================================================
% [q_opt,r_opt] = qr_cordic_opt(M,U);

% disp("qr cordic opt");
% disp("Q")
% disp(q_opt);
% disp("R")
% disp(r_opt);
