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
#   Date:   March 14, 2023.                                                    #
################################################################################
"""

# mpmath imported here.
import tmpld

# mpmath constants.
import tmpld.constants

# Computes the Pade coefficient matrix with mpmath.mpf entries.
def mp_get_coeff_matrix(coeffs, num_deg, den_deg):
    """
        Function:
            mp_get_coeff_matrix
        Purpose:
            Computes the coefficient matrix of the Pade approximant.
        Arguments:
            coeffs (list):
                The coefficients of the Taylor series.
            num_deg (int):
                The degree of the numerator.
            den_deg (int):
                The degree of the denominator.
        Outputs:
            coeff_matrix (mpmath.matrix):
                The coefficient matrix.
    """

    # The degree is the sum of the two degrees.
    deg = num_deg + den_deg

    # Convert the input into mpf objects.
    coeffs_mpf = [tmpld.mpmath.mpf(k) for k in coeffs]

    # Initialize the coefficient matrix as a list of lists.
    coeff_matrix = []

    # Loop over the columns of the matrix.
    for column_index in range(deg):

        # Initialize the column as an empty list.
        column = []

        # Loop over the denominator part.
        if column_index < den_deg:

            # Loop over the rows.
            for row_index in range(deg):

                # This part of the matrix is triangular.
                if row_index < column_index:
                    column.append(tmpld.constants.zero)
                else:
                    column.append(coeffs_mpf[row_index - column_index])

            # Add the column to the matrix.
            coeff_matrix.append(column)

        # Loop over the numerator part of the matrix.
        else:

            # Loop over the rows.
            for row_index in range(deg):

                # This part of the matrix is diagonal.
                if column_index == den_deg + row_index:
                    column.append(tmpld.constants.minus_one)
                else:
                    column.append(tmpld.constants.zero)

            # Add this column to the matrix.
            coeff_matrix.append(column)

    # Convert to an mpmath matrix and return.
    return tmpld.mpmath.matrix(coeff_matrix).transpose()
