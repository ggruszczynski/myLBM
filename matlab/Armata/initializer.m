



% lets define a steel ball
d = 0.1; % diameter [m]
rhoSteel = 7800; % density of steel [kg/m3]

%% parameters - these are const, which are used within functions


%param.S=0.001; % reference area [m2]
%param.m=0.01;  % mass of the bullet [kg]

param.S=pi*d^2 /4; % reference area [m2]
param.C=0.5;   % drag coefficient [-]
param.q=1.2;   % air density [kg/m3]
param.g=9.81;  % gravity acceleration [m/s2]
param.m= 4/3* pi*d^3 /8;  % mass of the bullet [kg]

param.Ct=param.q*param.S*param.C/2; % total drag coeff [-]

param.dt = 1e-2; %  time step
param.przedzial = 0 : param.dt : 0.4; %simulation time

param.xT = 0.4; % target
param.yT = 0.1;
