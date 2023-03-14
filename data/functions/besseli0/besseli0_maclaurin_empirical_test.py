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
#   Date:   January 10, 2023.                                                  #
################################################################################
"""

# Muli-precision math routines found here.
import mpmath

# Bessel I0 coefficients given here.
import besseli0

# Polynomial computations here.
import poly

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.dps = 224

# Desired precision.
EPS = 2**-23

# Function for computing the difference of the approximation with scipy.
def diff(a, x):
    y = mpmath.besseli(0, x)
    z = poly.poly_eval(a, x*x)
    return (y - z) / y

# Print which values of N achieved double precision.
x = 8

for m in range(2, 50):
    a = [besseli0.taylor(n) for n in range(m)]
    y = diff(a, x)

    # If the expansion was very accurate, move along.
    if abs(y) < EPS:
        b = [mpmath.mpf(k.numerator) / mpmath.mpf(k.denominator) for k in a]
        poly.print_coeffs(b)
        break
