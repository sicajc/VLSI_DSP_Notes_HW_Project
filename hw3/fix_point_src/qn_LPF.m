function filtered_img = qn_LPF(raw_img, horizontal)
    wn = [-0.064538882629 -0.040689417609 0.418092273222 0.788485616406 ...
              0.418092273222 -0.040689417609 -0.064538882629];

    T = 0;
    dwt_mode = 0;
    [h, w] = size(raw_img);
    filtered_img = raw_img;

    if horizontal == 1
        %Horizontal filtering
        for i = 1:h
            row_img = raw_img(i, :);
            filtered_row = filterSystem(row_img, wn, w, T, dwt_mode);
            filtered_img(i, :) = filtered_row;
        end

    else
        % Vertical filtering
        for i = 1:w
            col_img = raw_img(:, i);
            filtered_col = filterSystem(col_img', wn, h, T, dwt_mode);
            filtered_img(:, i) = filtered_col;
        end

    end

end
