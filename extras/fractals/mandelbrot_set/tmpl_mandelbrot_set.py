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
#       Draw the mandelbrot set.                                               #
#   Notes:                                                                     #
#       This file is an extra and is not compiled as part of libtmpl.          #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   June 1, 2021.                                                      #
################################################################################

# The width and height of the PPM file.
width = 1024;
height = 1024;

# The maximum number of iterations allowed while computing the fractal.
imax = 256;

# The maximum radius such that points will automatically be consider divergent.
zmax = 4.0;

# The values of the rectangle that will be drawn.
x_min = -3.0;
x_max = 1.0;
y_min = -2.0;
y_max = 2.0;

# Factors for transforming a pixel to the corresponding point in the plane.
x_factor = (x_max - x_min)/(width - 1.0);
y_factor = (y_max - y_min)/(height - 1.0);

# Open the PPM file and give it write permissions.
fp = open("swipecat_fractal.ppm", "w");

# Write the preamble to the PPM file. We'll use P3, which is text based, to
# ensure that this file renders properly on Windows.
fp.write("P3\n%d %d\n255\n" % (width, height));

for y in range(height):
    z_y = y_max - y_factor*y;
    for x in range(width):
        z_x = x_min + x_factor*x;
        c = complex(z_x, z_y);
        z = 0.0;
        backgnd = 0.0;
        for its in range(imax):
            z = z*z + c;
            if abs(z.real) >= zmax:
                break;

        if (its == imax - 1):
            red = 0;
            green = 0;
            blue = 0;
        elif (its < 64):
            red = 4*its;
            green = 4*its;
            blue = 255 - 4*its;
        else:
            red = 255;
            green = 255;
            blue = 0;

        fp.write("%u %u %u\n" % (red, green, blue));
fp.close();

