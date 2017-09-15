print("new test from auto1.lua.")
local s = auto.create()

s:fuel(298)
i1, i2, i3, i4 = s:check()
print(i1, i2, i3, i4)

-- s:fuel(99)
s:drive("moto", 800, 23.3)
i1, i2, i3, i4 = s:check()
print(i1, i2, i3, i4)

spend = s:maintain("1000 miles.")
print(spend)

s = nil
collectgarbage()


