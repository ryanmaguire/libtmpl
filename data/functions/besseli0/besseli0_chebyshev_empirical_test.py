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

# mpmath imported here.
import tmpld

# Chebyshev evaluation and coefficients.
import tmpld.chebyshev

# Polynomial evaluation via Horner's method.
import tmpld.poly

# Evaluates, using the Clenshaw algorithm, the Chebyshev expansion, of the
# transformed variable. Converts [8, infty] to [-1, 1] and performs the sum.
def cheb_eval(a, x):
    x = tmpld.mpmath.mpf(x)
    y = tmpld.mpmath.mpf(16)/x - tmpld.mpmath.mpf(1)
    z = tmpld.chebyshev.cheb_eval(a, y)
    return z/tmpld.mpmath.sqrt(x)

# Evaluates a polynomial in the transformed variable.
def poly_eval(a, x):
    x = tmpld.mpmath.mpf(x)
    y = tmpld.mpmath.mpf(16)/x - tmpld.mpmath.mpf(1)
    z = tmpld.poly.poly_eval(a, y)
    return z/tmpld.mpmath.sqrt(x)

def diff(a, x):
    y = cheb_eval(a, x)
    z = tmpld.mpmath.besseli(0, x)*tmpld.mpmath.exp(-x)
    return (y - z)/z

def diff2(a, b, x):
    y = cheb_eval(a, x)
    z = poly_eval(b, x)
    return (y - z)/z

# Desired precision.
EPS = 2**-52

# Print which values of N achieved double precision.
x = 20
N = 21
for m in range(2, N):
    a = tmpld.chebyshev.cheb_coeffs(scaled_i0, m, 1000)
    y = diff(a, x)

    # If the expansion was very accurate, move along.
    if abs(y) < EPS:
        b = tmpld.chebyshev.cheb_to_poly(a)
        tmpld.poly.print_coeffs(b)

        break
