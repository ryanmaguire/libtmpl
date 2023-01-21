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
#       Coefficients and tools for the Error Function.                         #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 19, 2023.                                                  #
################################################################################
"""

# exp, sqrt, and pi found here.
import math

# Rational numbers found here.
import fractions

# Muli-precision math routines found here.
import mpmath

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.dps = 224

# Function for computing the double factorial, n!! = n*(n-2)*...
def doublefactorial(n):
    if n <= 0:
        return 1
    else:
        double_fact = 1
        k = n
        while (k >= 0):
            double_fact = k*double_fact
            k = k - 2

    return double_fact

# Function for computing the nth coefficient of the Taylor series of erf.
def taylor(n):
    num = (-1)**n
    den = (2*n + 1)*math.factorial(n)
    out = mpmath.mpf(num) / mpmath.mpf(den)
    return (mpmath.mpf(2) / mpmath.sqrt(mpmath.pi)) * out

# Function for computing the nth coefficient of the asymptotic expansion of erf.
def asym(n):
    num = doublefactorial(2*n - 1) * (-1)**n
    den = 2**(n-1)
    out = mpmath.mpf(num) / mpmath.mpf(den)
    return (mpmath.mpf(1) / mpmath.sqrt(mpmath.pi)) * out

# Function for computing the degree N asymptotic expansion of erf.
def asym_series(x, N):
    one = mpmath.mpf(1)
    invx = one / mpmath.mpf(x)
    invx_sq = invx * invx
    y = mpmath.mpf(0)

    for n in range(1, N):
        val = asym(n)
        y += val * (invx_sq ** (n - 1))

    y *= invx
    mpx = mpmath.mpf(x)
    y *= mpmath.exp(-mpx*mpx)

    return y + one
