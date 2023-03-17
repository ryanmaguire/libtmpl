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

# mpmath constants.
import tmpld.constants

# Function for computing the rational coefficient matrix.
from tmpld.remez.get_rat_coeff_matrix import get_rat_coeff_matrix

# Given (x_vals, y_vals) data, inverts the rational Remez matrix and solves.
def perform_rational_remez_exchange(x_vals, y_vals, num_deg, den_deg):
    """
        Function:
            perform_rational_remez_exchange
        Purpose:
            Given data (x_vals, y_vals), inverts the Remez coefficient matrix
            for the rational approximation P(x)/Q(x) by linearizing and
            iteratively imporiving the linear approximation for the error
            term.
        Arguments:
            x_vals (list or array):
                The x-value data.
            y_vals (list or array):
                The values func(x_vals) where func is the function being
                approximated by the Minimax rational function.
            num_deg (int):
                The degree of the numerator P(x).
            den_deg (int):
                The degree of the denominator Q(x).
        Outputs:
            coeffs (list):
                The coefficients of the approximate Minimax rational function.
    """

    # The rational approximation does not yield a linear system of equations
    # for the coefficients. We linearize by using an initial guess of E = E0 = 0
    # and then iteratively improve this until the E value stablizes.
    error_guess = tmpld.constants.zero

    # Variable for keeping track of the number of iterations performed.
    iters = 0

    # Iteratively improve the guess for E0.
    while iters < 100:

        # We have n+2 equations with n+2 unknowns (the n+1 coefficients, and
        # the error estimate). Solve this using matrices.
        coeff_matrix = get_rat_coeff_matrix(
            x_vals, y_vals, num_deg, den_deg, error_guess
        )

        # Convert the y data to a vector.
        y_vec = tmpld.mpmath.matrix(y_vals)

        # Invert and solve using LU Decomposition.
        data = list(tmpld.mpmath.lu_solve(coeff_matrix, y_vec))

        # Avoid division by zero.
        if data[-1] == 0:
            iters += 1
            continue

        # Compute the relative difference and check if it is small enough.
        rel_increment_diff = tmpld.mpmath.fabs((error_guess-data[-1])/data[-1])

        # If the error has stabilized, we're done.
        if rel_increment_diff < tmpld.mpmath.mpf(1.0E-6):
            return data

        # Update the error guess.
        error_guess = data[-1]
        iters += 1

    return data
