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
#       Computes the cosine of the Chebyshev angles theta.                     #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# mpmath imported here.
import tmpld

# Chebyshev angle function found here.
from tmpld.chebyshev.cheb_angle import cheb_angle

# Function for computing the cosine of theta for the Chebyshev polynomials.
def cheb_cos(ind, order):
    """
        Function:
            cheb_cos
        Purpose:
            Computes the cosine of theta values for the Chebyshev polynomials.
        Arguments:
            ind (int):
                The index, an integer between 0 and order.
            order (int):
                The order of the approximation.
        Outputs:
            cos_angle (mpmath.mpf):
                The cosine of the Chebyshev angle for ind and order.
    """

    # Use the cheb_angle function and return the cosine of this.
    return tmpld.mpmath.cos(cheb_angle(ind, order))
