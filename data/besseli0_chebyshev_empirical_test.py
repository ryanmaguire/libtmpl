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

# Evaluates, using the Clenshaw algorithm, the Chebyshev expansion, of the
# transformed variable. Converts [8, infty] to [-1, 1] and performs the sum.
def cheb_eval(a, x):
    x = mpmath.mpf(x)
    y = mpmath.mpf(16)/x - mpmath.mpf(1)
    z = chebyshev.cheb_eval(a, y)
    return z/mpmath.sqrt(x)

# Evaluates a polynomial in the transformed variable.
def poly_eval(a, x):
    x = mpmath.mpf(x)
    y = mpmath.mpf(16)/x - mpmath.mpf(1)
    z = poly.poly_eval(a, y)
    return z/mpmath.sqrt(x)

def diff(a, x):
    y = cheb_eval(a, x)
    z = mpmath.besseli(0, x)*mpmath.exp(-x)
    return (y - z)/z

# Desired precision.
EPS = 2**-52

# Print which values of N achieved double precision.
x = 16
N = 21
for m in range(2, N):
    a = coeffs(m)
    y = diff(a, x)

    # If the expansion was very accurate, move along.
    if abs(y) < EPS:
        b = chebyshev.cheb_to_poly(a)
        poly.print_coeffs(b)
        break
