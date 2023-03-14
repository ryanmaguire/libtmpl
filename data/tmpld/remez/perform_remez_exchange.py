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

# mpmath is import here.
import tmpld

# Remez coefficient matrix function.
from tmpld.remez.get_coeff_matrix import get_coeff_matrix

# Given (x_vals, y_vals) data, inverts the Remez matrix and solves.
def perform_remez_exchange(x_vals, y_vals):
    """
        Function:
            perform_remez_exchange
        Purpose:
            Given data (x_vals, y_vals), inverts the Remez matrix and solves
            for the coefficients of the approximant Minimax polynomial.
        Arguments:
            x_vals (list or array):
                The x-value data.
            y_vals (list or array):
                The values func(x_vals) where func is the function being
                approximated by the Minimax polynomial.
        Outputs:
            coeffs (list):
                The coefficients of the approximate Minimax polynomial.
    """

    # The degree of the polynomial is given by the size of the input array.
    deg = len(x_vals) - 1

    # Convert our list-of-lists to a matrix using mpmath.
    coeff_matrix = get_coeff_matrix(x_vals)

    # Convert the data vector, which is a list, to an actual vector.
    y_data = tmpld.mpmath.matrix(y_vals)

    # Solve the equation using LU decomposition and return as a list.
    return list(tmpld.mpmath.lu_solve(coeff_matrix, y_data))[0:deg + 1]
