clc, clear;
disp('strzal z armaty - met Eulera');
addpath(genpath('myAutomaticDifferentiation'));
addpath(genpath('ADRozgrzewka2'));
initializer;

% V0 = 2; % predkosc poczatkowa [m/s]
% angle = 45; % kat wystrzalu [deg]
% 
% vx0 = V0*cosd(angle); 	 
% vy0 = V0*sind(angle); 	
vx(1) = 1;
vy(1) = 1.5;
x0 = 0; 	  % polozenie poczatkowe
y0 = 0;

dvx = 0; % correction
dvy = 0;

tic;
iMax = 500;
for i = 1: iMax
    [DJ(:,i), historia{i}]=   Celowanie1step(vx(i), vy(i), x0, y0,param);
    dvx(i) = DJ(1,i);
    dvy(i) = DJ(2,i);
    
    dvstep = 1;
    vx(i+1) = vx(i) - dvstep * dvx(i);
    vy(i+1) = vy(i) - dvstep * dvy(i);
    xError(i) = param.xT - historia{i}.xLast;
    yError(i) = param.yT - historia{i}.yLast;
    i
end
totaltime = toc;
fprintf('\n total time %d \n iteration: %d \n',totaltime, totaltime/i)


subplot(3,1,1)       % add first plot in 2 x 1 grid
title('x, y - kolejne strzaly');
hold on
grid on
plot(xError)
plot(yError)
hold off
legend('xError(iter)', 'yError(iter)');

subplot(3,1,2)       % add second plot in 2 x 1 grid
title('predkosci');
grid on
plot(1:i+1,vx, 1:i+1, vy)
legend('vx(iter)', 'vy(iter)');
 
subplot(3,1,3)       % add first plot in 2 x 1 grid
title('last shot - polozenie');
hold on
grid on
plot(historia{i}.all(:,3))
plot(historia{i}.all(:,4))
hold off
legend('x(t)', 'y(t)');

%% wykresiki
% subplot(2,1,1)       % add first plot in 2 x 1 grid
% title('polozenie');
% grid on
% hold on
% plot(historia{i}.all(:,3))
% plot(historia{i}.all(:,4))
% hold off
% legend('x(t)', 'y(t)');
% 
% subplot(2,1,2)       % add second plot in 2 x 1 grid
% title('predkosci');
% grid on
% hold on
% plot(historia{i}.all(:,1))
% plot(historia{i}.all(:,2))
% hold off
% legend('vx(t)', 'vy(t)');


% Wykresy