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

% x = 5;
% y = 0;
% angle = 0; % Set x=3,y=4 . Expect 53.

% [x_result, y_result, angle_result] = cordic_vector_mode(x, y, angle, ITERS_NUM);
% fprintf('Vector Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);

% x = 3;
% y = 4;
% angle = 37; % Target angle 37 angle, starting from x=3,y=4,angle 53. expect x=0,y=5

% [x_result, y_result, angle_result] = cordic_rotation_mode(x, y, angle, ITERS_NUM);
% fprintf('Rotation Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);


x = -16;
y = -6;
angle = 69.4326; % Target angle 37 angle, starting from x=-6,y=-16,angle 69.4326. expect x=-17.088,y=-0.003378
[x_result, y_result, angle_result] = cordic_rotation_mode(x, y, angle, ITERS_NUM);
fprintf('Rotation Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);



%================================================================
%  Functions
%================================================================
function [x_result, y_result, angle] = cordic_vector_mode(x, y, angle, iters_num)
    % Vectoring mode
    % Description: Vectoring mode uses linear rotation s.t. y approach to 0 iteratively
    % Input:  vector (x,y) rotates it with the angle z
    % Output: Value after rotation (x,y) also the angle of tan(y/x)
    % Goal is trying to nullify y accumulating the angle when rotating.
    alpha = [45, 26.565, 14.0362, 7.12502, 3.57633, 1.78991, 0.895174, 0.447614, 0.223811, 0.111906, 0.055953, 0.027977];
    for i = 1:iters_num
        % Z is the current angle, and also the angle I want to shift toward to.
        if -sign(x * y) > 0
            x_new = x - bitsra(y, i - 1);
            y = y + bitsra(x, i - 1);
            x = x_new;
            angle = angle - alpha(i);
        else
            x_new = x + bitsra(y, i - 1);
            y = y - bitsra(x, i - 1);
            x = x_new;
            angle = angle + alpha(i);
        end

    end

    x_result = x;
    y_result = y;
end


function [x_result, y_result, angle] = cordic_rotation_mode(x, y, angle, iters_num)
    % Rotation mode
    % Description: Rotation mode using Linear rotation and multiplied by a constant K = 0.607252935 for stretching
    % Input:  vector (x,y) rotates it with the angle z
    % Output: vector (xcos(z),ysin(z))
    % Enables shift add multiply instead of calculation trigonemetric function
    % tan(a^i) = 2^(-i), thus tan(a^i) is simply shift.
    % Try to approach the desirable angle, we multiply the cos(a^i) only after the complete rotation.
    % Simply multiply K = 0.607252935 after the rotations. See if the angle difference approach to zero.

    alpha = [45, 26.565, 14.0362, 7.12502, 3.57633, 1.78991, 0.895174, 0.447614, 0.223811, 0.111906, 0.055953, 0.027977];
    K = 0.607252935;

    for i = 1:iters_num
        % Z is the current angle, and also the angle I want to shift toward to.
        if angle > 0
            x_new = x - bitsra(y, i - 1);
            y = y + bitsra(x, i - 1);
            x = x_new;
            angle = angle - alpha(i);
        else
            x_new = x + bitsra(y, i - 1);
            y = y - bitsra(x, i - 1);
            x = x_new;
            angle = angle + alpha(i);
        end

    end

    x_result = x*K;
    y_result = y*K;
end
