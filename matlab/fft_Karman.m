clc, clear

fname = 'PointData.dat'; % filename
data = load (fname);
 
t = data(:,1);
vx = data(:,2);
vy = data(:,3);
vTot = data(:,4);


% t = data(4000:end,1);
% vx = data(4000:end,2);
% vy = data(4000:end,3);
% vTot = data(4000:end,4);

figure ('name','Signal');
plot (t,vx,t,vy,t,vTot);
title('Signal')
legend('vx','vy','vTot');
xlabel('time (lattice)')

%% try autocor
addpath('acf');
lags = numel(vTot) - 1;
x_autocorr = acf(vTot, lags);


figure ('name','autocor');
plot (x_autocorr);
title('Signal - autocorrelation')
legend('x autocorr');
xlabel('hmm')

%fft from autocorrelation
 fs = 20;                                % Sample frequency (Hz)
% %t = 0:1/fs:10-1/fs;                      % 10 sec sample

x = x_autocorr;

m = length(x);          % Window length
n = pow2(nextpow2(m));  % Transform length
y = fft(x,n);           % DFT
f = (0:n-1)*(fs/n);     % Frequency range
power = y.*conj(y)/n;   % Power of the DFT

%To visualize the DFT, plots of abs(y), abs(y).^2, and log(abs(y)) are all common. A plot of power versus frequency is called a periodogram.
% plot(f,abs(y))
figure ('name','fft');
plot(f,power)
xlabel('Frequency (Hz)')
ylabel('Power')
title('{\bf Periodogram}')
legend('x - signal after autocorrelation');

%% Use fft to compute the DFT y and its power.
%  fs = 1;                                % Sample frequency (Hz)

x = vTot;

m = length(x);          % Window length
n = pow2(nextpow2(m));  % Transform length
y = fft(x,n);           % DFT
f = (0:n-1)*(fs/n);     % Frequency range
power = y.*conj(y)/n;   % Power of the DFT

%% To visualize the DFT, plots of abs(y), abs(y).^2, and log(abs(y)) are all common. A plot of power versus frequency is called a periodogram.
% plot(f,abs(y))
figure ('name','fft');
plot(f,power)
xlabel('Frequency (Hz)')
ylabel('Power')
title('{\bf Periodogram}')
legend('x - pure signal');

%% garbage
% n = [0:29];
% x = cos(2*pi*n/10);5
% N1 = 1000;
% X1 = abs(fft(x,N1));
% F1 = [0 : N1 - 1]/N1;
% plot(F1,X1,'-x');
