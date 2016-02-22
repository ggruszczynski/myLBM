function [ dJ, historia ] = Celowanie1step( vx0, vy0, x0, y0 ,param )
%CELOWANIE1STEP Summary of this function goes here
%   Detailed explanation goes here

in = [ vx0, vy0, x0, y0 ];
inAD{1} = myAD(in);


% vx{1} = inAD{1}(1);	 
% vy{1} = inAD{1}(2);	  
% x{1} = inAD{1}(3); 
% y{1} = inAD{1}(4); 


%[outad] = VPstep_test (inad, param); % wrong way 
%[outad] = VPstep_test (in1ad, in2ad, param); % wrong way 
%[outad] = VPstep_test ([in1ad, in2ad], param); % wrong way 
%[out1ad, out2ad] = VPstep_test (.., param); % wrong way 

% [  vx, vy, x, y  ] = VPstep_test(inAD{1}, param); % SYNTAX !!! : [out1AD, out2AD] = f(inAD, param_notAD); 



n=1; % indeks startowy
  [ vx{1}, vy{1}, x{1}, y{1}, Lx{1}, Ly{1}  ] = VPstep_AD(inAD{n}, param);
   dH{1} = [ getderivs(vx{n}); getderivs(vy{n}); getderivs(x{n}); getderivs(y{n});  getderivs(Lx{n}); getderivs(Ly{n});];
    
while n < numel(param.przedzial);
    [ vx{n+1}, vy{n+1}, x{n+1}, y{n+1}, Lx{n+1}, Ly{n+1}  ] = VPstep_AD(inAD{n}, param);    
    in(n+1,:) = [getvalue(vx{n+1}),  getvalue(vy{n+1}),    getvalue(x{n+1}),    getvalue(y{n+1})]; 
    dH{n+1} = [ getderivs(vx{n});
              getderivs(vy{n});
              getderivs(x{n});
              getderivs(y{n});
              getderivs(Lx{n});
              getderivs(Ly{n});];
    
    inAD{n+1} = myAD(in(n+1,:));
    
    n = n + 1;
end


%% teraz z powrotem - adjoint
h = zeros(2,n);
h(:,n) = [1;1]; % weights

v(:,n) = zeros(4,1);

N = numel(param.przedzial);
while N > 1
    v(:,N-1) =  dH{N}' * [v(:,N);h(:,N)];
    N = N-1;
end


historia.all = in;
historia.vx0 = getvalue(vx{1});
historia.vy0 = getvalue(vy{1});
historia.xLast = getvalue(x{n});
historia.yLast = getvalue(y{n});

dJ = v(:,1);
end

