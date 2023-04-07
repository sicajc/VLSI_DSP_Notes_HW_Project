function filtered_img = gn_HPF(raw_img, horizontal, T, stage)
    wn = [-0.064538882629 0.040689417609 0.418092273222 ...
              -0.788485616406 ...
              0.418092273222 0.040689417609 -0.064538882629];

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

    filtered_img = cast(raw_img, 'like', output_type);


    if horizontal == 1
        %Horizontal filtering
        for i = 1:h
            row_img = filtered_img(i,:);
            filtered_img(i, :) = filterSystem(row_img, wn, w, T, dwt_mode);
        end

    else
        % Vertical filtering
        for i = 1:w
            col_img = filtered_img(:,i);
            filtered_img(:, i) = filterSystem(col_img', wn, h, T, dwt_mode);
        end

    end

end
