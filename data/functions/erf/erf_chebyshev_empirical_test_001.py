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
#       Computes the Chebyshev coefficients for the error function Erf(x).     #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 19, 2023.                                                  #
################################################################################
"""

# mpmath imported here.
import tmpld

# Chebyshev functions here.
import tmpld.chebyshev

# Polynomial tools.
import tmpld.poly

# mpmath constants.
import tmpld.constants

def func(x_val):
    """
        Function:
            func
        Purpose:
            Computes a scaled error function.
        Arguments:
            x_val (mpmath.mpf / float):
                A real number.
        Outputs:
            erf_two_x (mpmath.mpf):
                The value Erf(2 x).
    """
    return tmpld.mpmath.erf(tmpld.mpmath.mpf(x_val) * tmpld.constants.two)

def cheb_coeffs(deg):
    """
        Function:
            cheb_coeffs
        Purpose:
            Computes the Chebyshev coefficients of Erf(2 x).
        Arguments:
            deg (int):
                The degree of the expansion.
        Outputs:
            coeffs (list):
                The coefficients of the expansion.
    """
    return tmpld.chebyshev.cheb_coeffs(func, deg, 1000)

def cheb_eval(coeffs, x_val):
    """
        Function:
            cheb_eval
        Purpose:
            Evaluates the Chebyshev expansion of Erf(2 x).
        Arguments:
            coeffs (list):
                The coefficients of the Chebyshev expansion.
            x_val (float / mpmath.mpf):
                A real number.
        Outputs:
            erf_two_x (mpmath.mpf):
                The value Erf(2 x).
    """
    return tmpld.chebyshev.cheb_eval(
        coeffs, tmpld.mpmath.mpf(x_val) * tmpld.constants.half
    )

def poly_eval(coeffs, x_val):
    """
        Function:
            poly_eval
        Purpose:
            Evaluates the polynomial approximation of Erf(2 x).
        Arguments:
            coeffs (list):
                The coefficients of the polynomial approximation.
            x_val (float / mpmath.mpf):
                A real number.
        Outputs:
            erf_two_x (mpmath.mpf):
                The value Erf(2 x).
    """
    return tmpld.poly.poly_eval(
        coeffs, tmpld.mpmath.mpf(x_val) * tmpld.constants.half
    )

def diff(coeffs, x_val):
    """
        Function:
            diff
        Purpose:
            Computes the relative error of the approximation.
        Arguments:
            coeffs (list):
                The coefficients of the Chebyshev expansion.
            x_val (float / mpmath.mpf):
                A real number.
        Outputs:
            rel_err (mpmath.mpf):
                The relative error of the approximation.
    """
    y_val = cheb_eval(coeffs, x_val)
    z_val = tmpld.mpmath.erf(x_val)
    return (y_val - z_val)/z_val

# Desired precision.
EPS = 2**-54

# Print which values of N achieved double precision.
X_IN = 2
DEG = 40
for m in range(20, DEG):
    a = cheb_coeffs(m)
    y = diff(a, X_IN)

    # If the expansion was very accurate, move along.
    if abs(y) < EPS:
        b = tmpld.chebyshev.cheb_to_poly(a)
        a = []
        k = 0
        while (2*k + 1) < len(b):
            a.append(b[2*k+1])
            k += 1
        tmpld.poly.print_coeffs(a)
        break
