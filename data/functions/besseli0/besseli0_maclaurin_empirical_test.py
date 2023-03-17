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
#       Determine the degrees necessary for the bessel I0 asymptotic expansion #
#       to achieve double precision in certain windows.                        #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 10, 2023.                                                  #
################################################################################
"""

# mpmath imported here.
import tmpld

# Polynomial evaluation via Horner's method.
import tmpld.poly

# Scaled Bessel I0 function.
import besseli0

# Desired precision.
EPS = 2**-23

# Function for computing the difference of the approximation with scipy.
def diff(coeffs, x_val):
    """
        Function:
            diff
        Purpose:
            Computes relative error of Taylor series.
        Arguments:
            coeffs (list):
                Taylor coefficients.
            x_val (float / mpmath.mpf):
                A real number.
        Outputs:
            rel_err (mpmath.mpf):
                The relative error.
    """
    y_val = tmpld.mpmath.besseli(0, x_val)
    z_val = tmpld.poly.poly_eval(coeffs, x_val*x_val)
    return (y_val - z_val) / y_val

# Print which values of N achieved double precision.
X_IN = 8

for m in range(2, 50):
    a = [besseli0.taylor(n) for n in range(m)]
    y = diff(a, X_IN)

    # If the expansion was very accurate, move along.
    if abs(y) < EPS:
        b = [
            tmpld.mpmath.mpf(k.numerator) / tmpld.mpmath.mpf(k.denominator)
            for k in a
        ]
        tmpld.poly.print_coeffs(b)
        break
