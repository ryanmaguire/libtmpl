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

# mpmath imported here.
import tmpld

# double_factorial here.
import tmpld.math

# mpmath constants.
import tmpld.constants

# Function for computing the nth coefficient of the Taylor series of erf.
def taylor(deg):
    """
        Function:
            taylor
        Purpose:
            Computes the coefficients of the Taylor series of Erf.
        Arguments:
            deg (int):
                The degree of the coefficient to be computed.
        Outputs:
            coeff (mpmath.mpf):
                The deg^{th} coefficients.
    """
    num = (-1)**deg
    den = (2*deg + 1)*math.factorial(deg)
    out = tmpld.mpmath.mpf(num) / tmpld.mpmath.mpf(den)
    return (tmpld.constants.two / tmpld.mpmath.sqrt(tmpld.mpmath.pi)) * out

# Function for computing the nth coefficient of the asymptotic expansion of erf.
def asym(deg):
    """
        Function:
            asym
        Purpose:
            Computes the coefficients of the asymptotic expansion of Erf.
        Arguments:
            deg (int):
                The degree of the coefficient to be computed.
        Outputs:
            coeff (mpmath.mpf):
                The deg^{th} coefficients.
    """
    num = tmpld.math.double_factorial(2*deg - 1) * (-1)**deg
    den = 2**(deg - 1)
    out = tmpld.mpmath.mpf(num) / tmpld.mpmath.mpf(den)
    return (tmpld.constants.one / tmpld.mpmath.sqrt(tmpld.mpmath.pi)) * out

# Function for computing the degree N asymptotic expansion of erf.
def asym_series(x_val, deg):
    """
        Function:
            asym_series
        Purpose:
            Evaluates the degree "deg" asymptotic expansion of Erf at "x_val".
        Arguments:
            x_val (mpmath.mpf / float):
                A real number.
            deg (int):
                The degree of the expansion.
        Outputs:
            erf_x (mpmath.mpf):
                The asymptotic expansion of Erf(x).
    """
    x_mpf = tmpld.mpmath.mpf(x_val)
    invx = tmpld.constants.one / x_mpf
    invx_sq = invx * invx
    erf_x = tmpld.constants.zero

    # Use Horner's method to compute the sum.
    for ind in range(1, deg):
        val = asym(ind)
        erf_x += val * (invx_sq ** (ind - 1))

    # Compute the scale factor.
    erf_x *= invx*tmpld.mpmath.exp(-x_mpf*x_mpf)

    # The above is the asymptotic expansion for a shifted Erf. Shift back.
    return erf_x + tmpld.constants.one
