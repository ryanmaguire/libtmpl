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

# mpmath is imported here.
import tmpld

# mpmath constants.
import tmpld.constants

# Pade coeff matrix here.
from tmpld.pade.mp_get_coeff_matrix import mp_get_coeff_matrix

# Pade column vector here.
from tmpld.pade.mp_get_data_vector import mp_get_data_vector

# Given the first n + m + 1 coefficients a_k for the Taylor series,
# compute the (n, m) Pade approximant. This uses mpmath instead of sympy.
def mp_pade(coeffs, num_deg, den_deg):
    """
        Function:
            mp_pade
        Purpose:
            Computes the coefficients of the Pade approximant.
        Arguments:
            coeffs (list):
                The coefficients of the Taylor series of the function.
            num_deg (int):
                The degree of the numerator.
            den_deg (int):
                The degree of the denominator.
        Outputs:
            num_poly (list):
                The coefficients of the numerator.
            den_poly (list):
                The coefficients of the denominator.
    """

    coeff_matrix = mp_get_coeff_matrix(coeffs, num_deg, den_deg)
    data = mp_get_data_vector(coeffs, num_deg + den_deg)
    solved_coeffs = tmpld.mpmath.lu_solve(coeff_matrix, data)

    den_poly = [tmpld.constants.one]
    num_poly = [tmpld.mpmath.mpf(coeffs[0])]

    for ind in range(den_deg):
        den_poly.append(solved_coeffs[ind])

    for ind in range(num_deg):
        num_poly.append(solved_coeffs[den_deg + ind])

    return (num_poly, den_poly)
