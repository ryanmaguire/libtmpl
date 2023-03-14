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

# Function for finding local mins and maxes.
from tmpld.remez.get_peaks import get_peaks

# Resets the x and y samples to correspond to the new peak points.
def reset_samples(func, xarr, yarr):
    """
        Function:
            reset_samples
        Purpose:
            Resets x and y samples to corresponds to peaks in yarr as a function
            of xarr. That is, the peaks in |yarr| are found and the x-values are
            stored in x_vals. Then y_vals = func(x_vals) is computed.
        Arguments:
            func (function):
                The function being computed.
            xarr (list or array):
                The x-data.
            yarr (list or array):
                The y-data.
        Output:
            x_vals (list):
                The x-values of the peak points.
            y_vals (list):
                The function func evaluated at x_vals.
    """

    # Get the peaks of the error funcion |f(x) - P(x)|.
    maxarr = get_peaks(xarr, yarr)

    # Convert the points to mpmath objects.
    x_vals = [tmpld.mpmath.mpf(k) for k in maxarr]

    # Evaluate the function at these new points and return.
    y_vals = [func(k) for k in x_vals]

    return x_vals, y_vals
