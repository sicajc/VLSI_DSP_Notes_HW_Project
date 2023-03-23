clear all
close all
clc
%clf

%image = double(imread('HW2 test image_8bit.bmp'));

%Read image
test_image = double(imread('image.bmp'));
[M, N] = size(test_image);

%Define output result matrix
result = zeros(M, N);

%Define image process length
L = 512;
h = [0.037828455507; -0.023849465020; -0.110624404418; 0.377402855613;
     0.852698679009; 0.377402855613; -0.110624404418; -0.023849465020;
     0.037828455507];
g = [-0.064538882629; 0.040689417609; 0.418092273222; -0.788485616406;
     0.418092273222; 0.040689417609; -0.064538882629];
q = [-0.064538882629; -0.040689417609; 0.418092273222; 0.788485616406;
     0.418092273222; -0.040689417609; -0.064538882629];
p = [-0.037828455507; -0.023849465020; 0.110624404418; 0.377402855613;
     -0.852698679009; 0.377402855613; 0.110624404418; -0.023849465020;
     -0.037828455507];

% DWT
% Level-1
[out_l_1, out_h_1] = DWT_ROW(test_image, h, g);
[out_ll_1, out_lh_1] = DWT_COL(out_l_1, h, g);
[out_hl_1, out_hh_1] = DWT_COL(out_h_1, h, g);
result(1:512, 1:512) = [zeros(256, 256) out_hl_1; out_lh_1 out_hh_1];
% Level-2
[out_l_2, out_h_2] = DWT_ROW(out_ll_1, h, g);
[out_ll_2, out_lh_2] = DWT_COL(out_l_2, h, g);
[out_hl_2, out_hh_2] = DWT_COL(out_h_2, h, g);
result(1:256, 1:256) = [zeros(128, 128) out_hl_2; out_lh_2 out_hh_2];
% Level-3
[out_l_3, out_h_3] = DWT_ROW(out_ll_2, h, g);
[out_ll_3, out_lh_3] = DWT_COL(out_l_3, h, g);
[out_hl_3, out_hh_3] = DWT_COL(out_h_3, h, g);
result(1:128, 1:128) = [out_ll_3 out_hl_3; out_lh_3 out_hh_3];

% IDWT
% Level-3
rev_l_3 = IDWT_COL(out_ll_3, out_lh_3, q, p);
rev_h_3 = IDWT_COL(out_hl_3, out_hh_3, q, p);
rev_ll_2 = IDWT_ROW(rev_l_3, rev_h_3, q, p);

% Level-2
rev_l_2 = IDWT_COL(rev_ll_2, out_lh_2, q, p);
rev_h_2 = IDWT_COL(out_hl_2, out_hh_2, q, p);
rev_ll_1 = IDWT_ROW(rev_l_2, rev_h_2, q, p);
% Level-1
rev_l_1 = IDWT_COL(rev_ll_1, out_lh_1, q, p);
rev_h_1 = IDWT_COL(out_hl_1, out_hh_1, q, p);
rev_img_a = IDWT_ROW(rev_l_1, rev_h_1, q, p);
% Drop Level-1
rev_l_0 = IDWT_COL(rev_ll_1, zeros(size(out_lh_1)), q, p);
rev_h_0 = IDWT_COL(zeros(size(out_hl_1)), zeros(size(out_hh_1)), q, p);
rev_img_b = IDWT_ROW(rev_l_0, rev_h_0, q, p);

% Calaulate PSNR
psnr_a = PSNR(test_image, rev_img_a, 8);
psnr_b = PSNR(test_image, rev_img_b, 8);
disp(['(a) PSNR = ', num2str(psnr_a), ' dB']);
disp(['(b) PSNR = ', num2str(psnr_b), ' dB']);

%% Display image after processing
figure('Name', 'Original Image', 'NumberTitle', 'off');
imshow(mat2gray(test_image));
title('Original Image');

figure('Name', '3-Level DWT', 'NumberTitle', 'off');
imshow(mat2gray(result));
title('3-Level DWT');

figure('Name', 'Synthesis Image A', 'NumberTitle', 'off');
imshow(mat2gray(rev_img_a));
title('Synthesis Image A');

figure('Name', 'Synthesis Image B', 'NumberTitle', 'off');
imshow(mat2gray(rev_img_b));
title('Synthesis Image B');

%% Filter
function y = filter(x, w)
    % x: inputs, w: weights
    if iscolumn(x), x = x'; end
    if iscolumn(w), w = w'; end

    N = size(x, 2); % input size
    M = size(w, 2); % filter size
    L = fix(M / 2); % extend size // 2
    y = zeros(1, N); % result (row-wise)
    ext = [flip(x(2:L + 1)), x, flip(x(N - L:N - 1))]; % sym. extend

    for i = 1:N
        y(i) = dot(w, ext(1, i:i + M - 1));
    end

end

%% ROW-wise DWT
function [L, H] = DWT_ROW(img, low_filter, high_filter)
    [M, N] = size(img);
    L = zeros(M, N);
    H = zeros(M, N);

    for i = 1:M
        L(i, :) = filter(img(i, :), low_filter);
        H(i, :) = filter(img(i, :), high_filter);
    end

    % down sample
    L = L(:, 1:2:end); % keep odd
    H = H(:, 2:2:end); % keep even
end

%% COL-wise DWT
function [L, H] = DWT_COL(img, low_filter, high_filter)
    [M, N] = size(img);
    L = zeros(M, N);
    H = zeros(M, N);

    for i = 1:N
        L(:, i) = filter(img(:, i), low_filter)';
        H(:, i) = filter(img(:, i), high_filter)';
    end

    % down sample
    L = L(1:2:end, :); % keep odd
    H = H(2:2:end, :); % keep even
end

%% COL-wise IDWT
function img = IDWT_COL(L, H, low_filter, high_filter)
    [M, N] = size([L; H]);

    % up sample
    ext_L = zeros(M, N);
    ext_H = zeros(M, N);
    ext_L(1:2:end, :) = L; % keep odd
    ext_H(2:2:end, :) = H; % keep even

    for i = 1:N
        ext_L(:, i) = filter(ext_L(:, i), low_filter)';
        ext_H(:, i) = filter(ext_H(:, i), high_filter)';
    end

    img = ext_L + ext_H;

    figure(9);
    imshow(img, []);
    title('img');
end

%% ROW-wise IDWT
function img = IDWT_ROW(L, H, low_filter, high_filter)
    [M, N] = size([L H]);

    % up sample
    ext_L = zeros(M, N);
    ext_H = zeros(M, N);
    ext_L(:, 1:2:end) = L; % keep odd
    ext_H(:, 2:2:end) = H; % keep even

    for i = 1:M
        ext_L(i, :) = filter(ext_L(i, :), low_filter);
        ext_H(i, :) = filter(ext_H(i, :), high_filter);
    end

    img = ext_L + ext_H;

    figure(9);
    imshow(img, []);
    title('img');

end

%% PSNR
function psnr = PSNR(img_ref, img, nbit)
    mse = mean((img(:) - img_ref(:)) .^ 2); % Calculate mean squared error
    maxi = 2 ^ nbit - 1; % Maximum possible pixel value for nbit
    psnr = 10 * log10((maxi ^ 2) / mse); % Calculate PSNR using the formula
end
