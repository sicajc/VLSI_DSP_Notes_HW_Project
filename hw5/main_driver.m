clc;
clear;
M = [2 16 -6 -16;
     16 -17 10 -2;
     -6 10 15 -1;
     -16 -2 -1 9];


[q,r] = qr_decomposition(M);
[q_c,r_c] = qr_cordic(M);

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