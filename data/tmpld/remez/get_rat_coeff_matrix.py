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

# mpmath import here.
import tmpld

# Computes the coefficient matrix for the rational Remez exchange.
def get_rat_coeff_matrix(x_vals, y_vals, num_deg, den_deg, error_guess):
    """
        Function:
            get_rat_coeff_matrix
        Purpose:
            Computes the coefficient matrix for the rational Remez exchance.
        Arguments:
            x_vals (list):
                The data points in the x axis.
            y_vals (list):
                The evaluation of the given function at the data points x_vals.
            num_deg (int):
                The degree of the numerator.
            den_deg (int):
                The degree of the denominator.
            error_guess (float / mpmath.mpf):
                The guess for the error in the Remez rational exchange.
        Outputs:
            coeff_matrix (mpmath.matrix):
                The coefficient matrix for the rational Remez exchange.
    """

    # The degree of the polynomial is given by the size of the input array.
    deg = num_deg + den_deg

    # Start the matrix as a list of lists.
    coeff_matrix = []

    # Loop over the rows of the matrix.
    for row_ind in range(deg + 2):
        row = []

        # The first coefficients of the row come from the polynomial in the
        # numerator.
        for num_ind in range(num_deg + 1):
            row.append(x_vals[row_ind]**num_ind)

        # The next coefficient come from the polynomial in the denominator,
        # combined with the data y and the error guess E0.
        for den_ind in range(1, den_deg + 1):
            row.append((x_vals[row_ind]**den_ind) *
                       (((-1)**row_ind)*error_guess - y_vals[row_ind]))

        # The last column is the (-1)^k E term.
        row.append((-1)**row_ind)
        coeff_matrix.append(row)

    # We have n+2 equations with n+2 unknowns (the n+1 coefficients, and
    # the error estimate). Solve this using matrices.
    return tmpld.mpmath.matrix(coeff_matrix)
