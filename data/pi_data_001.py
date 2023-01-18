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

x = mpmath.mpf(1)/(mpmath.mpf(2)*mpmath.pi)
y = binary.float_to_binary(x)
mpmath.nprint(x, 50, strip_zeros = True, min_fixed = 0, max_fixed = 0)

X = [0]*5
Y = [0]*5

for n in range(5):
    ynew = binary.round_up(y, 27+25*n)
    xnew = binary.binary_to_float(ynew)
    X[n] = xnew
    Y[n] = ynew

    s = mpmath.nstr(xnew, 50, strip_zeros = True, min_fixed = 0, max_fixed = 0)
    if s[0] != "-":
        s = "+" + s

    s = s.replace("e", "E")
    print("#define TMPL_PI_%02d (%s)" % (n, s))

    x = x - xnew
    y = binary.float_to_binary(x)
