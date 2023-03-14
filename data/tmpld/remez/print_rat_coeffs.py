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
#       Routines for computing Remez polynomials.                              #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# Functions for manipulating strings.
from tmpld.string.get_c_macro import get_c_macro

# Print the coefficients for the Remez rational approximation.
def print_rat_coeffs(num_coeffs, den_coeffs, ctype = "double"):
    """
        Function:
            print_coeffs
        Purpose:
            Prints the coefficients of a Minimax polynomial in a manner that is
            easy to copy/paste into a C program using macros.
        Arguments:
            num_coeffs (list):
                The coefficients of the numerator.
            den_coeffs (list):
                The coefficients of the denominator.
        Keywords:
            ctype (str):
                "double", "float", or "ldouble". The type of the float.
        Output:
            None.
    """

    # Index corresponding to the given coefficient.
    ind = 0

    # Comment describing what these numbers are.
    print("/*  Coefficients for the numerator of the Remez rational "
          "approximation.       */")

    # Loop through the numerator coefficients.
    for coeff in num_coeffs:

        # Convert and print the current value.
        print(get_c_macro(coeff, ind, ctype = ctype))

        ind += 1

    # Comment describing what these numbers are.
    print("\n/*  Coefficients for the denominator of the Remez rational "
          "approximation.     */")

    # Reset the index to zero for the denominator coefficients.
    ind = 0

    # Loop through the denominator coefficients.
    for coeff in den_coeffs:

        # Convert and print the current value.
        print(get_c_macro(coeff, ind, ctype = ctype))

        ind += 1
