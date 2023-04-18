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

# Plotting routines.
import matplotlib.pyplot as plt

# mpmath imported here.
import tmpld

# Function for updating points in the exchange algorithm.
def select_points(func, x_vals, y_vals, xarr, yarr, deg):
    """
        Function:
            select_points
        Purpose:
            Allows the user to interactively choose points for the exchange.
        Arguments:
            func (function):
                The function being approximated.
            xarr (array):
                The independent variable.
            yarr (array):
                The error array in the polynomial and the function.
            deg (int):
                The degree of the approximation.
        Outputs:
            None.
    """

    plt.show()
    plt.ion()
    plt.plot(xarr, yarr)

    for _ in range(deg + 2 - len(x_vals)):
        x_vals.append(tmpld.mpmath.mpf(float(input("Select Point: "))))
        y_vals.append(func(x_vals[-1]))

    plt.close()
