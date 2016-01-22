% Gauss
clc, clear

x = 0 : 0.01: 150; 

ni = 75;
Sig = 20;
YScaleFactor = 5;


f = 1/(Sig*2*pi)*exp((-(x-ni).^2)/(2*Sig*Sig));
f= f* YScaleFactor;
%f = exp((-(x-ni).^2));

plot(x,f);