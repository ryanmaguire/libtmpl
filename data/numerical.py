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

# Computes the numerical derivative of f at x using a five-point stencil.
def df(f, x, h):
    two = mpmath.mpf(2)
    eight = mpmath.mpf(8)
    twelve = mpmath.mpf(12)

    a = -f(x + two*h)
    b = eight * f(x + h)
    c = -eight * f(x - h)
    d = f(x - two*h)

    return (a + b + c + d) / (twelve * h)

# Computes the numerical second derivative of f at x using a five-point stencil.
def d2f(f, x, h):
    two = mpmath.mpf(2)
    twelve = mpmath.mpf(12)
    sixteen = mpmath.mpf(16)
    thirty = mpmath.mpf(30)

    a = -f(x + two*h)
    b = sixteen * f(x + h)
    c = -thirty * f(x)
    d = sixteen * f(x - h)
    e = -f(x - two*h)

    return (a + b + c + d + e) / (twelve * h * h)
