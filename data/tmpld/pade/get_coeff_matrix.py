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

# Package for working with fractions.
import fractions

# Matrix manipulations here.
import sympy

# Computes the coefficient matrix in the Pade approximant.
def get_coeff_matrix(coeffs, num_deg, den_deg):
    """
        Function:
            get_coeff_matrix
        Purpose:
            Computes the coefficient matrix for the Pade approximant.
        Arguments:
            coeffs (list):
                The coefficients of the Maclaurin series for the function.
            num_deg (int):
                The degree of the numerator.
            den_deg (int):
                The degree of the denominator.
        Outputs:
            coeff_matrix (sympy.Matrix):
                The coefficient matrix for the Pade approximant.
    """

    # The degree of the polynomial is the sum of the two degrees.
    deg = num_deg + den_deg

    # Constants used in the computation.
    zero = fractions.Fraction(0, 1)
    minus_one = fractions.Fraction(-1, 1)

    # Initialize the coefficient matrix as a list of lists.
    coeff_matrix = []

    # Loop over the columns of the matrix.
    for column_ind in range(deg):

        # Initialize the current column as an empty list.
        column = []

        # Loop over the rows for the denominator component.
        if column_ind < den_deg:

            # Loop over the rows.
            for row_ind in range(deg):

                # This part of the matrix is triangular.
                if row_ind < column_ind:
                    column.append(zero)
                else:
                    column.append(coeffs[row_ind - column_ind])

            # Add this column to the matrix.
            coeff_matrix.append(column)

        # Loop over the rows for the numerator component.
        else:

            # Loop over the rows.
            for row_ind in range(deg):

                # This part of the matrix is diagonal.
                if column_ind == den_deg + row_ind:
                    column.append(minus_one)
                else:
                    column.append(zero)

            # Add the column to the matrix.
            coeff_matrix.append(column)

    # Convert this into a matrix and take the transpose.
    return sympy.Matrix(coeff_matrix).T
