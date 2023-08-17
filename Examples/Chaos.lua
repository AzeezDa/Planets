Universe = {}

BodyAmount = 1000
for i = 1, BodyAmount do
    table.insert(Universe,
        {
            mass = math.random(2, 100),
            position = { math.random(-1000, 1000), math.random(-1000, 1000) },
            velocity = { math.random(-300, 300), math.random(-300, 300) },
            color = string.format("#%x", math.random(0x555555, 0xFFFFFF))
        }
    )
end
