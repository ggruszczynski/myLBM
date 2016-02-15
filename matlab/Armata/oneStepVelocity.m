function [ vxNext, vyNext ] = oneStepVelocity( vx , vy, param )

    dt = param.dt;
    Ct = param.Ct;
    m = param.m;
    g = param.g;

    vxNext = vx + Ct/m*sqrt(vx^2 + vy^2)*(-vx)*dt;
    vyNext = vy + (Ct/m*sqrt(vx^2 + vy^2)*(-vy) - g )*dt;

end

