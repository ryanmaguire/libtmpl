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
#       Creates plots of computational time for functions.                     #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   April 17, 2023                                                     #
################################################################################
"""

import time
import numpy

# Creates benchmarking plots.
def get_time_array(func, start, end, increment, samples):
    """
        Function:
            get_time_array
        Purpose:
            Creates a computation time vs input plot for a given function.
        Arguments:
            func (function):
                The function being benchmarked.
            start (float):
                The starting point of the interval being tested.
            end (float):
                The ending point of the interval being tested.
            increment (float):
                The step size used to sample the interval.
            samples (int):
                The number of samples between x and x + increment.
        Outputs:
            None.
    """
    time_array = []
    start_val = start
    end_val = start + increment
    dx_val = (end_val - start_val) / float(samples)

    while start_val < end:
        x_array = numpy.arange(start_val, end_val, dx_val)
        time0 = time.time()
        _ = func(x_array)
        time1 = time.time()
        time_array.append(time1 - time0)

        start_val += increment
        end_val += increment

    return time_array
