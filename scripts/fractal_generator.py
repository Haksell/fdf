from dataclasses import dataclass
from math import sqrt
import sys
import numpy as np


@dataclass
class Limits:
    x_min: int
    x_max: int
    y_min: int
    y_max: int


MAX_ITERATIONS = 100
MAX_HEIGHT = sqrt(MAX_ITERATIONS) - 1
ESCAPE_RADIUS = 4
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


def iterations_mandelbrot(z0):
    z = 0
    i = 0
    while i < MAX_ITERATIONS and abs(z) <= ESCAPE_RADIUS:
        z = z * z + z0
        i += 1
    return i


def iterations_julia(z0):
    z = z0
    i = 0
    while i < MAX_ITERATIONS and abs(z) <= ESCAPE_RADIUS:
        z = z * z + julia_start
        i += 1
    return i


def float_representation(x):
    return f"{'neg' if x<0 else ''}{abs(round(x*10000))}"


ITERATIONS = {
    "mandelbrot": iterations_mandelbrot,
    "julia": iterations_julia,
}
LIMITS = {
    "mandelbrot": Limits(-2.25, 0.75, -1.5, 1.5),
    "julia": Limits(-1.5, 1.5, -1.5, 1.5),
}
fractal = sys.argv[1]
assert fractal in ITERATIONS
assert len(sys.argv) == 3 + (fractal == "julia")
size = int(sys.argv[2])
if fractal == "julia":
    julia_start = complex(sys.argv[3])
    julia_filename = f"{float_representation(julia_start.real)}_{float_representation(julia_start.imag)}i_"
else:
    julia_filename = ""
iterations = ITERATIONS[fractal]
limits = LIMITS[fractal]
with open(f"maps/generated/{fractal}_{julia_filename}{size}x{size}.fdf", "w") as fp:
    for y in np.linspace(limits.y_min, limits.y_max, size):
        row = []
        for x in np.linspace(limits.x_min, limits.x_max, size):
            n = iterations(complex(x, y))
            height = sqrt(n) - 1
            color = (
                0x111111
                if n == MAX_ITERATIONS
                else COLORS[int(height * len(COLORS) / MAX_HEIGHT)]
            )
            row.append(f"{sqrt(n):.1f},0x{color:06x}")
        print(*row, file=fp)
