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
#       Computes the Chebyshev angles theta.                                   #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# mpmath imported here.
import tmpld

# Function for computing the theta variables of the Chebyshev polynomials.
def cheb_angle(ind, order):
    """
        Function:
            cheb_angle
        Purpose:
            Computes the theta values for the Chebyshev polynomials.
        Arguments:
            ind (int):
                The index, an integer between 0 and order.
            order (int):
                The order of the approximation.
        Outputs:
            angle (mpmath.mpf):
                The Chebyshev angle corresponding to ind and order.
    """

    # Compute the numerator and denominator and return.
    num = tmpld.mpmath.mpf(2*ind + 1)*tmpld.mpmath.pi
    den = tmpld.mpmath.mpf(2*order)
    return num / den
