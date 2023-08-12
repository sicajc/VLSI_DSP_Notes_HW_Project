clear all;

% Note sequence starting from 1~60
Sample_size = 100;
n = 1:Sample_size;
L = 15;
mu = 0.01;

%Input signal xn(n)
xn = sin(2 * pi * (n / 12)) + cos(2 * pi * (n / 4));
dn = sin(2 * pi * (n / 12));

%plot of original signal for 50 equally sampled value
figure(1);
sampleSteps = 1;
coefficient_steps = 1;
coefficient_spaced = 1:coefficient_steps:Sample_size;
n_spaced = 1:sampleSteps:Sample_size;
subplot(2, 2, 1);
stem(xn(n_spaced));
title('sin(2 * pi * n / 12) + cos(2 * pi * n / 4)'); xlabel('n*sampleSteps'); ylabel('Amplitude');

subplot(2, 2, 2);
stem(dn(n_spaced));
title('Desired output signal sin(2 * pi * n / 12)'); xlabel('n*sampleSteps'); ylabel('Amplitude');

% Adaptive Filter, Look for the minimum samples to reach 10% of LMS
[wn_in_time, rn, wn, dn_hat, en, steps] = lms(xn, dn, mu, L);

% Plot of dn_hat
subplot(2, 2, 3);
stem(dn_hat(n_spaced));
title('Estimated desired output from adaptive filter'); xlabel('n*sampleSteps'); ylabel('Amplitude');

% Plot of rn
subplot(2, 2, 4);
plot(rn(n_spaced));
title('RMS in time'); xlabel('n*sampleSteps'); ylabel('Amplitude');

disp("RMS final value");
% Since it might not converge, if the value converges, the value is stored in rn(steps), otherwise rn(steps-1)
if Sample_size > 10000
    disp(rn(steps-1));
else
    disp(rn(steps));
end

disp("Total Steps needed to reach 10% of RMS");
disp(steps);
% Plot of Coefficients v.s. steps
figure(2);
wn_in_time = wn_in_time';
stem(wn_in_time(coefficient_spaced, :));
title('Coefficients of bi'); xlabel('n*coefficient steps'); ylabel('Amplitude');

% FFT for the impulse response of converged filters.
N = 64;
wn_padded = zeros(1, N);
wn_padded(1:L) = wn;

figure(3);

Y = fft(wn_padded, N);
stem(Y); % Note must use stem.

function [wn_in_time, rn, wn, dn_hat, en, steps] = lms(xn, dn, mu, L)

    N = length(xn); %Length of input signals
    wn = zeros(1, L); %initialize filter coefficients
    dn_hat = zeros(1, N); % Initialize outputs
    rn = zeros(1, N);
    en = dn - dn_hat; % Error vectors, set as the difference of two signals
    disp(en);
    en_initial = en(1:16); % Latest 16 prediction error
    steps = 1; %Steps needed to reach the optimal value
    wn_in_time = zeros(L, N);

    desired_rn = 0.1/sqrt(2);
    disp("Desired RMS value");
    disp(desired_rn);

    % FIR filter, constructed from the equation of FIR filter.
    % Starting from Lth signal all the way till length of the whole signals.
    for n = L:N
        % The L-tap coefficient vector
        x1 = xn(n:-1:n - L + 1);
        %Convolution
        dn_hat(n) = wn * x1';
        %Error vector, due to the first 16 differences 1~16 is occ
        en(n+2) = dn(n) - dn_hat(n);
        %LMS algorithm
        wn = wn + mu * en(n+2) * x1;

        wn_in_time(:, steps) = wn;

        % RMS calculation
        en_latest = en(n+1:-1:n - L + 1); % The latest 16 errors of error vector.
        % disp("Latest 16 errors");
        % disp(en_latest);
        rn(steps) = RMS(en_latest, L);

        if rn(steps) <= desired_rn
            break;
        else
            steps = steps + 1;
        end

    end

end

function r = RMS(en, L)
    N = length(en); %Length of input signal
    sum = 0;

    r = sqrt(mean(en.^2));

end