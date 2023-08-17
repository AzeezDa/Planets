Universe = {}

BodyAmount = 1000
RadiusModifier = 5
SpiralAmount = 10
Mass = -8

function PolarToEuclid(step, radius)
    local theta = 2 * math.pi * step / BodyAmount
    return { radius * math.cos(SpiralAmount * theta), radius * math.sin(SpiralAmount * theta) }
end

for i = 1, BodyAmount do
    table.insert(Universe,
        { mass = Mass, position = PolarToEuclid(i, i * RadiusModifier), velocity = { 0, 0 }, color = "orange" })
end
