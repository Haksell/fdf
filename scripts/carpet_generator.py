import sys

ON = "5,0x02AAEB"
OFF = "0,0x111111"
assert len(sys.argv) == 2
STEPS = int(sys.argv[1])
carpet = [[ON]]
for _ in range(STEPS):
    new_carpet = []
    for row in carpet:
        new_carpet.append(3 * row)
    for row in carpet:
        new_carpet.append(row + [OFF] * len(row) + row)
    for row in carpet:
        new_carpet.append(3 * row)
    carpet = new_carpet
with open(f"maps/generated/carpet_{STEPS}.fdf", "w") as fp:
    for row in carpet:
        print(*row, file=fp)
