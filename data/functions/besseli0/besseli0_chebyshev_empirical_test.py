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
#       Computes the Chebyshev coefficients for the Bessel Function I0.        #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# mpmath imported here.
import tmpld

# Chebyshev evaluation and coefficients.
import tmpld.chebyshev

# Polynomial evaluation via Horner's method.
import tmpld.poly

# Scaled Bessel I0 function.
import besseli0

# Transforms [8, infty] to [-1, 1].
def transform(x_val):
    """
        Function:
            transform
        Purpose:
            Transforms the compactification [8, infty] into [-1, 1].
        Arguments:
            x_val (float / mpmath.mpf):
                A real number 8 <= x <= infty.
        Outputs:
            y_val (mpmath.mpf):
                The transformed value of x.
    """
    x_mpf = tmpld.mpmath.mpf(x_val)
    return tmpld.mpmath.mpf(16)/x_mpf - tmpld.mpmath.mpf(1)

# Evaluates, using the Clenshaw algorithm, the Chebyshev expansion, of the
# transformed variable. Converts [8, infty] to [-1, 1] and performs the sum.
def cheb_eval(coeffs, x_val):
    """
        Function:
            cheb_eval
        Purpose:
            Translates [8, infty] to [-1, 1] and evaluates the Chebyshev
            approximation of I0(x).
        Arguments:
            coeffs (list):
                The coefficients of the Chebyshev expansion.
            x_val (float / mpmath.mpf):
                A real number 8 <= x <= infty.
        Outputs:
            I0_x (mpmath.mpf):
                The Bessel I0 function of x, scaled by 1 / sqrt(x).
    """
    y_mpf = transform(x_val)
    z_mpf = tmpld.chebyshev.cheb_eval(coeffs, y_mpf)
    return z_mpf/tmpld.mpmath.sqrt(x_val)

# Evaluates a polynomial in the transformed variable.
def poly_eval(coeffs, x_val):
    """
        Function:
            poly_eval
        Purpose:
            Translates [8, infty] to [-1, 1] and evaluates the polynomial
            approximation of I0(x).
        Arguments:
            coeffs (list):
                The coefficients of the polynomial approximation.
            x_val (float / mpmath.mpf):
                A real number 8 <= x <= infty.
        Outputs:
            I0_x (mpmath.mpf):
                The Bessel I0 function of x, scaled by 1 / sqrt(x).
    """
    y_mpf = transform(x_val)
    z_mpf = tmpld.poly.poly_eval(coeffs, y_mpf)
    return z_mpf/tmpld.mpmath.sqrt(x_val)

# Computes the difference of the scaled Bessel function with the Cheb approx.
def diff(coeffs, x_val):
    """
        Function:
            diff
        Purpose:
            Computes the relative error in the Chebyshev expansion of I0(x).
        Arguments:
            coeffs (list):
                The coefficients of the Chebyshev expansion.
            x_val (float / mpmath.mpf)
                A real number.
        Outputs:
            rel_err (mpmath.mpf):
                The relative error.
    """
    y_val = cheb_eval(coeffs, x_val)
    z_val = tmpld.mpmath.besseli(0, x_val)*tmpld.mpmath.exp(-x_val)
    return (y_val - z_val) / z_val

# Computes the error between poly approx and Cheb approx.
def diff2(cheb_coeffs, poly_coeffs, x_val):
    """
        Function:
            diff
        Purpose:
            Computes the relative error in the Chebyshev expansion and
            polynomial approximation for I0(x).
        Arguments:
            cheb_coeffs (list):
                The coefficients of the Chebyshev expansion.
            poly_coeffs (list):
                The coefficients of the polynomial approximation.
            x_val (float / mpmath.mpf)
                A real number.
        Outputs:
            rel_err (mpmath.mpf):
                The relative error.
    """
    y_val = cheb_eval(cheb_coeffs, x_val)
    z_val = poly_eval(poly_coeffs, x_val)
    return (y_val - z_val)/z_val

# Desired precision.
EPS = 2**-52

# Print which values of N achieved double precision.
X_IN = 20
DEG = 21

for m in range(2, DEG):
    a = tmpld.chebyshev.cheb_coeffs(besseli0.scaled_i0, m, 1000)
    y = diff(a, X_IN)

    # If the expansion was very accurate, move along.
    if abs(y) < EPS:
        b = tmpld.chebyshev.cheb_to_poly(a)
        tmpld.poly.print_coeffs(b)

        break
