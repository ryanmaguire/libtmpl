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
#       Computes the Maclaurin coefficients for exp(x).                        #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 30, 2023.                                                  #
################################################################################
"""

# Polynomial evaluation via Horner's method.
import poly

# Muli-precision math routines found here.
import mpmath

# Factorial found here.
import math

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.dps = 224

# Function for computing the first N + 1 Maclaurin coefficients for exp(x).
def coeffs(N):
    return [mpmath.mpf(1) / mpmath.mpf(math.factorial(n)) for n in range(N + 1)]

# Float = 4, double = 8, extended = 10, double-double = 15, quadruple = 16.
a = coeffs(16)
poly.print_coeffs(a)
