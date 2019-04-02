# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
from PIL import Image

import numpy as np
import matplotlib.pyplot as pyplot
import pylab

sobel_x =[[-1, 0, 1],[-2, 0, 2],[-1, 0, 1]]
sobel_y =[[-1, -2, 1],[0, 0, 0],[1, 2, -1]]


im=Image.open('C:\pytest\sun.jpg').convert('L')
im_array=im.load()
im.show()

w,h = im.size
res = np.zeros((w, h))
sobel_x =[[-1, 0, 1],[-2, 0, 2],[-1, 0, 1]]
sobel_y =[[-1, -2, 1],[0, 0, 0],[1, 2, -1]]
for x in range(1, (w-1)):
    for y in range(1, (h-1)):
        sub =[[im_array[x-1, y-1], im_array[x-1, y], im_array[x-1, y+1]],
        [im_array[x, y-1], im_array[x, y], im_array[x, y+1]], 
        [im_array[x+1, y-1], im_array[x+1, y], im_array[x+1, y+1]]]
        sub = np.array(sub)
        roberts_x = np.array(sobel_x)
        roberts_y = np.array(sobel_y)
        var_x = sum(sum(sub*sobel_x))
        var_y = sum(sum(sub*sobel_y))

    
        var = abs(var_x) + abs(var_y)

        res[x][y] = var.T



pyplot.imshow(res, cmap=pyplot.cm.gray)
pylab.show()