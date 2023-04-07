function filtered_img = dwt(raw_img, stride, T)

    % Octave 1
    octave1 = octave(raw_img, stride, 1,T);

    % Octave 2
    octave2 = octave(octave1, stride, 2,T);

    % Octave 3
    filtered_img = octave(octave2, stride, 3,T);

end
