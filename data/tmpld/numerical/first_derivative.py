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

# mpmath constants here.
import tmpld.constants

# Computes the numerical derivative of f at x using a five-point stencil.
def first_derivative(func, x_val, step):
    """
        Function:
            first_derivative
        Purpose:
            Computes the derivative of func using a five-point stencil.
        Arguments:
            func (function):
                The function being differentiated.
            x_val (float / mpmath.mpf):
                A real number.
            step (float / mpmath.mpf):
                The step size.
        Outputs:
            dfunc_x_val (float / mpmath.mpf):
                The derivative of func evaluated at x_val.
    """

    # The endpoints of the stencil.
    left = -func(x_val + tmpld.constants.two*step)
    right = func(x_val - tmpld.constants.two*step)

    # The centers of the stencil.
    mid_left = tmpld.constants.eight * func(x_val + step)
    mid_right = -tmpld.constants.eight * func(x_val - step)

    # Sum the points in the stencil.
    stencil_sum = left + mid_left + mid_right + right

    # Divide by the weight and return.
    return stencil_sum / (tmpld.constants.twelve * step)
