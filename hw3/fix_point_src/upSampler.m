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