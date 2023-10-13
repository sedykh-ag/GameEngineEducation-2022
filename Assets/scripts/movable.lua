function Update(dt)
    deltaVel = 0.0

    state = GetInputState()
    if state:test(eIC_GoLeft) then
        deltaVel -= spd
    end
    if state:test(eIC_GoRight) then
        deltaVel += spd
    end

    vel_x += deltaVel * dt
end