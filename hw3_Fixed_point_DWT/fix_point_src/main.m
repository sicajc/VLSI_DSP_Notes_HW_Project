filter_coef.WL = 11;
filter_coef.FL = 10;

lv1_output.WL = 10;
lv1_output.FL = 0;

lv2_output.WL = 11;
lv2_output.FL = 0;

lv3_output.WL = 12;
lv3_output.FL = 0;

odd = 0;
horizontal = 1;
zero_padded = 0;

% Broadcasting data types.
T = filterDataType('double', filter_coef, lv1_output, lv2_output, lv3_output);

%================================================================
%  RD image
%================================================================
img = double(imread('image.bmp'));
img_fixed = cast(img, 'like', T.lv3_output);

[h, w] = size(img_fixed);
n = 1;
stride = 2;

%================================================================
%  DWT
%================================================================
buildInstrumentedMex dwt -o dwt_mex ...
    -args {img_fixed, stride, T} -histogram

H1_ = dwt_mex(img_fixed, stride, T);

H1f = double(H1_);
figure(7);
imshow(H1f, []);
title('H1_');

%================================================================
%  IDWT
%================================================================
restored_image = idwt(H1f, stride, zero_padded);

%================================================================
%  PSNR
%================================================================
img = double(img);
disp("PSNR:");
[psnr, difference] = PSNR(img, restored_image);
fprintf('%.2f db\n', psnr);

% Verify results
% Show instrumentatinResults can suggest you the optimal width you should use for the best result
showInstrumentationResults dwt_mex -proposeWL -defaultDT numerictype(1,16,4)

% Code generation
codegen dwt ...
    -args {img_fixed, stride, T} -config:lib -report
