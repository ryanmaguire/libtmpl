################################################################################
#                                  LICENSE                                     #
################################################################################
#   This file is part of libtmpl.                                              #
#                                                                              #
#   libtmpl is free software: you can redistribute it and/or modify it         #
#   under the terms of the GNU General Public License as published by          #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpl is distributed in the hope that it will be useful,                 #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.          #
################################################################################
#   Purpose:                                                                   #
#       Draw the Barnsley fern.                                                #
#   Notes:                                                                     #
#       This file is an extra and is not part of the libtmpl library.          #
#       This is a modification of some ideas I found while browsing reddit.    #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   June 12, 2021.                                                     #
################################################################################

import random
 
width = 720
height = 720
fp = open("tmpl_barnsley_fern.ppm", "w")
fp.write("P3\n%u %u\n255\n" % (width, height))
factor = 1.0

pixels = [0] * (width * height)
x, y = 0, 1
grow = (1 - (factor - 1) ** 4) * 0.85
    
for n in range(60 * width * height):        
    r = random.random() * 100
    xn, yn = x, y
    if r < 1:
        x = 0
        y = 0.16 * yn
    elif r < 86:
        x = grow * xn + 0.04 * yn
        y = -0.04 * xn + 0.85 * yn + 1.6
    elif r < 93:
        x = 0.20 * xn - 0.26 * yn
        y = 0.23 * xn + 0.22 * yn + 1.6
    else:
        x = -0.15 * xn + 0.28 * yn
        y = 0.26 * xn + 0.24 * yn + 0.44

    x_pix = int(width * (0.45 + 0.195 * x))
    y_pix = int(height * (1 - 0.099 * y ))
    pixels[x_pix + y_pix * width] += 1

for y in range(height):
    for x in range(width):
        p = pixels[x + y*width]
        grey = max(0, (256-p) / 256)
        val = grey ** 6
        red = 255*int(val)
        green = 255*int(val)
        blue = red
        fp.write("%u %u %u\n" % (red, green, blue))

fp.close()