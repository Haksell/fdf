from random import randrange
import sys

assert len(sys.argv) == 2
size = int(sys.argv[1])
with open(f"maps/generated/rgb_cube_{size}.fdf", "w") as fp:
    for y in range(size):
        line = []
        for x in range(size):
            z = randrange(size)
            line.append(
                f"{z-size/2},0x{int(x*256/size):02x}{int(y*256/size):02x}{int(z*256/size):02x}"
            )
        print(*line, file=fp)
