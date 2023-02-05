from random import randrange

SIZE = 16
with open(f"maps/generated/rgb_cube_{SIZE}.fdf", "w") as fp:
    for y in range(SIZE):
        line = []
        for x in range(SIZE):
            z = randrange(SIZE)
            line.append(
                f"{z-SIZE/2},0x{int(x*256/SIZE):02x}{int(y*256/SIZE):02x}{int(z*256/SIZE):02x}"
            )
        print(*line, file=fp)
