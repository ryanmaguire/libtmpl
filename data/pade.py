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
#       Routines for computing Pade approximants.                              #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# Many Pade approximants deal with rational coefficients only.
import fractions

# Muli-precision math routines found here.
import mpmath

# Used for solving systems of equations with rational numbers.
import sympy

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.dps = 224

# TODO: Explain the Pade algorithm below. Add comments and what-not.

# Given the first n + m + 1 coefficients a_k for the Taylor series,
# compute the (n, m) Pade approximant.
def pade(a, n, m):
    N = m + n
    zero = fractions.Fraction(0, 1)
    one = fractions.Fraction(1, 1)
    minus_one = fractions.Fraction(-1, 1)
    A = []
    b = []

    for k in range(N):
        b.append(-a[k+1])

    for i in range(N):
        column = []
        if i < m:
            for j in range(N):
                if j < i:
                    column.append(zero)
                else:
                    column.append(a[j-i])

            A.append(column)
        else:
            for j in range(N):
                if i == m + j:
                    column.append(minus_one)
                else:
                    column.append(zero)

            A.append(column)

    A = sympy.Matrix(A).T
    b = sympy.Matrix(b)
    system = (A, b)
    c = list(sympy.linsolve(system))[0]
    Q = [one]
    P = [a[0]]

    for k in range(m):
        Q.append(c[k])

    for k in range(n):
        P.append(c[m+k])

    return (P, Q)

# Given the first n + m + 1 coefficients a_k for the Taylor series,
# compute the (n, m) Pade approximant. This uses mpmath instead of sympy.
def mp_pade(a, n, m):
    N = n + m
    an = [mpmath.mpf(k) for k in a]
    zero = mpmath.mpf(0)
    one = mpmath.mpf(1)
    minus_one = mpmath.mpf(-1)
    A = []
    b = []

    for k in range(N):
        b.append(-an[k+1])

    for i in range(N):
        column = []
        if i < m:
            for j in range(N):
                if j < i:
                    column.append(zero)
                else:
                    column.append(an[j-i])

            A.append(column)
        else:
            for j in range(N):
                if i == m + j:
                    column.append(minus_one)
                else:
                    column.append(zero)

            A.append(column)

    A = mpmath.matrix(A).transpose()
    c = mpmath.lu_solve(A, b)

    Q = [one]
    P = [an[0]]

    for k in range(m):
        Q.append(c[k])

    for k in range(n):
        P.append(c[m+k])

    return (P, Q)

# Print the coefficients for the (P, Q) Pade approximant in a manner that is
# easy to copy / paste into C code.
def print_coeffs(P, Q, ctype = "double"):

    # Number of decimals to print.
    N = 50

    # Extension for literal constants, depends on data type.
    if ctype == "ldouble":
        ext = "L"
    elif ctype == "float":
        ext = "F"
    else:
        ext = ""

    print("/*  Coefficients for the numerator of the Pade approximant."
          "                   */")
    for n in range(len(P)):
        x = mpmath.mpf(P[n].numerator) / mpmath.mpf(P[n].denominator)
        s = mpmath.nstr(x, N, show_zero_exponent = True, strip_zeros = False,
                        min_fixed = 0, max_fixed = 0)
        s = s.replace("e", "E")

        if not s[-2:].isnumeric():
            s = s[:-1] + "0" + s[-1:]

        if P[n] >= 0:
            print("#define P%02d (+%s%s)" % (n, s, ext))
        else:
            print("#define P%02d (%s%s)" % (n, s, ext))

    print("\n/*  Coefficients for the denominator of the Pade approximant."
          "                 */")
    for n in range(len(Q)):
        x = mpmath.mpf(Q[n].numerator) / mpmath.mpf(Q[n].denominator)
        s = mpmath.nstr(x, N, show_zero_exponent = True, strip_zeros = False,
                        min_fixed = 0, max_fixed = 0)
        s = s.replace("e", "E")

        if not s[-2:].isnumeric():
            s = s[:-1] + "0" + s[-1:]

        if Q[n] >= 0:
            print("#define Q%02d (+%s%s)" % (n, s, ext))
        else:
            print("#define Q%02d (%s%s)" % (n, s, ext))

# Print function when the coefficients are mpmath instead of fractions.
def mp_print_coeffs(P, Q, ctype = "double"):

    # Number of decimals to print.
    N = 50

    # Extension for literal constants, depends on data type.
    if ctype == "ldouble":
        ext = "L"
    elif ctype == "float":
        ext = "F"
    else:
        ext = ""

    print("/*  Coefficients for the numerator of the Pade approximant."
          "                   */")
    for n in range(len(P)):
        x = P[n]
        s = mpmath.nstr(x, N, show_zero_exponent = True, strip_zeros = False,
                        min_fixed = 0, max_fixed = 0)
        s = s.replace("e", "E")

        if not s[-2:].isnumeric():
            s = s[:-1] + "0" + s[-1:]

        if P[n] >= 0:
            print("#define P%02d (+%s%s)" % (n, s, ext))
        else:
            print("#define P%02d (%s%s)" % (n, s, ext))

    print("\n/*  Coefficients for the denominator of the Pade approximant."
          "                 */")
    for n in range(len(Q)):
        x = Q[n]
        s = mpmath.nstr(x, N, show_zero_exponent = True, strip_zeros = False,
                        min_fixed = 0, max_fixed = 0)
        s = s.replace("e", "E")

        if not s[-2:].isnumeric():
            s = s[:-1] + "0" + s[-1:]

        if Q[n] >= 0:
            print("#define Q%02d (+%s%s)" % (n, s, ext))
        else:
            print("#define Q%02d (%s%s)" % (n, s, ext))
