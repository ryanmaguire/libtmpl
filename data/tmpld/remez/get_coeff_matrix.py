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
#       Routines for computing Remez polynomials.                              #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# mpmath is imported here.
import tmpld

# Computes the coefficient matrix for the Remez exchange from the data points.
def get_coeff_matrix(x_vals):
    """
        Function:
            get_coeff_matrix
        Purpose:
            Computes the coefficient matrix for the Remez exchange.
        Arguments:
            x_vals (list or array):
                The x-value data.
            y_vals (list or array):
                The values func(x_vals) where func is the function being
                approximated by the Minimax polynomial.
        Outputs:
            coeff_matrix (mpmath.matrix):
                The coefficients matrix of the approximate Minimax polynomial.
    """

    # The degree of the polynomial is given by the size of the input array.
    deg = len(x_vals) - 1

    # We'll compute the entries of the coefficient matrix term-by-term.
    coeff_matrix = []

    # Loop over the rows of the matrix.
    for row_ind in range(deg + 2):
        row = []

        # And loop over the columns of the matrix.
        for column_ind in range(deg + 2):

            # The last column is given by the error term E. The coefficients
            # simply osciallate, (-1)^k where k is the row index.
            if column_ind == deg + 1:
                row.append(tmpld.mpmath.mpf((-1)**row_ind))

            # Otherwise the elements are given by powers of x.
            else:
                row.append(tmpld.mpmath.mpf(x_vals[row_ind]**column_ind))

        # Add this row to the matrix.
        coeff_matrix.append(row)

    # Convert our list-of-lists to a matrix using mpmath.
    return tmpld.mpmath.matrix(coeff_matrix)
