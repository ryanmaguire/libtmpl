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
#       Compute the Remez coefficient for exp(x) on [-1/128, 1/128].           #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# Remez routines found here.
import remez

# Muli-precision math routines found here.
import mpmath

# The highest precision of long double is 112-bit mantissa. 224 bits is safe
# enough for all precisions used by libtmpl long double functions.
mpmath.mp.dps = 224

start = -mpmath.mpf(1) / mpmath.mpf(128)
end = mpmath.mpf(1) / mpmath.mpf(128)
deg = 5
c = remez.remez(mpmath.exp, deg, start, end)
remez.print_coeffs(c)
