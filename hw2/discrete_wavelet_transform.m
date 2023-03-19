clear;
clc

%================================================================
%  RD image
%================================================================
img = imread('image.bmp');
img = double(img);
[h, w] = size(img);
n = 1;
stride = 2;

filtered_img = img;

figure(1);
imshow(img, []);
title('Original image');
%================================================================
%  DWT
%================================================================
% Octave 1
gn_filtered_img = gn_HPF(img);
w1n = downSampler(gn_filtered_img, stride, 0);

figure(2);
subplot(3, 2, 1);
imshow(w1n, []);
title('w1n');

hn_filtered_img = hn_LPF(img);
s1n = downSampler(hn_filtered_img, stride, 1);

subplot(3, 2, 2);
imshow(s1n, []);
title('s1n');

% Octave 2
gn_filtered_img = gn_HPF(s1n);
w2n = downSampler(gn_filtered_img, stride, 0);

subplot(3, 2, 3);
imshow(w2n, []);
title('w2n');

hn_filtered_img = hn_LPF(s1n);
s2n = downSampler(hn_filtered_img, stride, 1);

subplot(3, 2, 4);
imshow(s2n, []);
title('s2n');

% Octave 3
gn_filtered_img = gn_HPF(s2n);
w3n = downSampler(gn_filtered_img, stride, 0);

subplot(3, 2, 5);
imshow(w3n, []);
title('w3n');

hn_filtered_img = hn_LPF(s2n);
s3n = downSampler(hn_filtered_img, stride, 1);

subplot(3, 2, 6);
imshow(s3n, []);
title('s3n');

figure(3);
imshow(s3n, []);
title('s3n');
figure(4);
imshow(w3n, []);
title('w3n');
hold on;
%================================================================
%  IDWT
%================================================================
% Octave 1
w3n_ = upSampler(w3n, stride, 3);
pn_filtered_img = pn_HPF(w3n_);

s3n_ = upSampler(s3n, stride, 3);
qn_filtered_img = qn_LPF(s3n_);

s2_hatn = pn_filtered_img + qn_filtered_img;

% Octave 2
w2n_ = upSampler(w2n, stride, 2);
pn_filtered_img = pn_HPF(w2n_);

s2_hatn_ = upSampler(s2_hatn, stride, 2);
qn_filtered_img = qn_LPF(s2_hatn_);

s1_hatn = pn_filtered_img + qn_filtered_img;

% Octave 3
w1n_ = upSampler(w1n, stride, 1);
pn_filtered_img = pn_HPF(w1n_);

s1_hatn_ = upSampler(s1_hatn, stride, 1);
qn_filtered_img = qn_LPF(s1_hatn_);

s0_hatn = pn_filtered_img + qn_filtered_img;

s0_hatn_ = ceil(s0_hatn);
s0_hatn_(s0_hatn_ > 255) = 255;
s0_hatn_(s0_hatn_ < -255) = -255;

figure(5);
imshow(s0_hatn_, []);
title('s0 hatn');
%================================================================
%  PSNR
%================================================================
disp("PSNR:");
[psnr, difference] = PSNR(img, s0_hatn_);
disp(psnr);

%================================================================
%  FUNCTIONS
%================================================================
function filtered_img = gn_HPF(raw_img)
    wn = [-0.064538882629 0.040689417609 0.418092273222 ...
              -0.788485616406 ...
              0.418092273222 0.040689417609 -0.064538882629];

    [h, w] = size(raw_img);
    filtered_img = raw_img;

    for i = 1:h
        row_img = raw_img(i, :)
        filtered_row = filterSystem(row_img, wn, w);
        filtered_img(i, :) = filtered_row;
    end

end

function filtered_img = hn_LPF(raw_img)
    wn = [0.037828455507 -0.023849465020 -0.110624404418 0.377402855613 ...
              0.852698679009 ...
              0.377402855613 -0.110624404418 -0.023849465020 0.037828455507];

    [h, w] = size(raw_img);
    filtered_img = raw_img;

    for i = 1:w
        row_img = raw_img(i, :)
        filtered_row = filterSystem(row_img, wn, h);
        filtered_img(i, :) = filtered_row;
    end

end

function filtered_img = qn_LPF(raw_img)
    wn = [-0.064538882629 -0.040689417609 0.418092273222 ...
              0.788485616406 ...
              0.418092273222 -0.040689417609 -0.064538882629];

    [h, w] = size(raw_img);
    filtered_img = raw_img;

    for i = 1:w
        row_img = raw_img(i, :)
        filtered_row = filterSystem(row_img, wn, h);
        filtered_img(i, :) = filtered_row;
    end

end

function filtered_img = pn_HPF(raw_img)
    wn = [-0.037828455507 -0.023849465020 0.110624404418 0.377402855613 ...
              -0.852698679009 ...
              0.377402855613 0.110624404418 -0.023849465020 -0.037828455507];

    [h, w] = size(raw_img);
    filtered_img = raw_img;

    for i = 1:w
        row_img = raw_img(i, :)
        filtered_row = filterSystem(row_img, wn, h);
        filtered_img(i, :) = filtered_row;
    end

end

function yn = filterSystem(xn, wn, N)
    % N signals
    % xn is the input signals
    % wn is the coefficient vector of filterSystem
    yn = zeros(1, N);
    L = size(wn);
    L = L(2);

    %Symmetric extension
    xn = [xn(2:L), xn, xn(N - L:N - 1)];

    for n = L:N + L - 1
        x = xn(n:-1:n - L + 1);
        yn(n - L + 1) = wn * x';
    end

end

function downSampledimg = downSampler(img, stride, odd)
    [h, w] = size(img);
    downSampledimg = zeros(h);

    if odd == 0
        %even for HPF
        downSampledimg(1:w / 2, 1:h / 2) = img(2:stride:w, 2:stride:h);
    else
        %odd for LPF
        downSampledimg(1:w / 2, 1:h / 2) = img(1:stride:w, 1:stride:h);
    end

end

function upSampledimg = upSampler(img, stride, n)
    % n means nth octave
    [h, w] = size(img);
    partition = 2 ^ n;
    upSampledimg = zeros(h);

    % Replicated the the second row to first row
    upSampledimg(2:stride:w / (partition / 2), 2:stride:h / (partition / 2)) = img(1:w / partition, 1:h / partition);
    upSampledimg(1:stride:w / (partition / 2), 1:stride:h / (partition / 2)) = img(1:w / partition, 1:h / partition);
end

function [psnr, difference] = PSNR(img, filtered_img)
    [h, w] = size(img);
    MAXI = 255;
    difference = (img - filtered_img) .^ 2;
    MSE = sum(difference, "all") / (h * w);

    psnr = 10 * log10(MAXI ^ 2 / MSE);
end
