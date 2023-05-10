% Rotation mode want z approach to 0
% 3 types of cordic algorithm, each types has 2 modes.(rotation mode) turns the vector(1,0) to the desired angle you want,
% another mode
% cordic(x,y,z)
% (Rotation mode)  z is the angle we want to rotate, returns the rotated (x = cos(phi),y=sin(phi))
% 3 types, Circular rotation, Linear rotation and hyperbolic rotation.
%================================================================
%  Main Driver
%================================================================
clear;
clc;

ITERS_NUM = 12;
lut_coef.WL = 12;
lut_coef.FL = 5;

x_output.WL = 12;
x_output.FL = 10;

y_output.WL = 12;
y_output.FL = 10;

theta_output.WL = 12;
theta_output.FL = 4;

U = qrDataType('double', lut_coef, x_output, y_output, theta_output);


%================================================================
%  Testing cordic modules
%================================================================
x = 3;
y = 4;
angle = 0; % Set x=3,y=4 . Expect 53.

[x_result, y_result, angle_result] = cordic_vector_mode(x, y, angle, ITERS_NUM,U);
fprintf('Vector Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);

% x = 3;
% y = 4;
% angle = 37; % Target angle 37 angle, starting from x=3,y=4,angle 53. expect x=0,y=5

% [x_result, y_result, angle_result] = cordic_rotation_mode(x, y, angle, ITERS_NUM);
% fprintf('Rotation Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);

x = -6;
y = -16;
angle = 69.4326; % Target angle 37 angle, starting from x=-6,y=-16,angle 69.4326. expect x=-17.088,y=-0.003378
[x_result, y_result, angle_result] = cordic_rotation_mode(x, y, angle, ITERS_NUM,U);
fprintf('Rotation Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);




%================================================================
%  Testing QR cordic
%================================================================

M = [0.25 0.36 0.6 0.88;
0.76 0.55 0.52 0.28;
0.6 0.33 0.45 0.25;
0.86 0.45 0.28 0.92];

[q,r]     = qr_decomposition(M);
[q_c,r_c] = qr_cordic(M,U);

disp("qr decomposition with double");
disp("Q");
disp(q);
disp("R");
disp(r);

disp("qr cordic with double");
disp("Q")
disp(q_c);
disp("R")
disp(r_c);

%================================================================
%  Testing QR cordic opt
%================================================================
[q_opt,r_opt] = qr_cordic_opt(M,U);

disp("qr cordic opt");
disp("Q")
disp(q_opt);
disp("R")
disp(r_opt);
