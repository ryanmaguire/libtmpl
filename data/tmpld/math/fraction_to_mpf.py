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
#       Converts a fraction to an mpf.                                         #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   March 14, 2023.                                                    #
################################################################################
"""

# mpmath imported here.
import tmpld

# Converts a fraction to an mpf object.
def fraction_to_mpf(x_val):
    """
        Function:
            fraction_to_mpf
        Purpose:
            Converts a fraction to an mpmath.mpf object.
        Arguments:
            x_val (fraction.Fraction):
                A fraction.
        Outputs:
            x_val_as_mpf (mpmath.mpf):
                The input converted to an mpmath.mpf object.
    """
    num = tmpld.mpmath.mpf(x_val.numerator)
    den = tmpld.mpmath.mpf(x_val.denominator)

    return num / den
