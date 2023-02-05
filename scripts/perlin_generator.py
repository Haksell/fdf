import sys
import numpy as np
from perlin_noise import PerlinNoise


def get_color(height):
    return (
        0x1E3F5A
        if height < -1.2
        else 0x92C4EE
        if height < -0.5
        else 0xF6E3D4
        if height < 0
        else 0x107812
        if height < 2
        else 0x014421
        if height < 5
        else 0x554124
        if height < 7
        else 0xFFFFFF
    )


AMPLITUDE = 20
noise1 = PerlinNoise(octaves=3)
noise2 = PerlinNoise(octaves=6)
noise3 = PerlinNoise(octaves=12)
noise4 = PerlinNoise(octaves=24)
assert len(sys.argv) == 2
size = int(sys.argv[1])
with open(f"maps/generated/perlin_{size}x{size}.fdf", "w") as fp:
    for y in np.linspace(0, 1, size):
        row = []
        for x in np.linspace(0, 1, size):
            coords = [y, x]
            height = noise1(coords)
            height += 0.5 * noise2(coords)
            height += 0.25 * noise3(coords)
            height += 0.125 * noise4(coords)
            height *= AMPLITUDE
            row.append(f"{max(0, height):.1f},0x{get_color(height):06x}")
        print(*row, file=fp)
