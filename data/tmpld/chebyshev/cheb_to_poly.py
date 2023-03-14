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
#       Converts a sum of Chebyshev polynomials to a sum of powers x^n.        #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# mpmath constants found here.
import tmpld.constants

# Convert the coefficients of a Chebyshev expansion into a regular polynomial.
# That is, given coefficients c_k, compute the values a_k such that:
#         N                  N
#       -----              -----
#       \                  \
#       /     c_k T_k(x) = /     a_k x^k
#       -----              -----
#       k = 0              k = 0
# Evaluation of a polynomial via Horner's method is usually faster than
# evaluation of a Chebyshev expansion using Clenshaw's algorithm.
def cheb_to_poly(coeffs):
    """
        Function:
            cheb_to_poly
        Purpose:
            Converts a Chebyshev expansion into an actual polynomial.
        Arguments:
            coeffs (list):
                The coefficients of the Chebyshev expansion.
        Outputs:
            poly_coeffs (list):
                The coefficients of the polynomial.
    """

    # The degree is given by the number of elements.
    deg = len(coeffs) - 1

    # Initialize the output to a list of zeros.
    poly_coeffs = [tmpld.constants.zero]*(deg + 1)

    # Helper arrays used to perform a Cauchy-like product.
    arr0 = [tmpld.constants.zero]*(deg + 1)
    arr1 = [tmpld.constants.zero]*(deg + 1)

    # Loop over the coefficients in the Chebyshev expansion.
    for ind0 in range(deg + 1):

        # The Chebyshev recurrence is T_{n+2}(x) = 2x T_{n+1}(x) - T_{n}(x).
        # If n == 0 or n == 1 do not use the recurrence, just set the values.
        # We have T_0(x) = 1 and T_1(x) = x.
        if ind0 == 0:
            arr0[0] = tmpld.constants.one
            arr2 = arr0.copy()
        elif ind0 == 1:
            arr1[1] = tmpld.constants.one
            arr2 = arr1.copy()

        # For n > 1 use the recurrence to compute the coefficients.
        else:
            arr2 = [tmpld.constants.zero]*(deg + 1)
            for ind1 in range(deg + 1):
                if ind1 == 0:
                    arr2[0] = -arr0[0]
                else:
                    arr2[ind1] = tmpld.constants.two*arr1[ind1-1] - arr0[ind1]

        # arr2[m] is the coefficient of x^m in T_n(x). This is weighted by c_n
        # in the expansion. The regularly polynomial will therefore have
        # c_n x^m in it. Add this to the m^th entry of P.
        for ind1 in range(deg + 1):
            poly_coeffs[ind1] += coeffs[ind0]*arr2[ind1]

        # If n == 0 or n == 1, there is no need to reset T0 or T1. Skip this.
        if ind0 > 1:
            arr0 = arr1.copy()
            arr1 = arr2.copy()

    # The zeroth coefficient of the Chebyshev expansion is special and is
    # multiplied by one-half in Clenshaw's algorithm. We did not take this into
    # account above, and hence need to subtract c[0] / 2 from the zeroth entry.
    poly_coeffs[0] -= coeffs[0] / tmpld.constants.two
    return poly_coeffs
