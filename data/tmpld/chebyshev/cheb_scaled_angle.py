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
#       Computes the scaled Chebyshev angles theta_n.                          #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# mpmath imported here.
import tmpld

# Chebyshev angle function found here.
from tmpld.chebyshev.cheb_angle import cheb_angle

# Function for computing the theta variables of the Chebyshev polynomials.
def cheb_scaled_angle(deg, ind, order):
    """
        Function:
            cheb_angle
        Purpose:
            Computes the theta values for the Chebyshev polynomials.
        Arguments:
            deg (int):
                The degree of the Chebyshev polynomial, T_n.
            ind (int):
                The index, an integer between 0 and order.
            order (int):
                The order of the approximation.
        Outputs:
            angle (mpmath.mpf):
                The scaled Chebyshev angle corresponding to ind and order.
    """

    # Scale the Chebyshev angle by "deg" and return.
    return tmpld.mpmath.mpf(deg) * cheb_angle(ind, order)
