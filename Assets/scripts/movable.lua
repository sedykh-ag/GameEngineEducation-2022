t = 0
function Update(dt)
    -- all this does not work
    deltaVel = 0.0

    x = inputHandler:TestLeftRight()
    if x == 1 then
        deltaVel = deltaVel - spd
    elseif x == -1 then
        deltaVel = deltaVel + spd
    end
    vel_x = vel_x + deltaVel * dt

    -- this does work
    t = t + dt
    vel_x = -1.0 + t % 2
end