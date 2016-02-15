
figure ('name','vx(t), vy(t), const step');
set(gcf,'Position',get(0,'Screensize')/1) % enlarge image to ( .../1.5) full screen

str1 = sprintf('Velocity \n vx(0)= %d,  vy(0) = %d, step = %d', vx(1), vy(1), param.dt);
str2 = sprintf('Position \n x(0)= %d,  y(0) = %d, step = %d', x(1), y(1), param.dt);
str3 = sprintf('Acceleration \n ax(0)= %d,  ay(0) = %d, step = %d', ax(1), ay(1), param.dt);
srt_file = sprintf(' vx1(0)=%d_vy(0)=%d_step=%d', vx(1), vy(1), param.dt);
srt_file = strrep(srt_file, '.', ','); %zamieniamy '.' na ',' w nazwie pliku aby sie kompilowalo w latexie

subplot(3,1,1)       % add first plot in 3 x 1 grid
plot(przedzial,x, przedzial,y);
title( str2)
grid on;
xlabel('t');
ylabel('x, y');
legend('x(t)', 'y(t)');

subplot(3,1,2)       % add second plot in 3 x 1 grid
plot(przedzial,vx, przedzial,vy);
grid on;
xlabel('t');
ylabel('vx, vy');
title(str1);
legend('vx(t)', 'vy(t)');

subplot(3,1,3)       % add third plot in 3 x 1 grid
plot(przedzial,ax, przedzial,ay);
title( str3)
grid on;
xlabel('t');
ylabel('ax, ay');
legend('ax(t)', 'ay(t)');

print('-djpeg','-r300',srt_file);