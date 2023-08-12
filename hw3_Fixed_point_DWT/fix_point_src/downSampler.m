function downSampledimg = downSampler(img, stride, odd, n, horizontal,T)
    [h, w] = size(img);
    partition = 2 ^ n;
    downSampledimg = cast(zeros(h),'like',img);

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