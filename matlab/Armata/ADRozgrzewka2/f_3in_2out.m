function [out1, out2] = f_3in_2out( X )
%F_3IN_2OUT Summary of this function goes here
%   Detailed explanation goes here


x = X(1);
y = X(2);
z = X(3);

out1 = 10*x + 15*y*x + exp(z); %3*x^2 + 7*x + 8*y + z +5;

out2 =  3*x^2 + 7*x + 8*y + z +5;

% OUT = [out1, out2];
end

