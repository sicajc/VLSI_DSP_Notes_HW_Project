function restored_image = idwt(raw_img, stride, zero_padded)
    %================================================================
    %  IDWT
    %================================================================
    [h, w] = size(raw_img);
    octave3_ = zeros(h);

    if zero_padded == 1
        octave3_(1:h / 2, 1:w / 2) = raw_img(1:h / 2, 1:w / 2);
    else
        octave3_ = raw_img;
    end

    ioctave3 = idwt_octave(octave3_, stride, 3);

    ioctave2 = idwt_octave(ioctave3, stride, 2);

    ioctave1 = idwt_octave(ioctave2, stride, 1);

    restored_image = ioctave1;

    figure(7);
    imshow(restored_image, []);
    title('Restored Image');

end
