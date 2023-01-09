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

def f(x):
    y = mpmath.mpf(16)/mpmath.mpf(x + 1)
    return mpmath.exp(-y)*mpmath.besseli(0, y)*mpmath.sqrt(y)-mpmath.mpf(0.375)

def coeffs(N):
    return chebyshev.cheb_coeffs(f, N, 1000)

def cheb_eval(a, x):
    x = mpmath.mpf(x)
    y = mpmath.mpf(16)/x - mpmath.mpf(1)
    z = chebyshev.cheb_eval(a, y)
    return (z + mpmath.mpf(0.375))/mpmath.sqrt(x)

def poly_eval(a, x):
    x = mpmath.mpf(x)
    y = mpmath.mpf(16)/x - mpmath.mpf(1)
    z = poly.poly_eval(a, y)
    return (z + mpmath.mpf(0.375))/mpmath.sqrt(x)

c = coeffs(20)
a = chebyshev.cheb_to_poly(c)
chebyshev.print_coeffs(c)
poly.print_coeffs(c)
