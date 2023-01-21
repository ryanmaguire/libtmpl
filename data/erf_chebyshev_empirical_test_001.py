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
#       Computes the Chebyshev coefficients for the error function Erf(x).     #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 19, 2023.                                                  #
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
    y = mpmath.mpf(x) * mpmath.mpf(2.0)

    return mpmath.erf(y)

def coeffs(N):
    return chebyshev.cheb_coeffs(f, N, 1000)

def cheb_eval(a, x):
    y = mpmath.mpf(x) * mpmath.mpf(0.5)
    return chebyshev.cheb_eval(a, y)

def poly_eval(a, x):
    y = mpmath.mpf(x) * mpmath.mpf(0.5)
    return poly.poly_eval(a, y)

def diff(a, x):
    y = cheb_eval(a, x)
    z = mpmath.erf(x)
    return (y - z)/z

# Desired precision.
EPS = 2**-54

# Print which values of N achieved double precision.
x = 2
N = 40
for m in range(20, N):
    a = coeffs(m)
    y = diff(a, x)

    # If the expansion was very accurate, move along.
    if abs(y) < EPS:
        b = chebyshev.cheb_to_poly(a)
        a = []
        k = 0
        while ((2*k + 1) < len(b)):
            a.append(b[2*k+1])
            k += 1
        poly.print_coeffs(a)
        break
