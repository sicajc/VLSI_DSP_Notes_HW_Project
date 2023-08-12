function filtered_img = hn_LPF(raw_img, horizontal, T,stage)
    wn = [0.037828455507 -0.023849465020 -0.110624404418 0.377402855613 ...
              0.852698679009 ...
              0.377402855613 -0.110624404418 -0.023849465020 0.037828455507];

    wn = cast(wn, 'like', T.filter_coef);

    dwt_mode = 1;

    [h, w] = size(raw_img);

    switch stage
        case 1
            output_type = T.lv1_output;
        case 2
            output_type = T.lv2_output;
        case 3
            output_type = T.lv3_output;
    end

    % Output types
    filtered_img = cast(raw_img, 'like', output_type);

    if horizontal == 1
        %Horizontal filtering
        for i = 1:h
            row_img = filtered_img(i, :);

            % row_img = cast(raw_img(i, :), 'like', T.filter_coef);
            filtered_img(i, :) = filterSystem(row_img, wn, w, T, dwt_mode);
        end

    else
        % Vertical filtering
        for i = 1:w
            col_img = filtered_img(:, i);

            % col_img = cast(raw_img(:, i), 'like', T.filter_coef);
            filtered_img(:, i) = filterSystem(col_img', wn, h, T, dwt_mode);
        end

    end

end
