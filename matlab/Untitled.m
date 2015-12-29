clc, clear

addpath('acf');

lags = 100;


% rng(1); % For reproducibility
% y = randn(1000, 1);
% plot(y)
% 
% y_autocorr = acf(y, lags); 
% plot(y_autocorr);


fs = 1000;                                % Sample frequency (Hz)
t = 0:  1/fs:  10-1/fs;                  % 10 sec sample -> start:step:end
x_dirty = (1.3)*sin(2*pi*15*t) ...             % 15 Hz component
  + (1.7)*sin(2*pi*40*(t-2)) ...         % 40 Hz component
  + 2.5*gallery('normaldata',size(t),4); % Gaussian noise;


x_clean  = (1.3)*sin(2*pi*15*t) ...             % 15 Hz component
         + (1.7)*sin(2*pi*40*(t-2));            % 40 Hz componen
     
x_autocorr = acf(x_dirty', lags);

plot(t,x_clean);
plot(x_autocorr);