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

x = 3;
y = 4;
angle = 0; % Set x=3,y=4 . Expect 53.

[x_result, y_result, angle_result] = cordic_vector_mode(x, y, angle, ITERS_NUM);
fprintf('Vector Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);

% x = 3;
% y = 4;
% angle = 37; % Target angle 37 angle, starting from x=3,y=4,angle 53. expect x=0,y=5

% [x_result, y_result, angle_result] = cordic_rotation_mode(x, y, angle, ITERS_NUM);
% fprintf('Rotation Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);

x = -6;
y = -16;
angle = 69.4326; % Target angle 37 angle, starting from x=-6,y=-16,angle 69.4326. expect x=-17.088,y=-0.003378
[x_result, y_result, angle_result] = cordic_rotation_mode(x, y, angle, ITERS_NUM);
fprintf('Rotation Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);
