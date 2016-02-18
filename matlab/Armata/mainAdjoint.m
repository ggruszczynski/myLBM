clc, clear;
disp('strzal z armaty - met Eulera');

initializer;

V0 = 1; % predkosc poczatkowa [m/s]
angle = 45; % kat wystrzalu [deg]
vx(1) = V0*cosd(angle); 	 
vy(1) = V0*sind(angle); 	 
x(1) = 0; 	  % polozenie poczatkowe
y(1) = 10;

n=1; % indeks startowy

tic

X = [vx,vy, x,y];

while n < numel(przedzial);
%     X(:,n+1) = VPstep(X, param  ) ;
    Y= VPstep(X, param  ) ;
    [ ax(n), ay(n) ] = oneStepAcceleration(vx(n),vy(n),param);   
    n = n + 1;
end
 ax(n) = 0;
 ay(n) = 0;
toc

% recover values




% Wykresy