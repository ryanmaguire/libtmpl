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
#       Determine the degrees necessary for the bessel I0 asymptotic expansion #
#       to achieve double precision in certain windows.                        #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# Muli-precision math routines found here.
import mpmath

# Bessel I0 coefficients given here.
import besseli0

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.dps = 224

# Precision needed.
EPS = 2**-52

# Function for computing the difference of the approximation.
def diff(x, N):
    y = mpmath.besseli(0, x)
    z = besseli0.asym_series(x, N)
    return (y - z) / y

# Print which values of N achieved double precision.
for n in range(3, 10):
    x = 2**n
    for m in range(2, 50):
        y = diff(x, m)

        # If the expansion was very accurate, move along.
        if abs(y) < EPS:
            print(m, x, "%E" % float(y))
            break
