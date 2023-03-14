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

# Function for converting a Python float or mpmath.mpf object to a string.
from tmpld.string.float_to_c_string import float_to_c_string

# Function for extracting the extension of a C constant literal.
from tmpld.string.get_c_ext import get_c_ext

# Print the coefficients of a polynomial.
def print_coeffs(coeffs, ctype = "double"):
    """
        Function:
            print_coeffs
        Purpose:
            Prints the coefficients of a polynomial in a manner that is
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
    current_ind = 0

    # Extension for literal constants, depends on data type.
    ext = get_c_ext(ctype)

    # Print a comments describing what these numbers are.
    print("/*  Coefficients for the polynomial." + (42*" ") + "*/")

    # Loop through the coefficients.
    for x_val in coeffs:

        # Convert the mpmath object to a string.
        x_string = float_to_c_string(x_val)

        # Add plus sign if the coefficient is positive.
        if x_val >= 0:
            print("#define A%02d (+%s%s)" % (current_ind, x_string, ext))
        else:
            print("#define A%02d (%s%s)" % (current_ind, x_string, ext))

        current_ind += 1
