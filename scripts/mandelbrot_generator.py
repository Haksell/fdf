from math import sqrt
import sys
import numpy as np

X_MIN = -2.25
X_MAX = 0.75
Y_MIN = -1.5
Y_MAX = 1.5
MAX_ITERATIONS = 100
MAX_HEIGHT = sqrt(MAX_ITERATIONS) - 1
ESCAPE_RADIUS = 4

assert len(sys.argv) == 2
size = int(sys.argv[1])

COLORS = [
    0xB2182B,
    0xD6604D,
    0xF4A582,
    0xFDDBC7,
    0xE0E0E0,
    0xBABABA,
    0x878787,
    0x4D4D4D,
]


def iterations(z0):
    z = 0
    i = 0
    while i < MAX_ITERATIONS and abs(z) <= ESCAPE_RADIUS:
        z = z * z + z0
        i += 1
    return i


with open(f"maps/generated/mandelbrot_{size}x{size}.fdf", "w") as fp:
    for y in np.linspace(Y_MIN, Y_MAX, size):
        row = []
        for x in np.linspace(X_MIN, X_MAX, size):
            n = iterations(complex(x, y))
            height = sqrt(n) - 1
            color = (
                0x111111
                if n == MAX_ITERATIONS
                else COLORS[int(height * len(COLORS) / MAX_HEIGHT)]
            )
            row.append(f"{sqrt(n):.1f},0x{color:06x}")
        print(*row, file=fp)
