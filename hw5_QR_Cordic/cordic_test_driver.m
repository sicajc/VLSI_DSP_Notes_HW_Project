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
qr_cordic_golden = 'C:\Users\User\Desktop\VLSI_DSP_Notes_HW_Project\hw5\pattern\qr_cordic_dat.txt'
fileID_0 = fopen(qr_cordic_golden, 'wt');

% Vectoring mode testing!
% Boundary conditions
x = 0;
y = -172.2021484375;
angle = 0; % Set x=3,y=4 . Expect 53.

x = cast(x,'like',T.x_partial);
y = cast(y,'like',T.y_partial);


[r,d] = cordic_vector_mode_opt(x, y, ITERS_NUM,T);
r
r_fix_bin = bin(r)

% % Write the result into file for later verification
% fprintf(fileID_0, '%s  // GG1 x = %f \n', x_fix_bin,x);
% fprintf(fileID_0, '%s  //    y = %f \n', y_fix_bin,y);
% fprintf(fileID_0, '%s  //    r = %f \n', r_fix_bin,r);

% x = 9;
% y = r;
% angle = 0; % Set x=3,y=4 . Expect 53.

% x = cast(x,'like',T.x_partial);
% y = cast(y,'like',T.y_partial);

% x_fix_bin = bin(x);
% y_fix_bin = bin(y);

% [r,d] = cordic_vector_mode_opt(x, y, ITERS_NUM,T);
% r_fix_bin = bin(r);

% % Write the result into file for later verification
% fprintf(fileID_0, '%s  // GG2 x = %f \n', x_fix_bin,x);
% fprintf(fileID_0, '%s  //    y = %f \n', y_fix_bin,y);
% fprintf(fileID_0, '%s  //    r = %f \n', r_fix_bin,r);

% for i = 1 : length(d)
%     fprintf(fileID_0, '%d ', d(i));
% end
% fprintf(fileID_0, '// Expected di  \n');

% Rotation mode testing
% x = -58;
% y = 76.8984375;
% d = [1,1,1,0,0,1,1,1,0,0,0,0];
% x = cast(x,'like',T.x_partial);
% y = cast(y,'like',T.y_partial);

% [x_result, y_result] = cordic_rotation_mode_opt(x, y, d, ITERS_NUM,T);

% x_fix_bin = bin(x);
% y_fix_bin = bin(y);

% x_result_fix_bin = bin(x_result);
% y_result_fix_bin = bin(y_result);

% Write the result into file for later verification
% fprintf(fileID_0, '%s  // GR1 x = %f \n', x_fix_bin,x);
% fprintf(fileID_0, '%s  //    y = %f \n', y_fix_bin,y);
% fprintf(fileID_0, '%s  //    x_result = %f \n', x_result_fix_bin ,x_result);
% fprintf(fileID_0, '%s  //    y_result = %f \n', y_result_fix_bin ,y_result);
%
% fclose(fileID_0);


% % Rotation mode testing
% x = -21;
% y = -14.83203125;
% d = [0,1,0,1,0,1,0,1,0,1,0,1];
% [x_result, y_result] = cordic_rotation_mode_opt(x, y, d, ITERS_NUM,T)

% x = 3;
% y = 4;
% angle = 37; % Target angle 37 angle, starting from x=3,y=4,angle 53. expect x=0,y=5

% [x_result, y_result, angle_result] = cordic_rotation_mode(x, y, angle, ITERS_NUM);
% fprintf('Rotation Mode:\n x = %f , y = %f , angle = %f  \n',x_result,y_result,angle_result);


%================================================================
%  Testing QR cordic
%================================================================

% M = [25 -36 -6 88;
% -76 55 52 28;
% 6 -33 45 -25;
% -86 45 28 -92];

% [q,r]     = qr(M);

% disp("MATLAB qr decomposition");
% disp("Q");
% disp(q);
% disp("R");
% disp(r);

%================================================================
%  Testing QR cordic opt
%================================================================
% [q_opt,r_opt] = qr_cordic_opt(M,T,S);

% disp("QR Cordic fixed point opt");
% disp("Q")
% disp(q_opt);
% disp("R")
% disp(r_opt);
