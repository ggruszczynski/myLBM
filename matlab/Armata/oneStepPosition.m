function [ xNext, yNext ] = oneStepPosition( x ,vx , y, vy, dt )

    xNext = x + vx*dt;
    yNext = y + vy*dt;

end

