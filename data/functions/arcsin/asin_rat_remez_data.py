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
#       Computes the rational minimax coefficients for arc-sine.               #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   May 13, 2023.                                                      #
################################################################################
"""

# mpmath imported here.
import tmpld

# Algorithm for computing Pade coefficients given here.
import tmpld.remez

# Arcsin Taylor coefficients given here.
import arcsin

# Compute and print the coefficients for the Pade approximant of asin(x).
coeffs = [arcsin.taylor(n) for n in range(1, 60)]

# Computes the Taylor series for (asin(sqrt(x)) - x) / x^3
def asin_sqrt_taylor(x_val):
    """
        Function:
            asin_sqrt_taylor
        Purpose:
            Computes the Taylor series of asin(x) in powers of x^n instead of
            x^{2n+1}. Roughly like asin(sqrt(x)).
    """
    x_mpf = tmpld.mpmath.mpf(x_val)
    out = tmpld.mpmath.mpf(0)
    deg = len(coeffs) - 1

    for ind in range(deg+1):
        num = coeffs[deg - ind].numerator
        den = coeffs[deg - ind].denominator
        coeff = tmpld.mpmath.mpf(num) / tmpld.mpmath.mpf(den)
        out = out*x_mpf + coeff

    return out

# Print the coefficients for the rational minimax approximation.
(P, Q, err) = tmpld.remez.rat_remez(asin_sqrt_taylor, 5, 4, -0.5, 0.5)
tmpld.remez.print_rat_coeffs(P, Q)
