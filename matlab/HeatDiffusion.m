clear, clc
% solve heat diffusion eq: u_t = k*u_xx
% with BC: 
% u(x,0) = a for x > b
% u(x,0) = 0 elsewhere

domain_legth = 200;
x = -domain_legth : 1:domain_legth; 
t = [1000 2000]; % time 
TempMax = 499;
k = 0.25;
b = 0; % 0 - in the middle
figure(1)
hold on

for i = 1:2
    u(i,:) = (TempMax/2)*(erf((x-b)/sqrt(4*k*t(i))));
    %plot(x,u(i,:))
end


% some weird transformation to fit the plot...
 u = u + TempMax/2 + 1;
 x = x + domain_legth ;

fname = 'CrossSectiondata.dat'; % filename
data = load (fname);
data = data'; % first row - timestep, next rows - temp along nodes at y/2
time_column = 11; % from which column(time) --> plot data
plot(data(2:end,time_column),'r *'); % LBM 

plot(x,u(1,:),x, u(2,:) ); % enable colors ;p -- exact solution
grid on
xlabel('x')
ylabel('Temperature')
set(gcf,'Position',get(0,'Screensize')/1) % enlarge image to ( .../1.5) full screen
str_legend1 = sprintf('t = %0.1f',t(1));
str_legend2 = sprintf('t = %0.1f',t(2));
legend('LBM',str_legend1,str_legend2,'Location','best' );
%legend('t = 0.1','t = 5','t = 100','Location','best')

str_title = sprintf('Temperatures across material at t = %0.1f, t = %0.1f', t(1),t(2));

title(str_title );
hold off;
