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
#       Routines for working with rational functions.                          #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# Muli-precision math routines found here.
import mpmath

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.dps = 224

# Evaluate a rational function given two arrays of coefficients "a" and "b".
def rat_eval(a, b, x):
    n = len(a) - 1
    m = len(b) - 1
    P = mpmath.mpf(0)
    Q = mpmath.mpf(0)
    y = mpmath.mpf(x)

    # Use Horner's method on the numerator.
    for k in range(n + 1):
        P = y*P + a[n-k]

    # Apply Horner's method for the denominator.
    for k in range(m + 1):
        Q = y*Q + b[n-k]

    # Return the quotient.
    return P/Q
