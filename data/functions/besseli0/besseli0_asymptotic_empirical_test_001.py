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
#       Determine the degrees necessary for the bessel I0 asymptotic expansion #
#       to achieve double precision in certain windows.                        #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# Bessel I0 at double precision found here.
import scipy.special

# Coefficients for the I0 functions found here.
import besseli0

# Print which values of N achieved double precision.
for n in range(3, 10):
    x = 2**n
    for m in range(2, 18):
        y = scipy.special.iv(0, x)
        z = besseli0.asym_series(x, m)
        diff = (y - z)/y

        # If the expansion is accurate, print the result.
        if abs(diff) < 6.0E-16:
            print(m, x, float(diff))
            break
