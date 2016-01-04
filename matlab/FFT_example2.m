clear,clc
%% Consider the following data x with two component frequencies of differing amplitude and phase buried in noise.
fs = 100;                                % Sample frequency (Hz)
t = 0:  1/fs:  10-1/fs;                  % 10 sec sample -> start:step:end
%t = 0:0.001:10;
x = (1.3)*sin(2*pi*15*t) ...             % 15 Hz component
  + (1.7)*sin(2*pi*40*(t-2)) ...         % 40 Hz component
  + 2.5*gallery('normaldata',size(t),4); % Gaussian noise;

plot(t,x);

%% Use fft to compute the DFT y and its power.

m = length(x);          % Window length
n = pow2(nextpow2(m));  % Transform length
y = fft(x,n);           % DFT
f = (0:n-1)*(fs/n);     % Frequency range
power = y.*conj(y)/n;   % Power of the DFT

%% To visualize the DFT, plots of abs(y), abs(y).^2, and log(abs(y)) are all common. A plot of power versus frequency is called a periodogram.

plot(f,power)
%plot(f,abs(y))
xlabel('Frequency (Hz)')
ylabel('Power')
title('{\bf Periodogram}')