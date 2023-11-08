import numpy as np
from PIL import Image, ImageDraw
import math

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    draw=ImageDraw.Draw(image)
    draw.line((x0,y0,x1,y1),fill=(fill),width=width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    if  (x0 < x1 and y0 < y1 and x0 > 0 and y0 > 0
        and x1 < image.width and y1 < image.height):
        return True
def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image,x0,y0,x1,y1):
        area=image.crop((x0,y0,x1,y1))
        converted_area=area.convert("1")
        image.paste(converted_area,(x0,y0,x1,y1))
    return image

# Задача 3
def find_largest_rect(image, color):
    width, height = image.size
    pixels = image.load()

    largest_area = 0
    top_x, top_y, bottom_x, bottom_y = 0, 0, 0, 0

    for x in range(width):
        for y in range(height):
            if pixels[x, y] == color:
                current_x, current_y = x, y
                current_area = 0

                while current_x < width and pixels[current_x, current_y] == color:
                    current_area += 1
                    current_x += 1
                #  ПРЕВЫШАЕТ ЛИМИТ ВРЕМЕНИ
                while current_y < height  and pixels[current_x-1, current_y] == color:
                    current_area += 1
                    current_y += 1

                if current_area > largest_area:
                    largest_area = current_area
                    top_x, top_y, bottom_x, bottom_y = x, y, current_x, current_y

    return (top_x,top_y,bottom_x-1, bottom_y-1)

def find_rect_and_recolor(image, old_color, new_color):
    draw=ImageDraw.Draw(image)
    print(find_largest_rect(image,old_color))
    draw.rectangle(find_largest_rect(image,old_color),fill=new_color)
    return image

image=Image.new("RGB",(1000,1000),(0,255,255))
draw=ImageDraw.Draw(image)
draw.rectangle((100, 100, 150, 200), fill=(0,0,0),width=1)
draw.rectangle((200, 200, 300, 400), fill=(0,0,0),width=1)
draw.rectangle((600, 600, 800, 800), fill=(0,0,0),width=1)

# user_func(image,150,160,170,180,(0,128,0),3)
# set_black_white(image,100,100,300,300)
find_rect_and_recolor(image,(0,0,0),(300,342,234))
image.show()


