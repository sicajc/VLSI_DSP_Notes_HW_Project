function filtered_img = hn_LPF(raw_img, horizontal, T)
    wn = [0.037828455507 -0.023849465020 -0.110624404418 0.377402855613 ...
              0.852698679009 ...
              0.377402855613 -0.110624404418 -0.023849465020 0.037828455507];

    wn = cast(wn, 'like', T.filter_coef);

    dwt_mode = 1;

    [h, w] = size(raw_img);
    %Outputs
    filtered_img = cast(raw_img, 'like', T.lv1_output);

    if horizontal == 1
        %Horizontal filtering
        for i = 1:h
            row_img = raw_img(i, :);

            % row_img = cast(raw_img(i, :), 'like', T.filter_coef);
            filtered_row = filterSystem(row_img, wn, w, T,dwt_mode);
            filtered_img(i, :) = filtered_row;
        end

    else
        % Vertical filtering
        for i = 1:w
            col_img = raw_img(:, i);

            % col_img = cast(raw_img(:, i), 'like', T.filter_coef);
            filtered_col = filterSystem(col_img', wn, h, T,dwt_mode);
            filtered_img(:, i) = filtered_col;
        end

    end

end
