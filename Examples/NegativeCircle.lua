Universe = {}

BodyAmount = 100
Radius = 200
Mass = -10

function PolarToEuclid(step)
    local theta = 2 * math.pi * step / BodyAmount
    return { Radius * math.cos(theta), Radius * math.sin(theta) }
end

for i = 0, BodyAmount - 1 do
    table.insert(Universe, { mass = Mass, position = PolarToEuclid(i), velocity = { 0, 0 }, color = "red" });
end
