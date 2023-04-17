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
#       Computes the rising factorial of 1/2.                                  #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   April 17, 2023.                                                    #
################################################################################
"""

# Output is a fraction.
import fractions

# Double factorial needed.
from . import double_factorial

# Function for computing the double factorial, n!! = n*(n-2)*...
def half_rising_factorial(value):
    """
        Function:
            half_rising_factorial
        Purpose:
            Computes the rising factorial (1/2) ^ (value)
        Arguments:
            value (int):
                An integer.
        Output:
            rising_fact (int):
                The rising factorial of (1/2) 'value' times.
    """
    # The numerator is given by the double factorial.
    num = double_factorial(2*value - 1)

    # The denominator is a power of two.
    den = 2 ** value

    return fractions.Fraction(num, den)
