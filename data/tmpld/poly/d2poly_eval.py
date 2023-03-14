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
#       Routines for evaluating polynomials and derivatives.                   #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# mpmath is imported here.
import tmpld

# mpmath constants found here.
import tmpld.constants

# Compute the second derivative of a polynomial using Horner's method.
def d2poly_eval(coeffs, x_val):
    """
        Function:
            d2poly_eval
        Purpose:
            Compute the second derivative of a polynomial using Horner's method.
        Arguments:
            coeffs (list):
                The coefficients of the polynomial.
            x_val (float or mpmath.mpf):
                The point where the polynomial is computed.
        Output:
            d2pval (mpmath.mpf):
                The value d^2P(x)/dx^2 at x = x_val, where P is the polynomial.
    """

    # The degree is given by the length of the coefficient list.
    deg = len(coeffs) - 1

    # Initialize the output to zero.
    d2pval = tmpld.constants.zero

    # Convert the input to an mpmath object if necessary.
    x_mpf = tmpld.mpmath.mpf(x_val)

    # Compute using Horner's method.
    for ind in range(deg-1):
        scale = tmpld.mpmath.mpf(deg - ind)*tmpld.mpmath.mpf(deg - ind - 1)
        d2pval = x_mpf*d2pval + scale*coeffs[deg - ind]

    return d2pval
