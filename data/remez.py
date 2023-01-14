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

# Muli-precision math routines found here.
import mpmath

# Polynomial evaluation found here.
import poly

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.dps = 224

# TODO: Add a more detailed explanation of the Remez exchange algorithm.

# Given a function f and derivative fp "f-prime" on the interval [start, end],
# compute the Remez polynomial of degree "deg" using the Remez exchange.
def remez(f, fp, deg, start, end):
    start = mpmath.mpf(start)
    end = mpmath.mpf(end)

    # We start with deg + 1 evenly spaced samples on the interval [start, end].
    dx = (end - start)/mpmath.mpf(deg + 1)
    x = [0]*(deg + 2)
    y = [0]*(deg + 2)
    z = [0]*(deg + 1)

    # Compute the sample points and the function at these points.
    for m in range(deg + 2):
        x[m] = start + dx*mpmath.mpf(m)
        y[m] = f(mpmath.mpf(x[m]))

    # Iteratively apply the Remez exchange algorithm until the error is decent.
    while(True):
        A = []
        for m in range(deg + 2):
            column = []
            for n in range(deg + 2):
                if n == deg + 1:
                    column.append(mpmath.mpf((-1)**m))
                else:
                    column.append(mpmath.mpf(x[m]**n))

            A.append(column)

        # We have n+2 equations with n+2 unknowns (the n+1 coefficients, and
        # the error estimate). Solve this using matrices.
        A = mpmath.matrix(A)
        b = mpmath.matrix(y)
        c = mpmath.lu_solve(A, b)
        c = list(c)
        max_err = mpmath.mpf(0)

        # Get a rough estimate to the max error in the polynomial.
        for n in range(deg + 1):
            tmp = abs(poly.poly_eval(c[0:deg+1], x[n]) - y[n])
            if tmp > max_err:
                max_err = tmp

        # Print the error and ask the user if this is adequate.
        print("%E" % tmp)
        stop = input("Stop? (y/n): ")

        # Stop the computation if this is good enough.
        if stop.lower() == "y":
            return c[0:deg+1]

        # Otherwise use Newton's method to compute local mins and maxes near
        # the sample point, and update the samples to these nodes.
        for n in range(1, deg):
            x0 = x[n]
            fx0 = f(x0)
            fpx0 = fp(x0)
            Px0 = poly.poly_eval(c, x0)
            dPx0 = poly.dpoly_eval(c, x0)
            x[n] = x0 - (Px0 - fx0)/(dPx0 - fpx0)
            y[n] = f(x[n])

# Print the coefficients for the Remez polynomial.
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

    print("/*  Coefficients for the numerator of the Remez polynomial."
          "                   */")
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
