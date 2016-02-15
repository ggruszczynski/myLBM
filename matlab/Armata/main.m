clc, clear;
disp('strzal z armaty - met Eulera');

%% parameters
% lets define a steel ball
d = 0.1; % diameter [m]
rhoSteel = 7800; % density of steel [kg/m3]

%param.S=0.001; % reference area [m2]
%param.m=0.01;  % mass of the bullet [kg]

param.S=pi*d^2 /4; % reference area [m2]
param.C=0.5;   % drag coefficient [-]
param.q=1.2;   % air density [kg/m3]
param.g=9.81;  % gravity acceleration [m/s2]
param.m= 4/3* pi*d^3 /8;  % mass of the bullet [kg]

param.Ct=param.q*param.S*param.C/2; % total drag coeff [-]

param.dt = 1e-3; %  time step

przedzial = 0 : param.dt : 10;

V0 = 1; % predkosc poczatkowa [m/s]
angle = 45; % kat wystrzalu [deg]
vx(1) = V0*cosd(angle); 	 
vy(1) = V0*sind(angle); 	 
x(1) = 0; 	  % polozenie poczatkowe
y(1) = 10;

n=1; % indeks startowy

tic
while n < numel(przedzial);
    [ vx(n+1),  vy(n+1)] = oneStepVelocity(vx(n),vy(n),param);
    [ x(n+1),  y(n+1)] = oneStepPosition(x(n),vx(n), y(n), vy(n), param.dt);
    [ ax(n), ay(n) ] = oneStepAcceleration(vx(n),vy(n),param);
    
    if y(n+1) < 0 % ground
        przedzial = przedzial(1:n+1);
        ax(n+1) = 0;
        ay(n+1) = 0;
        break;
    end
    n = n + 1;
end
toc

Wykresy