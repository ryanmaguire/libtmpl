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
#       Coefficients and tools for the modified Bessel function I0.            #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# exp, sqrt, and pi found here.
import math

# Rational numbers found here.
import fractions

# Muli-precision math routines found here.
import mpmath

# Double factorial function given here.
import misc_math

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.prec = 224

# Function for computing the nth coefficient of the Taylor series of I0.
def taylor(ind):
    """
        Function:
            taylor
        Purpose:
            Computes the Taylor coefficients for Bessel I0 at x = 0.
        Arguments:
            ind (int):
                The coefficient to be computed.
        Output:
            coeff (fraction):
                The coefficient of the Taylor Series of I0(x) x = 0.
    """
    num = 1
    den = (4**ind) * (math.factorial(ind)**2)
    return fractions.Fraction(num, den)

# Function for computing the nth coefficient of the asymptotic expansion of I0.
def asym(ind):
    """
        Function:
            asym
        Purpose:
            Computes the asymptotic expansion for Bessel I0 at x = 0.
        Arguments:
            ind (int):
                The coefficient to be computed.
        Output:
            coeff (fraction):
                The coefficient of the asymptotic expansion for I0(x).
    """
    num = misc_math.double_factorial(2*ind - 1)**2
    den = math.factorial(ind) * (8**ind)
    return fractions.Fraction(num, den)

# Function for computing the degree deg asymptotic expansion of I0.
def asym_series(val, deg):
    """
        Function:
            asym_series
        Purpose:
            Evaluates I0(x) via asymptotic expansion.
        Arguments:
            val (fraction):
                The input argument.
            deg (int):
                The degree of the asymptotic expansion.
        Output:
            I0_val (mpmath.mpf):
                The value I0(x) using the degree "deg" asymptotic expansion.
    """

    # Various constants used throughout.
    one = mpmath.mpf(1)
    invx = one / mpmath.mpf(val)
    output = mpmath.mpf(1)
    twopi = mpmath.mpf(2)*mpmath.pi

    # Lazily compute. Horner's method isn't used, this is the slow way.
    for ind in range(1, deg):
        val = asym(ind)
        val = mpmath.mpf(val.numerator) / mpmath.mpf(val.denominator)
        output += val * (invx ** ind)

    # The series is scaled by e^x / sqrt(2 pi x). Compute this and return.
    return mpmath.exp(val) * output / mpmath.sqrt(twopi*val)
