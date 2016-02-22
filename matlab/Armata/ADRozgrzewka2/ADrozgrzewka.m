clc, clear

addpath(genpath('../myAutomaticDifferentiation'));
in = [6,5,0]; %arguments
inAD = myAD(in); % overloaded arguments


disp('---------f_3in_2out---------')

[out1, out2] = f_3in_2out(in); % standard way - nothing new here
[out1, out2] = f_3in_2out(inAD) % overloaded

disp('Get Function values & First derivative of function values with respect to parameters')
wartosci_zout2 = getvalue(out2)
pochodne_zout2 = getderivs(out2)
