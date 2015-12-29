clc, clear

%% import data
% Unfortunately Audacity names all (despite its contents) exported .txt files as 'spectrum.txt' 

% delimiterIn = '\t';
% headerlinesIn = 1;
% 
% dirName = pwd; %# folder path = print working directory
% fnames = dir( fullfile(dirName,'*.dat') );     %# list all *.xyz files
% fnames = {fnames.name}';                       %'# file names
% 
% mydata = cell(numel(fnames),1);                %# store file contents
% 
%     fpath = fullfile(dirName,fnames);       %# full path to file
%     mydata = importdata(fpath,delimiterIn,headerlinesIn);        %# load file

%%%%%%%%%%%%%%%%5
 load KarmanData.dat
 
% t = KarmanData(:,1);
% vx = KarmanData(:,2);
% vy = KarmanData(:,3);
% vTot = KarmanData(:,4);


t = KarmanData(4000:end,1);
vx = KarmanData(4000:end,2);
vy = KarmanData(4000:end,3);
vTot = KarmanData(4000:end,4);

figure ('name','Signal');
plot (t,vx,t,vy,t,vTot);
title('Signal')
legend('vx','vy','vTot');
xlabel('time (lattice)')


% n = [0:29];
% x = cos(2*pi*n/10);5
% N1 = 1000;
% X1 = abs(fft(x,N1));
% F1 = [0 : N1 - 1]/N1;
% plot(F1,X1,'-x');

%% Use fft to compute the DFT y and its power.
 fs = 1;                                % Sample frequency (Hz)
% %t = 0:1/fs:10-1/fs;                      % 10 sec sample

x = vTot;

m = length(x);          % Window length
n = pow2(nextpow2(m));  % Transform length
y = fft(x,n);           % DFT
f = (0:n-1)*(fs/n);     % Frequency range
power = y.*conj(y)/n;   % Power of the DFT

%% To visualize the DFT, plots of abs(y), abs(y).^2, and log(abs(y)) are all common. A plot of power versus frequency is called a periodogram.
% plot(f,abs(y))
figure ('name','fft');
plot(f,power)
xlabel('Frequency (Hz)')
ylabel('Power')
title('{\bf Periodogram}')

