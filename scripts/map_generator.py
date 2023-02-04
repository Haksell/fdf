from math import cos, sin

SIZE = 64
FACTOR = 0.1
for y in range(SIZE):
    line = []
    for x in range(SIZE):
        line.append(round(100 * (sin(y * FACTOR) + cos(x * FACTOR))))
    print(*line)
