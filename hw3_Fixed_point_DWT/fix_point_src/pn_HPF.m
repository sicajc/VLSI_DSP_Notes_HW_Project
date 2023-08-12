function filtered_img = pn_HPF(raw_img, horizontal)
    wn = [-0.037828455507 -0.023849465020 0.110624404418 0.377402855613 ...
              -0.852698679009 0.377402855613 0.110624404418 -0.023849465020 ...
              -0.037828455507];
    T = 0;
    dwt_mode = 0;
    [h, w] = size(raw_img);
    filtered_img = raw_img;

    if horizontal == 1
        %Horizontal filtering
        for i = 1:h
            row_img = raw_img(i, :);
            filtered_row = filterSystem(row_img, wn, w,T,dwt_mode);
            filtered_img(i, :) = filtered_row;
        end

    else
        % Vertical filtering
        for i = 1:w
            col_img = raw_img(:, i);
            filtered_col = filterSystem(col_img', wn, h,T,dwt_mode);
            filtered_img(:, i) = filtered_col;
        end

    end

end