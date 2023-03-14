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

# String converting tool found here.
from tmpld.string.get_c_macro import get_c_macro

# Print the coefficients for the Remez polynomial.
def print_coeffs(coeffs, ctype = "double"):
    """
        Function:
            print_coeffs
        Purpose:
            Prints the coefficients of a Minimax polynomial in a manner that is
            easy to copy/paste into a C program using macros.
        Arguments:
            coeffs (list):
                The coefficients of the polynomial.
        Keywords:
            ctype (str):
                "double", "float", or "ldouble". The type of the float.
        Output:
            None.
    """

    # Index corresponding to the given coefficient.
    ind = 0

    # Print a comment describing what the numbers are.
    print("/*  Coefficients for the Remez polynomial." + (36*" ") + "*/")

    # Loop through the coefficients.
    for coeff in coeffs:

        # Convert and print the current value.
        print(get_c_macro(coeff, ind, ctype = ctype))

        ind += 1
