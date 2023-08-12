function filtered_img = octave(raw_img, stride, n, T)
    [h, w] = size(raw_img);

    switch n
        case 1
            output_type = T.lv1_output;
        case 2
            output_type = T.lv2_output;
        case 3
            output_type = T.lv3_output;
    end

    filtered_img = cast(raw_img, 'like', output_type);
    partition = 2 ^ n;

    % Horizontal
    H1 = gn_HPF(raw_img(1:h / (partition / 2), 1:w / (partition / 2)), 1, T, n);
    H1_ = downSampler(H1, stride, 0, n, 1, T);

    L1 = hn_LPF(raw_img(1:h / (partition / 2), 1:w / (partition / 2)), 1, T, n);
    L1_ = downSampler(L1, stride, 1, n, 1, T);

    % Vertical!, i have problem here! The high pass components leads to some errors.
    HH = gn_HPF(H1_(1:h / (partition / 2), 1:w / partition), 0, T, n);
    HH_ = downSampler(HH, stride, 0, n, 0, T);

    HL = hn_LPF(H1_(1:h / (partition / 2), 1:w / partition), 0, T, n);
    HL_ = downSampler(HL, stride, 1, n, 0, T);

    LH = gn_HPF(L1_(1:h / (partition / 2), 1:w / partition), 0, T, n);
    LH_ = downSampler(LH, stride, 0, n, 0, T);

    LL = hn_LPF(L1_(1:h / (partition / 2), 1:w / partition), 0, T, n);
    LL_ = downSampler(LL, stride, 1, n, 0, T);

    % Trace till here, problems happens with LL_
    % Recombination
    filtered_img(1:h / partition, 1:w / partition) = LL_(1:h / partition, 1:w / partition);

    filtered_img(1:(h / partition), (w / partition) + 1:w / (partition / 2)) = HL_(1:h / partition, 1:w / partition);

    filtered_img((h / partition) + 1:(h / (partition / 2)), 1:(w / partition)) = LH_(1:h / partition, 1:w / partition);
    filtered_img((h / partition) + 1:(h / (partition / 2)), (w / partition) + 1:(w / (partition / 2))) = HH_(1:h / partition, 1:w / partition);

end
