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

# Arrays.
import numpy

# mpmath is imported here.
import tmpld

# Computes the initial values of the exchange functions.
def start_exchange(func, deg, start, end):
    """
        Function:
            start_exchange
        Purpose:
            Creates the initial variables for the exchange functions.
        Arguments:
            f (function):
                The function to be approximated.
            deg (int):
                The degree of the output Minimax polynomial.
            start (float):
                The left-most point of the interval f is approximated on.
            end (float):
                The right-most point of the interval f is approximated on.
    """

    # Convert the inputs to mpmath objects if necessary.
    start = tmpld.mpmath.mpf(start)
    end = tmpld.mpmath.mpf(end)

    # Compute the distance between initial samples.
    dist = (end - start)/tmpld.mpmath.mpf(deg + 1)

    # Sample the interval [start, end] with a sufficient number of points so
    # that the peaks can be easily calculated. Compute the corresponding
    # y-vals farr = func(xarr).
    xarr = numpy.arange(float(start), float(end), float(dist)*1.0E-3)
    farr = [func(k) for k in xarr]

    x_vals = [start + m*dist for m in range(deg + 2)]
    y_vals = [func(m) for m in x_vals]

    return xarr, farr, x_vals, y_vals
