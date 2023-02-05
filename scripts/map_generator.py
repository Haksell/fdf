from math import cos, hypot, sin, sqrt, tau
import sys
from types import FunctionType

PREFIX = "generate_"


def generate_wave(x, y, args):
    assert len(args) == 2
    bumps = int(args[0])
    amplitude = float(args[1])
    height = amplitude * (
        sin(bumps * tau * y / (SIZE - 1)) + cos(bumps * tau * x / (SIZE - 1))
    )
    color = (
        0x8AB4F8
        if height < 0
        else 0x2DB900
        if height < 4
        else 0x1D9100
        if height < 6
        else 0x5F2B14
        if height < 8
        else 0xFFFFFF
    )
    return f"{height:.2f},0x{color:x}"


def generate_flat(x, y, args):
    assert len(args) == 0
    return 0


def generate_checkerboard(x, y, args):
    assert len(args) == 0
    return (x ^ y) & 1


def generate_abs(x, y, args):
    assert len(args) == 0
    dx = (SIZE - 1) / 2 - x
    dy = (SIZE - 1) / 2 - y
    height = abs(dx) + abs(dy)
    return f"{height:.1f}"


def generate_parabola(x, y, args):
    assert len(args) == 0
    dx = (SIZE - 1) / 2 - x
    dy = (SIZE - 1) / 2 - y
    height = dx * dx + dy * dy
    return f"{height:.1f}"


def generate_donut(x, y, args):
    assert len(args) == 1
    width = float(args[0])
    radius = SIZE / 2 - width - 2
    dx = (SIZE - 1) / 2 - x
    dy = (SIZE - 1) / 2 - y
    center_dist = hypot(dx, dy)
    donut_dist = max(0, width - abs(center_dist - radius))
    height = sqrt(width**2 - (width - donut_dist) ** 2)
    return f"{height:.1f}"


assert len(sys.argv) >= 3
MAP_TYPE, SIZE, args = sys.argv[1], int(sys.argv[2]), sys.argv[3:]
GENERATORS = {
    k.removeprefix(PREFIX): v
    for k, v in globals().items()
    if k.startswith(PREFIX) and type(v) == FunctionType
}
generator = GENERATORS[MAP_TYPE]
filename = f"maps/generated/{MAP_TYPE}_{SIZE}x{SIZE}.fdf"
with open(filename, "w") as fp:
    for y in range(SIZE):
        line = [generator(x, y, args) for x in range(SIZE)]
        print(*line, file=fp)
