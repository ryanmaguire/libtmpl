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
#       Routines for computing numerical derivatives using five-point stencils.#
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 10, 2023.                                                  #
################################################################################
"""

# mpmath constants.
import tmpld.constants

# Computes the numerical second derivative of f at x using a five-point stencil.
def second_derivative(func, x_val, step):
    """
        Function:
            second_derivative
        Purpose:
            Computes the second derivative of func using a five-point stencil.
        Arguments:
            func (function):
                The function being differentiated.
            x_val (float / mpmath.mpf):
                A real number.
            step (float / mpmath.mpf):
                The step size.
        Outputs:
            d2func_x_val (float / mpmath.mpf):
                The second derivative of func evaluated at x_val.
    """

    # The end-points on the stencil.
    left = -func(x_val + tmpld.constants.two*step)
    right = -func(x_val - tmpld.constants.two*step)

    # The off-center points.
    mid_left = tmpld.constants.sixteen * func(x_val + step)
    mid_right = tmpld.constants.sixteen * func(x_val - step)

    # The center of the stencil.
    mid = -tmpld.constants.thirty * func(x_val)

    # Sum of the stencil points.
    stencil_sum = left + mid_left + mid + mid_right + right

    # Divide by the weight and return.
    return stencil_sum / (tmpld.constants.twelve * step * step)
