function [ ax, ay ] = oneStepAcceleration( vx , vy,param)

    Ct = param.Ct;
    m = param.m;
    g = param.g;

    ax =  Ct/m*sqrt(vx^2 + vy^2)*(-vx);
    ay = Ct/m*sqrt(vx^2 + vy^2)*(-vy) - g ;
end

