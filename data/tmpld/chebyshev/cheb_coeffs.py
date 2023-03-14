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
#       Computes the coefficients of the Chebyshev approximation.              #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# mpmath is imported here.
import tmpld

# mpmath constants found here.
import tmpld.constants

# Function for compute the Chebyshev angles.
from tmpld.chebyshev.cheb_cos import cheb_cos

# Scaled version of the previous function, angle is scaled by degree.
from tmpld.chebyshev.cheb_scaled_cos import cheb_scaled_cos

# Given a continuous and piecewise smooth function f on the interval [-1, 1],
# approximate the first "deg+1" Chebyshev polynomials. The higher the "order"
# factor, the better the approximation.
def cheb_coeffs(func, deg, order):
    """
        Function:
            cheb_coeffs
        Purpose:
            Computes the coefficients for the Chebyshev approximation of
            "func" of degree "deg" using an order "order" approximation.
            The higher the order, the closer the coefficients are to the
            actual Chebyshev coefficients for "func". This numerically solves
            the integral using the Chebyshev discrete orthogonality condition.
        Arguments:
            func (function):
                A continuous and piecewise smooth function on [-1, 1].
            deg (int):
                The degree of the approximation.
            order (int):
                The order of the approximation for the coefficients. The
                integral for the coefficients is solved numerical. The higher
                this value, the better the approximation.
        Outputs:
            coeffs (list):
                The coefficients for the Chebyshev approximation.
    """

    # Array for the zeros, or Chebyshev angles, and for the coefficients.
    x_arr = [0]*order
    coeffs = [tmpld.constants.zero]*(deg+1)

    # Precompute this division to turn it into multiplication.
    factor = tmpld.constants.two / tmpld.mpmath.mpf(order)

    # The zeroes of the Chebyshev polynomials are used to approximate the
    # coefficients. The zeros of the nth polynomial are given by:
    #   x_k = cos(pi (k + 1/2) / n)
    # Evaluate the given function f at these points.
    for ind in range(order):
        x_arr[ind] = func(cheb_cos(ind, order))

    # Using the discrete orthogonality condition of the Chebyshev polynomials,
    # one obtains the following approximation for the Chebyshev coefficients:
    #              N - 1
    #              -----
    #          2   \
    #   a_n = ---  /     cos(n pi (k + 1/2) / N) f(x_k)
    #          N   -----
    #              k = 0
    #
    # Where N is the "order" of the approximation, and x_k is the kth zero of
    # the Chebyshev polynomial computed above.
    for cheb_deg in range(deg+1):
        for ind in range(order):
            coeffs[cheb_deg] += x_arr[ind]*cheb_scaled_cos(cheb_deg, ind, order)

        coeffs[cheb_deg] = factor * coeffs[cheb_deg]

    return coeffs
