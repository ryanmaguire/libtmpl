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
mpmath.mp.dps = 224

# Evaluate a polynomial with coeffs "a" at the point "x" using Horner's method.
def poly_eval(a, x):
    deg = len(a) - 1
    P = mpmath.mpf(0)

    # Compute using Horner's method.
    for n in range(deg + 1):
        P = x*P + a[deg - n]

    return P

# Compute the derivative of a polynomial using Horner's method.
def dpoly_eval(a, x):
    deg = len(a) - 1
    P = mpmath.mpf(0)

    # Compute the derivative using Horner's method.
    for n in range(deg):
        P = x*P + mpmath.mpf(deg - n)*a[deg - n]

    return P

# Compute the second derivative of a polynomial using Horner's method.
def d2poly_eval(a, x):
    deg = len(a) - 1
    P = mpmath.mpf(0)

    # Compute the derivative using Horner's method.
    for n in range(deg - 1):
        P = x*P + mpmath.mpf(deg - n)*mpmath.mpf(deg - n - 1)*a[deg - n]

    return P

# Print the coefficients for the Chebyshev expansion.
def print_coeffs(c, ctype = "double"):

    # Number of decimals to print.
    N = 50

    # Extension for literal constants, depends on data type.
    if ctype == "ldouble":
        ext = "L"
    elif ctype == "float":
        ext = "F"
    else:
        ext = ""

    print("/*  Coefficients for the polynomial."
          "                                          */")
    for n in range(len(c)):
        x = mpmath.mpf(c[n])
        s = mpmath.nstr(x, N, show_zero_exponent = True, strip_zeros = False,
                        min_fixed = 0, max_fixed = 0)
        s = s.replace("e", "E")

        if not s[-2:].isnumeric():
            s = s[:-1] + "0" + s[-1:]

        if x >= 0:
            print("#define A%02d (+%s%s)" % (n, s, ext))
        else:
            print("#define A%02d (%s%s)" % (n, s, ext))

def print_poly_helper(n, A = "A", skip = 4):
    print("/*  Helper macro for evaluating a polynomial via Horner's method."
          "             */")
    print("#define TMPL_POLY_EVAL(z) \\")
    for k in range (n-1):
        print(" "*(skip*k) + "%s%02d + z*(\\" % (A, k))
    print(" "*(skip*(n-1)) + "%s%02d + z*%s%02d\\" % (A, n-1, A, n))

    for k in range(2, n):
        print(" "*(skip*(n-k)) + ")\\")

    print(")")
