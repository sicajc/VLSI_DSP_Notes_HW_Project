% Filter
function yn = filterSystem(xn, wn, N, T, dwt_mode)
    N = length(xn);
    M = size(wn, 2);
    L = fix(M / 2); % extend size // 2

    if dwt_mode == 1
        yn = zeros(1, N); % result
        yn = cast(yn, 'like', xn);
    else
        yn = zeros(1, N); % result
    end

    x = [flip(xn(2:L + 1)), xn, flip(xn(N - L:N - 1))]; % Symmetric extension!

    for i = 1:N
        yn(i) = wn * x(1, i:i + M - 1)';
    end

end
