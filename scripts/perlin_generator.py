import sys
import numpy as np
from perlin_noise import PerlinNoise

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
            noise_val = noise1(coords)
            noise_val += 0.5 * noise2(coords)
            noise_val += 0.25 * noise3(coords)
            noise_val += 0.125 * noise4(coords)
            row.append(f"{AMPLITUDE*noise_val:.1f}")
        print(*row, file=fp)
