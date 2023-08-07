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
#       Taylor coefficients for the inverse sine function.                     #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   April 17, 2023.                                                    #
################################################################################
"""

# Arbitrary precision rationals here.
import fractions

# Denominator given by factorial function.
import math

# Numerator given by rising factorial.
import tmpld.math

# Compute the nth Taylor coefficient of asin(x).
def taylor(ind):
    """
        Function:
            taylor
        Purpose:
            Given a non-negative integer n, compute the coefficient of the
            nth term of the Taylor series for arcsin at x = 0.
        Arguments:
            ind (int):
                The index of the coefficient to be computed.
        Output:
            coeff (fraction):
                The coefficient of the Taylor series of arcsin(x) at x = 0.
    """
    num = tmpld.math.half_rising_factorial(ind)
    den = (2*ind + 1)*math.factorial(ind)
    return fractions.Fraction(num, den)
