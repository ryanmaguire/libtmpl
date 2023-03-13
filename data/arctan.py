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
#       Taylor and asymptotic coefficients for the inverse tangent function.   #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# Arbitrary precision rationals here.
import fractions

# Compute the nth Taylor coefficient of atan(x).
def taylor(ind):
    """
        Function:
            taylor
        Purpose:
            Given a non-negative integer n, compute the coefficient of the
            nth term of the Taylor series for arctan at x = 0.
        Arguments:
            ind (int):
                The index of the coefficient to be computed.
        Output:
            coeff (fraction):
                The coefficient of the Taylor series of arctan(x) at x = 0.
    """
    return fractions.Fraction((-1)**ind, 2*ind + 1)

# Compute the nth asymptotic coefficient of atan(x) - pi/2.
def asym(ind):
    """
        Function:
            asym
        Purpose:
            Given a non-negative integer n, compute the coefficient of the
            nth term of the asymptotic expansion for arctan.
        Arguments:
            ind (int):
                The index of the coefficient to be computed.
        Output:
            coeff (fraction):
                The coefficient of the asymptotic expansion for arctan.
    """
    return fractions.Fraction((-1)**(ind+1), 2*ind + 1)
