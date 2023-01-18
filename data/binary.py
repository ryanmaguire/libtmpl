"""
################################################################################
#                                   LICENSE                                    #
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
#       Routines for working with binary representations of floats.            #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 10, 2023.                                                  #
################################################################################
"""

# Multi-precision math routines found here.
import mpmath

# Pi to ~1300 digits is needed for quad precision argument reduction.
mpmath.mp.prec = 1500

def binary_to_float(x):

    if x[0] == "-" or x[0] == "+":
        z = x[1:]
    else:
        z = x

    num_len = len(z) - 1
    expo = 0

    while (z[expo] != "."):
        expo = expo + 1

    expo = expo - 1
    z = z.replace(".", "")
    y = mpmath.mpf(0)

    for n in range(num_len):
        y += mpmath.mpf(int(z[n]) * 2**(expo - n))

    if x[0] == "-":
        return -y
    else:
        return y

def float_to_binary(x):
    z = mpmath.fabs(x)
    y = bin(int(z))[2:] + "."

    z = z - mpmath.mpf(int(z))

    for n in range(1, mpmath.mp.prec):
        p = 2**-n;
        if p <= z:
            y += "1"
            z = z - mpmath.mpf(p)
        else:
            y += "0"

    if x < 0:
        y = "-" + y

    return y

def round_up(x, n):

    if x[0] == "-" or x[0] == "+":
        z = x[1:]
    else:
        z = x

    expo = 0

    while (z[expo] != "."):
        expo = expo + 1

    ind = expo + n
    y = z[0:ind]

    if z[ind+1] == "1" or z[ind] == "1":
        y += "1"
    else:
        y += "0"

    if x[0] == "-":
        y = "-" + y

    return y;
