from math import cos, sin, tau
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


# TODO donuts
# TODO flat

assert len(sys.argv) >= 3
MAP_TYPE, SIZE, args = sys.argv[1], int(sys.argv[2]), sys.argv[3:]
GENERATORS = {
    k.removeprefix(PREFIX): v
    for k, v in globals().items()
    if k.startswith(PREFIX) and type(v) == FunctionType
}
generator = GENERATORS[MAP_TYPE]
filename = f"maps/valid/{MAP_TYPE}_{SIZE}x{SIZE}.fdf"
with open(filename, "w") as fp:
    for y in range(SIZE):
        line = [generator(x, y, args) for x in range(SIZE)]
        print(*line, file=fp)
