function [ vxNext, vyNext, xNext, yNext   ] = VPstep(vx, vy, x, y,param  ) 
% H- operator
% Position
% Velocity
% 
%     vx = X(1);
%     vy = X(2);
%     x = X(3);
%     y = X(4);


    dt = param.dt;
    Ct = param.Ct;
    m = param.m;
    g = param.g;

    xNext = x + vx*dt;
    yNext = y + vy*dt;

    
    vxNext = vx + Ct/m*sqrt(vx^2 + vy^2)*(-vx)*dt;
    vyNext = vy + (Ct/m*sqrt(vx^2 + vy^2)*(-vy) - g )*dt;
    
 %   XNext = [  vxNext, vyNext, xNext, yNext  ];
end

