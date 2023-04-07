function filtered_img = gn_HPF(raw_img, horizontal, T)
    wn = [-0.064538882629 0.040689417609 0.418092273222 ...
              -0.788485616406 ...
              0.418092273222 0.040689417609 -0.064538882629];

    wn = cast(wn, 'like', T.filter_coef);
    dwt_mode = 1;

    [h, w] = size(raw_img);
    filtered_img = cast(raw_img, 'like', T.filter_coef);

    if horizontal == 1
        %Horizontal filtering
        for i = 1:h
            row_img = cast(raw_img(i, :), 'like', T.filter_coef);
            filtered_row = filterSystem(row_img, wn, w, T,dwt_mode);
            filtered_img(i, :) = filtered_row;
        end

    else
        % Vertical filtering
        for i = 1:w
            col_img = cast(raw_img(:, i), 'like', T.filter_coef);
            filtered_col = filterSystem(col_img', wn, h, T,dwt_mode);
            filtered_img(:, i) = filtered_col;
        end

    end

end
