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
#       Prints pi/2 in the form a0 + a1 + a2 + a3, correctly founded.          #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 18, 2023.                                                  #
################################################################################
"""

# Functions for working in binary.
import binary

# Multi-precision math functions.
import mpmath

# Set precision to 1500 bits. Overkill for most things.
mpmath.mp.prec = 1500

x = mpmath.pi/mpmath.mpf(2)
y = binary.float_to_binary(x)

number = 29
X = [0]*number
Y = [0]*number

skip = 8
start = skip

for n in range(number):
    ynew = binary.round_up(y, start + skip*n)
    xnew = binary.binary_to_float(ynew)
    X[n] = xnew
    Y[n] = ynew

    s = mpmath.nstr(xnew, 50, strip_zeros = True, min_fixed = 0, max_fixed = 0)
    if s[0] != "-":
        s = "+" + s

    s = s.replace("e", "E")
    # print("#define A%d (%s)" % (n, s))
    print("    %s," % s)
    x = x - xnew
    y = binary.float_to_binary(x)
