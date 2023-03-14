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

# Prints a helper macro for evaluating a polynomial with Horner's method.
def print_poly_helper(deg, label = "A", skip = 4):
    """
        Function:
            print_poly_helper
        Purpose:
            Prints a helper macro for evaluating a polynomial in C using
            Horner's method. Easy to just copy and paste.
        Arguments:
            deg (int):
                The degree of the polynomial.
        Keywords:
            label (str):
                The label for the polynomial coefficients.
            skip (int):
                The number of spaces to pad the lines with.
    """

    # Print a comment describing what this is.
    print("/*  Helper macro for evaluating a polynomial via Horner's method."
          "             */")

    # Print the start of the macro.
    print("#define TMPL_POLY_EVAL(z) \\")

    # Print each line of Horner's method.
    for k in range (deg - 1):
        print(" "*(skip*k) + "%s%02d + z*(\\" % (label, k))

    # Print the final line, which is A_{deg-1} + x*A_{deg}.
    print(" "*(skip*(deg-1))+"%s%02d + z*%s%02d\\" % (label, deg-1, label, deg))

    # Add all of the closing parenthesis.
    for k in range(2, deg):
        print(" "*(skip*(deg - k)) + ")\\")

    print(")")
