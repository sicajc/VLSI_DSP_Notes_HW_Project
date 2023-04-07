clear all;
clc

filter_coef_WL = 128;
lv1_output_WL = 128;
lv2_output_WL = 128;
lv3_output_WL = 128;

%================================================================
%  RD image
%================================================================
img = double(imread('image.bmp'));
img = fi(img, 1, filter_coef_WL);

[h, w] = size(img);
n = 1;
stride = 2;

%================================================================
%  DWT
%================================================================

% Octave 1
octave1 = dwt_octave(img, stride, 1, lv1_output_WL, filter_coef_WL);

octave1_ = double(octave1);
figure(3);
imshow(octave1_, []);
title('Octave1');

% Octave 2
octave2 = dwt_octave(octave1, stride, 2, lv2_output_WL, filter_coef_WL);

% Octave 3
octave3 = dwt_octave(octave2, stride, 3, lv3_output_WL, filter_coef_WL);

octave3 = double(octave3);

%================================================================
%  IDWT
%================================================================
zero_padded = 0;
octave3_ = zeros(h);

if zero_padded == 1
    octave3_(1:h / 2, 1:w / 2) = octave3(1:h / 2, 1:w / 2);
else
    octave3_ = octave3;
end

ioctave3 = idwt_octave(octave3_, stride, 3);

ioctave2 = idwt_octave(ioctave3, stride, 2);

ioctave1 = idwt_octave(ioctave2, stride, 1);

restored_image = ioctave1;

figure(7);
imshow(restored_image, []);
title('Restored Image');

%================================================================
%  PSNR
%================================================================
img = double(img);
disp("PSNR:");
[psnr, difference] = PSNR(img, restored_image);
fprintf('%.2f db\n', psnr);

%================================================================
%  FUNCTIONS
%================================================================
function filtered_img = dwt_octave(raw_img, stride, n, output_word_length, filter_word_length)
    [h, w] = size(raw_img);
    filtered_img = raw_img;
    partition = 2 ^ n;

    % Horizontal
    H1 = gn_HPF(raw_img(1:h / (partition / 2), 1:w / (partition / 2)), 1, filter_word_length);
    H1_ = downSampler(H1, stride, 0, n, 1);

    H1f = double(H1_);
    figure(7);
    imshow(H1f, []);
    title('H1_');

    L1 = hn_LPF(raw_img(1:h / (partition / 2), 1:w / (partition / 2)), 1, filter_word_length);
    L1_ = downSampler(L1, stride, 1, n, 1);

    L1f = double(L1_);
    figure(7);
    imshow(L1f, []);
    title('L1_');

    % Vertical!, i have problem here! The high pass components leads to some errors.
    HH = gn_HPF(H1_(1:h / (partition / 2), 1:w / partition), 0, filter_word_length);
    HH_ = downSampler(HH, stride, 0, n, 0);

    HL = hn_LPF(H1_(1:h / (partition / 2), 1:w / partition), 0, filter_word_length);
    HL_ = downSampler(HL, stride, 1, n, 0);

    LH = gn_HPF(L1_(1:h / (partition / 2), 1:w / partition), 0, filter_word_length);
    LH_ = downSampler(LH, stride, 0, n, 0);

    LL = hn_LPF(L1_(1:h / (partition / 2), 1:w / partition), 0, filter_word_length);
    LL_ = downSampler(LL, stride, 1, n, 0);
    % Trace till here, problems happens with LL_
    % Recombination
    filtered_img(1:h / partition, 1:w / partition) = LL_(1:h / partition, 1:w / partition);

    filtered_img(1:(h / partition), (w / partition) + 1:w / (partition / 2)) = HL_(1:h / partition, 1:w / partition);

    filtered_img((h / partition) + 1:(h / (partition / 2)), 1:(w / partition)) = LH_(1:h / partition, 1:w / partition);
    filtered_img((h / partition) + 1:(h / (partition / 2)), (w / partition) + 1:(w / (partition / 2))) = HH_(1:h / partition, 1:w / partition);

    filtered_img = fi(filtered_img, 1, output_word_length);

end

function reconstructed_img = idwt_octave(compressed_img, stride, n)

    [h, w] = size(compressed_img);
    partition = 2 ^ n;
    reconstructed_img = compressed_img;

    % Extraction
    LL_ = compressed_img(1:h / partition, 1:w / partition);
    LH_ = compressed_img((h / partition) + 1:(h / (partition / 2)), 1:(w / partition));

    HL_ = compressed_img(1:(h / partition), (w / partition) + 1:w / (partition / 2));
    HH_ = compressed_img((h / partition) + 1:(h / (partition / 2)), (w / partition) + 1:(w / (partition / 2)));

    % Vertical!
    LL = upSampler(LL_, stride, n, 1, 0);
    LL_test = LL(1:h / (partition / 2), 1:w / partition);
    LL(1:h / (partition / 2), 1:w / (partition)) = qn_LPF(LL_test, 0);

    % LH is wrong~ for the last 3 columns.
    LH = upSampler(LH_, stride, n, 0, 0);
    LH(1:h / (partition / 2), 1:w / (partition)) = pn_HPF(LH(1:h / (partition / 2), 1:w / partition), 0);

    s0 = LL + LH;

    HL = upSampler(HL_, stride, n, 1, 0);
    HL(1:h / (partition / 2), 1:w / (partition)) = qn_LPF(HL(1:h / (partition / 2), 1:w / partition), 0);

    HH = upSampler(HH_, stride, n, 0, 0);
    HH(1:h / (partition / 2), 1:w / (partition)) = pn_HPF(HH(1:h / (partition / 2), 1:w / partition), 0);

    % Minor difference in boundary of 160 colunms and rows.
    s1 = HL + HH;

    % Horizontal!
    s0_ = upSampler(s0, stride, n, 1, 1);
    disp("Size of s0_");
    disp(size(s0_));
    s0_ = qn_LPF(s0_, 1);

    s1_ = upSampler(s1, stride, n, 0, 1);
    disp("Size of s1_");
    disp(size(s1_));
    s1_ = pn_HPF(s1_, 1);

    s_temp = s0_ + s1_;

    reconstructed_img(1:h / (partition / 2), 1:w / (partition / 2)) = s_temp;

end

function downSampledimg = downSampler(img, stride, odd, n, horizontal)
    [h, w] = size(img);
    partition = 2 ^ n;
    % downSampledimg = img;
    downSampledimg = zeros(h);

    if horizontal == 1

        if odd == 0
            %even for HPF
            downSampledimg(1:h, 1:w / 2) = img(1:h, 2:stride:w);
        else
            %odd for LPF
            downSampledimg(1:h, 1:w / 2) = img(1:h, 1:stride:w);
        end

    else

        if odd == 0
            %even for HPF
            downSampledimg(1:h / 2, 1:w) = img(2:stride:h, 1:w);
        else
            %odd for LPF
            downSampledimg(1:h / 2, 1:w) = img(1:stride:h, 1:w);
        end

    end

end

function upSampledimg = upSampler(img, stride, n, odd, horizontal)
    % Interpolation algorithm should be adopted to further increase resolution after upSampling
    % n means nth dwt_octave
    [h, w] = size(img);
    partition = 2 ^ n;
    new_h = 2 * h;
    new_w = 2 * w;

    if horizontal == 1
        upSampledimg = zeros(h);

        if odd == 0
            %even for HPF
            upSampledimg(1:h, 2:stride:w) = img(1:h, 1:w / 2);
        else
            %odd for LPF
            upSampledimg(1:h, 1:stride:w) = img(1:h, 1:w / 2);
        end

    else
        upSampledimg = zeros(2 * h);
        % Vertical
        if odd == 0
            %even for HPF
            upSampledimg(2:stride:new_h, 1:new_w / 2) = img(1:h, 1:w);
        else
            %odd for LPF
            upSampledimg(1:stride:new_h, 1:new_w / 2) = img(1:h, 1:w);
        end

    end

end

function filtered_img = gn_HPF(raw_img, horizontal, word_length)
    wn = [-0.064538882629 0.040689417609 0.418092273222 ...
              -0.788485616406 ...
              0.418092273222 0.040689417609 -0.064538882629];
    fix_point = 1;
    wn = fi(wn, 1, word_length);

    [h, w] = size(raw_img);
    filtered_img = raw_img;

    if horizontal == 1
        %Horizontal filtering
        for i = 1:h
            row_img = raw_img(i, :);
            filtered_row = filterSystem(row_img, wn, w, fix_point, word_length);
            filtered_img(i, :) = filtered_row;
        end

    else
        % Vertical filtering
        for i = 1:w
            col_img = raw_img(:, i);
            filtered_col = filterSystem(col_img', wn, h, fix_point, word_length);
            filtered_img(:, i) = filtered_col;
        end

    end

end

function filtered_img = hn_LPF(raw_img, horizontal, word_length)
    wn = [0.037828455507 -0.023849465020 -0.110624404418 0.377402855613 ...
              0.852698679009 ...
              0.377402855613 -0.110624404418 -0.023849465020 0.037828455507];

    fix_point = 1;

    wn = fi(wn, 1, word_length);

    [h, w] = size(raw_img);
    filtered_img = raw_img;

    if horizontal == 1
        %Horizontal filtering
        for i = 1:h
            row_img = raw_img(i, :);
            filtered_row = filterSystem(row_img, wn, w, fix_point, word_length);
            filtered_img(i, :) = filtered_row;
        end

    else
        % Vertical filtering
        for i = 1:w
            col_img = raw_img(:, i);
            filtered_col = filterSystem(col_img', wn, h, fix_point, word_length);
            filtered_img(:, i) = filtered_col;
        end

    end

end

function filtered_img = qn_LPF(raw_img, horizontal)
    wn = [-0.064538882629 -0.040689417609 0.418092273222 0.788485616406 ...
              0.418092273222 -0.040689417609 -0.064538882629];

    fix_point = 0;

    [h, w] = size(raw_img);
    filtered_img = raw_img;

    if horizontal == 1
        %Horizontal filtering
        for i = 1:h
            row_img = raw_img(i, :);
            filtered_row = filterSystem(row_img, wn, w, fix_point, 32);
            filtered_img(i, :) = filtered_row;
        end

    else
        % Vertical filtering
        for i = 1:w
            col_img = raw_img(:, i);
            filtered_col = filterSystem(col_img', wn, h, fix_point, 32);
            filtered_img(:, i) = filtered_col;
        end

    end

end

function filtered_img = pn_HPF(raw_img, horizontal)
    wn = [-0.037828455507 -0.023849465020 0.110624404418 0.377402855613 ...
              -0.852698679009 0.377402855613 0.110624404418 -0.023849465020 ...
              -0.037828455507];

    fix_point = 0;

    [h, w] = size(raw_img);
    filtered_img = raw_img;

    if horizontal == 1
        %Horizontal filtering
        for i = 1:h
            row_img = raw_img(i, :);
            filtered_row = filterSystem(row_img, wn, w, fix_point, 32);
            filtered_img(i, :) = filtered_row;
        end

    else
        % Vertical filtering
        for i = 1:w
            col_img = raw_img(:, i);
            filtered_col = filterSystem(col_img', wn, h, fix_point, 32);
            filtered_img(:, i) = filtered_col;
        end

    end

end

% Filter
function yn = filterSystem(xn, wn, N, fix_point, word_length)
    N = length(xn);
    M = size(wn, 2);
    L = fix(M / 2); % extend size // 2

    if fix_point == 1
        yn = fi(zeros(1, N), 1, word_length);
    else
        yn = zeros(1, N); % result
    end

    x = [flip(xn(2:L + 1)), xn, flip(xn(N - L:N - 1))]; % Symmetric extension!
    x = fi(x,1,word_length);

    for i = 1:N
        yn(i) = wn * x(1, i:i + M - 1)';
    end

end

function [psnr, difference] = PSNR(img, filtered_img)
    [h, w] = size(img);
    MAXI = 255;
    difference = (img - filtered_img) .^ 2;
    MSE = sum(difference, "all") / (h * w);

    psnr = 10 * log10(MAXI ^ 2 / MSE);
end
