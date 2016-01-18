clc, clear

fname = 'CrossSectiondata.dat'; % filename
data = load (fname);
data = data'; % first row - timestep, next rows - temp along nodes at y/2

time_column = 11; % from which column(time) --> plot data

plot(data(2:end,time_column));
grid on;