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
#       Routines for working with asymptotic expansions.                       #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 10, 2023.                                                  #
################################################################################
"""

# String converting tools found here.
from tmpld.string.float_to_c_string import float_to_c_string
from tmpld.string.get_c_ext import get_c_ext

# Print the coefficients of an asymptotic expansion.
def print_coeffs(coeffs, ctype = "double", prefix = "A"):
    """
        Function:
            print_coeffs
        Purpose:
            Prints the coefficients of an asymptotic expansion in a manner that
            is easy to copy/paste into a C program using macros.
        Arguments:
            coeffs (list):
                The coefficients.
        Keywords:
            ctype (str):
                "double", "float", or "ldouble". The type of the float.
            prefix (str):
                The character that prepends the macro.
        Output:
            None.
    """

    # Variable for keeping track of the indices of the coefficients.
    current_index = 0

    # Extension for literal constants, depends on data type.
    ext = get_c_ext(ctype)

    # Comment for the C code describing what the numbers are.
    print("/*  Coefficients for the asymptotic expansion." + (32*" ") + "*/")

    # Loop through the coefficients and print.
    for coeff in coeffs:

        # Convert the number to a string.
        coeff_string = float_to_c_string(coeff)

        # Create a macro for the current coefficient.
        macro_tuple = (prefix, current_index, coeff_string, ext)

        # Negative numbers have a minus sign. Add a plus to positive numbers.
        if coeff >= 0:
            macro_string = "#define %s%02d (+%s%s)" % macro_tuple
        else:
            macro_string = "#define %s%02d (%s%s)" % macro_tuple

        # Lastly, print the macro to the screen.
        print(macro_string)

        # Update the index.
        current_index += 1
