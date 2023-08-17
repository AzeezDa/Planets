Universe = {}

BodyAmount = 25
Mass = 100

for i = 1, BodyAmount do
    table.insert(Universe,
        { mass = Mass, position = { -900, -500 + i * 40 }, velocity = { 400, 0 }, color = "green" }
    )
    table.insert(Universe,
        { mass = Mass, position = { 900, -500 + i * 40 }, velocity = { -400, 0 }, color = "cyan" }
    )
end
