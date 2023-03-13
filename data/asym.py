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

# Muli-precision math routines found here.
import mpmath

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.prec = 224

# Print the coefficients for the asymptotic expansion.
def print_coeffs(coeffs, ctype = "double"):
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
        Output:
            None.
    """

    # Number of decimals to print.
    number_of_decimals = 50

    # Variable for keeping track of the indices of the coefficients.
    current_index = 0

    # Extension for literal constants, depends on data type.
    if ctype == "ldouble":
        ext = "L"
    elif ctype == "float":
        ext = "F"
    else:
        ext = ""

    print("/*  Coefficients for the asymptotic expansion." + (32*" ") + "*/")

    for coeff in coeffs:
        coeff_mpf = mpmath.mpf(coeff)
        coeff_string = mpmath.nstr(
            coeff_mpf, number_of_decimals, show_zero_exponent = True,
            strip_zeros = False, min_fixed = 0, max_fixed = 0
        ).replace("e", "E")

        # Make the exponent two decimals by adding a zero if necessary.
        if not coeff_string[-2:].isnumeric():
            coeff_string = coeff_string[:-1] + "0" + coeff_string[-1:]

        if coeff_mpf >= 0:
            print("#define A%02d (+%s%s)" % (current_index, coeff_string, ext))
        else:
            print("#define A%02d (%s%s)" % (current_index, coeff_string, ext))

        # Update the index.
        current_index += 1
