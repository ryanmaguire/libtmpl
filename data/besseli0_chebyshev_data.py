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
#       Computes the Chebyshev coefficients for the Bessel Function I0.        #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# Chebyshev evaluation and coefficients.
import chebyshev

# Polynomial evaluation via Horner's method.
import poly

# Muli-precision math routines found here.
import mpmath

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.dps = 224

# Transforms the interval [-1, 1] to [8, inft] and computes the scaled bessel
# function I0(y) exp(-y) sqrt(y) in the new variable y.
def f(x):
    y = mpmath.mpf(16)/mpmath.mpf(x + 1)
    return mpmath.exp(-y)*mpmath.besseli(0, y)*mpmath.sqrt(y)

# Computes the first N coefficients of the Chebyshev expansion of f.
def coeffs(N):
    return chebyshev.cheb_coeffs(f, N, 1000)

c = coeffs(20)
a = chebyshev.cheb_to_poly(c)
chebyshev.print_coeffs(c)
poly.print_coeffs(a)
