clc,clear
%Wall force (@lid) in Couete flow
uLid = 0.1;
nu = 0.1;
length = 256;
height = 128;

F = nu*uLid*length/height