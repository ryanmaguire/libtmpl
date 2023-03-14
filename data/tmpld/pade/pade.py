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

# Used for solving systems of equations with rational numbers.
import sympy

# Pade coeff matrix here.
from tmpld.pade.get_coeff_matrix import get_coeff_matrix

# Pade column vector here.
from tmpld.pade.get_data_vector import get_data_vector

# Given the first n + m + 1 coefficients a_k for the Taylor series,
# compute the (n, m) Pade approximant.
def pade(coeffs, num_deg, den_deg):
    """
        Function:
            pade
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

    # Compute the coefficient matrix.
    coeff_matrix = get_coeff_matrix(coeffs, num_deg, den_deg)

    # And set up the column vector.
    data_vector = get_data_vector(coeffs, num_deg + den_deg)

    # Invert the system to compute the coefficient list.
    solved_data = list(sympy.linsolve((coeff_matrix, data_vector)))[0]

    # The denominator is normalized to have constants term "1".
    den_poly = [fractions.Fraction(1, 1)]

    # The numerator starts with the function value at x = 0.
    num_poly = [coeffs[0]]

    # Loop through the indices and create the denominator polynomial.
    for ind in range(den_deg):
        den_poly.append(solved_data[ind])

    # Do the same thing for the numerator.
    for ind in range(num_deg):
        num_poly.append(solved_data[den_deg + ind])

    # Return the two polynomials as a tuple.
    return (num_poly, den_poly)
