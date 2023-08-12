function reconstructed_img = idwt_octave(compressed_img, stride, n)

    [h, w] = size(compressed_img);
    partition = 2 ^ n;
    reconstructed_img = compressed_img;

    % Extraction
    LL_ = compressed_img(1:h / partition, 1:w / partition);
    LH_ = compressed_img((h / partition) + 1:(h / (partition / 2)), 1:(w / partition));

    HL_ = compressed_img(1:(h / partition), (w / partition) + 1:w / (partition / 2));
    HH_ = compressed_img((h / partition) + 1:(h / (partition / 2)), (w / partition) + 1:(w / (partition / 2)));

    % Vertical!
    LL = upSampler(LL_, stride, n, 1, 0);
    LL_test = LL(1:h / (partition / 2), 1:w / partition);
    LL(1:h / (partition / 2), 1:w / (partition)) = qn_LPF(LL_test, 0);

    % LH is wrong~ for the last 3 columns.
    LH = upSampler(LH_, stride, n, 0, 0);
    LH(1:h / (partition / 2), 1:w / (partition)) = pn_HPF(LH(1:h / (partition / 2), 1:w / partition), 0);

    s0 = LL + LH;

    HL = upSampler(HL_, stride, n, 1, 0);
    HL(1:h / (partition / 2), 1:w / (partition)) = qn_LPF(HL(1:h / (partition / 2), 1:w / partition), 0);

    HH = upSampler(HH_, stride, n, 0, 0);
    HH(1:h / (partition / 2), 1:w / (partition)) = pn_HPF(HH(1:h / (partition / 2), 1:w / partition), 0);

    % Minor difference in boundary of 160 colunms and rows.
    s1 = HL + HH;

    % Horizontal!
    s0_ = upSampler(s0, stride, n, 1, 1);
    disp("Size of s0_");
    disp(size(s0_));
    s0_ = qn_LPF(s0_, 1);

    s1_ = upSampler(s1, stride, n, 0, 1);
    disp("Size of s1_");
    disp(size(s1_));
    s1_ = pn_HPF(s1_, 1);

    s_temp = s0_ + s1_;

    reconstructed_img(1:h / (partition / 2), 1:w / (partition / 2)) = s_temp;

end
