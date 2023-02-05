from PIL import Image, ImageDraw, ImageFont
import numpy as np
import sys

assert len(sys.argv) == 2
text = sys.argv[1]
myfont = ImageFont.truetype(
    "/mnt/nfs/homes/axbrisse/Desktop/cursus/fdf/scripts/verdanab.ttf", 12
)
size = myfont.getsize(text)
img = Image.new("1", size, "black")
draw = ImageDraw.Draw(img)
draw.text((0, 0), text, "white", font=myfont)
pixels = np.array(img, dtype=np.uint8)
chars = np.array(["0", "3"], dtype="U1")[pixels]
strings = list(chars.view("U" + str(chars.shape[1])).flatten())
empty = strings[0]
rows = [empty, empty, *strings[3:], empty, empty]
rows = [["0", *row, "0"] for row in rows]
rows = [[h if h == "0" else f"{h},0xDC143C" for h in row] for row in rows]
filename = f"maps/generated/text_{''.join(c.lower() for c in text if c.isalnum())}.fdf"
print("\n".join(" ".join(row) for row in rows), file=open(filename, "w"))
