A = [15 -13 20 -8;
     -5 -15 -4 -4;
     -17 16 -2 9;
     10 -19 -14 -15;
     -7 8 -7 15;
     14 10 -8 -17;
     -5 -3 16 -2;
     13 -5 -10 -19];

b = [13 10 -15 9 3 18 3 20];
b = b';
A_dagger = pinv(A);
% [Q, R] = qr(A);
% disp(Q);
% disp(R);

x_hat_dagger = A_dagger * b;
x_hat_qr     = ((R')*R)^(-1)*(R')*(Q')*b;

disp("Solution with pseuodoInverse");
disp(x_hat_dagger);
disp("Solution with QR");
disp(x_hat_qr);
