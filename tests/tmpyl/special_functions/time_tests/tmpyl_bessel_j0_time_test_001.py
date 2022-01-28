"""
################################################################################
#                                  LICENSE                                     #
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
#   Author:     Ryan Maguire                                                   #
#   Date:       January 28, 2022.                                              #
################################################################################
"""

import timeit, numpy, tmpyl, scipy.special

ARR = numpy.arange(-10.0, 10.0, 0.001)
FUNC0 = tmpyl.besselJ0
FUNC1 = scipy.special.j0
N = 1E4

timeit.timeit(
    setup = "from __main__ import FUNC0, ARR",
    stmt = "y = FUNC0(ARR)",
    number = N
)

timeit.timeit(
    setup = "from __main__ import FUNC1, ARR",
    stmt = "y = FUNC1(ARR)",
    number = N
)

