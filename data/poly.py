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

# Muli-precision math routines found here.
import mpmath

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.prec = 224

# Evaluate a polynomial using Horner's method.
def poly_eval(coeffs, x_val):
    """
        Function:
            poly_eval
        Purpose:
            Evaluates a polynomial using Horner's method.
        Arguments:
            coeffs (list):
                The coefficients of the polynomial.
            x_val (float or mpmath.mpf):
                The point where the polynomial is computed.
        Output:
            pval (mpmath.mpf):
                The value P(x) at x = x_val, where P is the polynomial.
    """

    # The degree is given by the length of the coefficient list.
    deg = len(coeffs) - 1

    # Initialize the output to zero.
    pval = mpmath.mpf(0)

    # Convert the input to an mpmath object if necessary.
    x_mpf = mpmath.mpf(x_val)

    # Compute using Horner's method.
    for k in range(deg + 1):
        pval = x_mpf*pval + coeffs[deg - k]

    return pval

# Compute the derivative of a polynomial using Horner's method.
def dpoly_eval(coeffs, x_val):
    """
        Function:
            dpoly_eval
        Purpose:
            Evaluates the derivative of a polynomial using Horner's method.
        Arguments:
            coeffs (list):
                The coefficients of the polynomial.
            x_val (float or mpmath.mpf):
                The point where the polynomial is computed.
        Output:
            dpval (mpmath.mpf):
                The value dP(x)/dx at x = x_val, where P is the polynomial.
    """

    # The degree is given by the length of the coefficient list.
    deg = len(coeffs) - 1

    # Initialize the output to zero.
    dpval = mpmath.mpf(0)

    # Convert the input to an mpmath object if necessary.
    x_mpf = mpmath.mpf(x_val)

    # Compute using Horner's method.
    for k in range(deg):
        dpval = x_mpf*dpval + mpmath.mpf(deg - k)*coeffs[deg - k]

    return dpval

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
    d2pval = mpmath.mpf(0)

    # Convert the input to an mpmath object if necessary.
    x_mpf = mpmath.mpf(x_val)

    # Compute using Horner's method.
    for k in range(deg-1):
        scale = mpmath.mpf(deg - k)*mpmath.mpf(deg - k - 1)
        d2pval = x_mpf*d2pval + scale*coeffs[deg-k]

    return d2pval

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

    # Number of decimals to print.
    number_of_decimals = 50

    # Index corresponding to the given coefficient.
    current_ind = 0

    # Extension for literal constants, depends on data type.
    if ctype == "ldouble":
        ext = "L"
    elif ctype == "float":
        ext = "F"
    else:
        ext = ""

    print("/*  Coefficients for the polynomial."
          "                                          */")

    # Loop through the coefficients.
    for x_val in coeffs:

        # Convert to mpmath objects if necessary.
        x_mpf = mpmath.mpf(x_val)

        # Convert the mpmath object to a string.
        x_string = mpmath.nstr(
            x_mpf, number_of_decimals, show_zero_exponent = True,
            strip_zeros = False, min_fixed = 0, max_fixed = 0
        ).replace("e", "E")

        # Pad a zero to the exponent if necessary.
        if not x_string[-2:].isnumeric():
            x_string = x_string[:-1] + "0" + x_string[-1:]

        # Add plus sign if the coefficient is positive.
        if x_mpf >= 0:
            print("#define A%02d (+%s%s)" % (current_ind, x_string, ext))
        else:
            print("#define A%02d (%s%s)" % (current_ind, x_string, ext))

        current_ind += 1

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
