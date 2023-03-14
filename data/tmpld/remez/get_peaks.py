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

# argrelextrema found here.
import scipy.signal

# Computes the peaks of |yarr| and returns the xarr values.
def get_peaks(xarr, yarr):
    """
        Function:
            get_peaks
        Purpose:
            Given x-data xarr and y-data yarr, with len(xarr) = len(yarr),
            compute the points xarr[n] such that xarr[n] corresponds to a peak
            of the absolute value |yarr[n]|.
        Arguments:
            xarr (list or array):
                The points in the x-axis the data corresponds to.
            yarr (list or array):
                The y-data.
        Output:
            peaks (numpy.array):
                The x-values corresponding to the peaks of |yarr|.
    """

    # scipy has a built-in function that is easy to use.
    maxind = list(scipy.signal.argrelextrema(yarr, numpy.greater_equal)[0])

    # The first and last elements of the interval should be added. Check.
    if len(xarr) - 1 not in maxind:
        maxind.append(len(xarr)-1)

    if 0 not in maxind:
        maxind = [0] + maxind

    # Convert back to a numpy array to be returned.
    maxind = numpy.array(maxind)

    # Return the points corresponding to peaks as an array.
    return xarr[maxind]
