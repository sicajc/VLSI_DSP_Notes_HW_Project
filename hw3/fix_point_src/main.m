WL = 22;
FL = 10;

odd = 0;
horizontal = 1;
zero_padded = 0;

% Broadcasting data types.
T = filterDataType('fixed', WL, FL);

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
    -args {img_fixed,stride,T} -histogram

H1_ = dwt_mex(img_fixed,stride,T);

H1f = double(H1_);
figure(7);
imshow(H1f, []);
title('H1_');

%================================================================
%  IDWT
%================================================================
restored_image = idwt(H1f,stride,zero_padded);

%================================================================
%  PSNR
%================================================================
img = double(img);
disp("PSNR:");
[psnr, difference] = PSNR(img, restored_image);
fprintf('%.2f db\n', psnr);


% Verify results
showInstrumentationResults dwt_mex
    % -proposeFL -defaultDT numerictype(1, 16)

% Code generation
codegen dwt ...
    -args {img_fixed, stride,T} -config:lib -report
