
clear, clc

fname = 'CrossSectiondata_advection.dat'; % filename
data = load (fname);
data = data'; % first row - timestep, next rows - temp along nodes at y/2
time_column1 = 5; % from which column(time) --> plot data
time_column2 = 19;

figure(1)
hold on
plot(data(2:end,time_column1),'r'); % LBM 
plot(data(2:end,time_column2),'b'); % LBM 
hold off
grid on

xlabel('x')
ylabel('Temperature')
set(gcf,'Position',get(0,'Screensize')/1) % enlarge image to ( .../1.5) full screen
str_legend1 = sprintf('t = %0.1f',data(1,time_column1));
str_legend2 = sprintf('t = %0.1f',data(1,time_column2));
legend(str_legend1,str_legend2,'Location','best' );
%legend('t = 0.1','t = 5','t = 100','Location','best')

str_title = sprintf('Temperature: advection at t = %0.1f, t = %0.1f', data(1,time_column1),data(1,time_column2));
title(str_title );