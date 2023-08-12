% filtered_img(:,1:2:end) means from the matrix filtered_img selects its odds column vectors
% filtered_img(:,2:2:end) means from the matrix filtered_img selects its even column vectors

% Expected Result
for i = 1:n
    % The image becomes smaller and smaller
    filtered_img(1:w, 1:h) = [filtered_img(1:w, 1:2:h) + filtered_img(1:w, 2:2:h) filtered_img(1:w, 1:2:h) - filtered_img(1:w, 2:2:h)];
    filtered_img(1:w, 1:h) = [filtered_img(1:2:w, 1:h) + filtered_img(2:2:w, 1:h); filtered_img(1:2:w, 1:h) - filtered_img(2:2:w, 1:h)];

    w = w / 2;
    h = h / 2;

end

The bracket is added for auto interpolation due to overflow.
imshow(filtered_img, []);