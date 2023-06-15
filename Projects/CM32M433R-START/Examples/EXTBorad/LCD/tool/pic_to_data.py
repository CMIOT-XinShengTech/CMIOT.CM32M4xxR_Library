#!/usr/bin/env python3
# -*- coding:utf-8 -*-
"""
Convert picture to C array with RGB565 pixels.
"""

from pathlib import Path
from PIL import Image
import fire


def main(file, out=None):
    img = Image.open(file)
    img = img.convert('RGB')
    pixels = []
    for j in range(img.height):
        for i in range(img.width):
            r, g, b = img.getpixel((i, j))
            #rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3)
            #pixels.append(rgb565)
            rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3)
            rgb565_2 = ((rgb565 & 0xFF) << 8) | ((rgb565 & 0xFF00) >> 8)
            pixels.append(rgb565_2)

    if not out:
        out = Path(file).with_suffix(".c")
    with open(out, 'w') as f:
        f.write('#include <stdint.h>\n')
        #f.write('#include "lcd.h"\n')
        f.write(
            f'const color_t pic_{Path(out).stem}_data[{img.width * img.height}] = {{'
        )
        for i, pixel in enumerate(pixels):
            if i % 8 == 0:
                f.write('\n    ')
            f.write(f'0x{pixel:04x}, ')
        f.write('\n};\n')
        #f.write(f'const image_t pic_{Path(out).stem} = {{.width = {img.width}, .height = {img.height}, .img_data = (color_t*)pic_{Path(out).stem}_data, .format=FORMAT_RGB565,}};\n')


if __name__ == "__main__":
    fire.Fire(main)
