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
#       Evaluates a Chebyshev approximation with Clenshaw's algorithm.         #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# mpmath is imported here.
import tmpld

# mpmath constants found here.
import tmpld.constants

# Evaluation of the Chebyshev expansion with coefficents "a" at the value "x".
def cheb_eval(coeffs, val):
    """
        Function:
            cheb_eval
        Purpose:
            Evaluates a Chebyshev approximation using Clenshaw's algorithm.
        Arguments:
            coeffs (list):
                A list of coefficients, the coefficients of the approximation.
            val (float / mpmath.mpf):
                The point in [-1, 1] where the approximation is evaluated.
        Outputs:
            out (mpmath.mpf):
                The Chebyshev approximation for "coeffs" at the point "val".
    """

    # The degree is given by the number of elements in the "coeffs" list.
    deg = len(coeffs) - 1

    # Convert the input to an mpmath.mpf object if needed.
    val_mpf = tmpld.mpmath.mpf(val)

    # Placeholder variables used in Clenshaw's algorithm.
    y_val = tmpld.constants.zero
    z_val = tmpld.constants.zero

    # Twice the input.
    two_val = tmpld.constants.two*val_mpf

    # Use the Clenshaw algorithm to efficiently evaluate the expansion. This is
    # a generalization of Horner's algorithm to evaluate Taylor polynomials.
    for ind in range(deg):
        temp = y_val
        y_val = two_val*y_val - z_val + coeffs[deg - ind]
        z_val = temp

    return val_mpf*y_val - z_val + tmpld.mpmath.mpf(0.5)*coeffs[0]
