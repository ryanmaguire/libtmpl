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
#       Basic implementation of Chebyshev polynomials.                         #
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

# Given a continuous and piecewise smooth function f on the interval [-1, 1],
# approximate the first "deg+1" Chebyshev polynomials. The higher the "order"
# factor, the better the approximation.
def cheb_coeffs(f, deg, order):
    x = [0]*order
    a = [mpmath.mpf(0)]*(deg+1)

    # The zeroes of the Chebyshev polynomials are used to approximate the
    # coefficients. The zeros of the nth polynomial are given by:
    #   x_k = cos(pi (k + 1/2) / n)
    # Evaluate the given function f at these points.
    for k in range(order):
        angle = mpmath.mpf(2*k + 1)*mpmath.pi / mpmath.mpf(2*order)
        y = mpmath.cos(angle)
        x[k] = f(y)

    # Using the discrete orthogonality condition of the Chebyshev polynomials,
    # one obtains the following approximation for the Chebyshev coefficients:
    #              N - 1
    #              -----
    #          2   \
    #   a_n = ---  /     cos(n pi (k + 1/2) / N) f(x_k)
    #          N   -----
    #              k = 0
    #
    # Where N is the "order" of the approximation, and x_k is the kth zero of
    # the Chebyshev polynomial computed above.
    for n in range(deg+1):
        for k in range(order):
            angle = mpmath.mpf(n*(2*k + 1))*mpmath.pi / mpmath.mpf(2*order)
            a[n] += x[k]*mpmath.cos(angle)

        a[n] = mpmath.mpf(2) * a[n] / mpmath.mpf(order)

    return a

# Evaluation of the Chebyshev expansion with coefficents "a" at the value "x".
def cheb_eval(a, x):
    deg = len(a)
    d0 = mpmath.mpf(0)
    d1 = mpmath.mpf(0)
    twox = mpmath.mpf(2)*x

    # Use the Clenshaw algorithm to efficiently evaluate the expansion. This is
    # a generalization of Horner's algorithm to evaluate Taylor polynomials.
    for n in range(deg - 1):
        temp = d0
        d0 = twox*d0 - d1 + a[deg - 1 - n]
        d1 = temp

    return x*d0 - d1 + mpmath.mpf(0.5)*a[0]

# Convert the coefficients of a Chebyshev expansion into a regular polynomial.
# That is, given coefficients c_k, compute the values a_k such that:
#         N                  N
#       -----              -----
#       \                  \
#       /     c_k T_k(x) = /     a_k x^k
#       -----              -----
#       k = 0              k = 0
# Evaluation of a polynomial via Horner's method is usually faster than
# evaluation of a Chebyshev expansion using Clenshaw's algorithm.
def cheb_to_poly(c):
    deg = len(c) - 1
    zero = mpmath.mpf(0)
    one = mpmath.mpf(1)
    two = mpmath.mpf(2)

    P = [zero]*(deg + 1)
    T0 = [zero]*(deg + 1)
    T1 = [zero]*(deg + 1)

    for n in range(deg + 1):
        # The Chebyshev recurrence is T_{n+2}(x) = 2x T_{n+1}(x) - T_{n}(x).
        # If n == 0 or n == 1 do not use the recurrence, just set the values.
        # We have T_0(x) = 1 and T_1(x) = x.
        if n == 0:
            T0[0] = one
            T2 = [k for k in T0]
        elif n == 1:
            T1[1] = one
            T2 = [k for k in T1]

        # For n > 1 use the recurrence to compute the coefficients.
        else:
            T2 = [zero]*(deg + 1)
            for m in range(deg + 1):
                if m == 0:
                    T2[0] = -T0[0]
                else:
                    T2[m] = two*T1[m-1] - T0[m]

        # T2[m] is the coefficient of x^m in T_n(x). This is weighted by c_n
        # in the expansion. The regularly polynomial will therefore have
        # c_n x^m in it. Add this to the m^th entry of P.
        for m in range(deg + 1):
            P[m] += c[n]*T2[m]

        # If n == 0 or n == 1, there is no need to reset T0 or T1. Skip this.
        if n > 1:
            T0 = [k for k in T1]
            T1 = [k for k in T2]

    # The zeroth coefficient of the Chebyshev expansion is special and is
    # multiplied by one-half in Clenshaw's algorithm. We did not take this into
    # account above, and hence need to subtract c[0] / 2 from the zeroth entry.
    P[0] -= c[0] / two
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

    print("/*  Coefficients for the Chebyshev approximation."
          "                             */")
    for n in range(len(c)):
        x = mpmath.mpf(c[n])
        s = mpmath.nstr(x, N, show_zero_exponent = True, strip_zeros = False,
                        min_fixed = 0, max_fixed = 0)
        s = s.replace("e", "E")

        if not s[-2:].isnumeric():
            s = s[:-1] + "0" + s[-1:]

        if x >= 0:
            print("#define C%02d (+%s%s)" % (n, s, ext))
        else:
            print("#define C%02d (%s%s)" % (n, s, ext))
