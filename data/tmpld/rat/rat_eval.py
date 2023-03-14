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
#       Routines for working with rational functions.                          #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# mpmath imported here.
import tmpld

# mpmath constants.
import tmpld.constants

# Evaluate a rational function given two arrays of coefficients.
def rat_eval(num_coeffs, den_coeffs, x_val):
    """
        Function:
            rat_eval
        Purpose:
            Computes P(x)/Q(x) using Horner's method.
        Arguments:
            num_coeffs (list):
                The coefficients of P(x).
            den_coeffs (list):
                The coefficients of Q(x).
            x_val (float or mpmath.mpf):
                The input to the rational function P(x)/Q(x).
        Output:
            val (mpmath.mpf):
                The value P(x)/Q(x) at x = x_val.
    """

    # The degrees of the numerator and denominator are given by the lengths of
    # the lists of coefficients.
    num_deg = len(num_coeffs) - 1
    den_deg = len(den_coeffs) - 1

    # Initialize the numerator and denominator to zero.
    num = tmpld.constants.zero
    den = tmpld.constants.zero

    # Convert the input to an mpmath object if necessary.
    x_mpf = tmpld.mpmath.mpf(x_val)

    # Use Horner's method on the numerator.
    for ind in range(num_deg + 1):
        num = x_mpf*num + num_coeffs[num_deg - ind]

    # Apply Horner's method for the denominator.
    for ind in range(den_deg + 1):
        den = x_mpf*den + den_coeffs[den_deg - ind]

    # Return the quotient.
    return num/den
