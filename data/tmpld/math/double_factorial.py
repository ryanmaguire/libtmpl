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
#       Computes the double factorial, n!!.                                    #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   March 13, 2023.                                                    #
################################################################################
"""

# Function for computing the double factorial, n!! = n*(n-2)*...
def double_factorial(value):
    """
        Function:
            double_factorial
        Purpose:
            Computes the double factorial of the input, n!!.
        Arguments:
            value (int):
                An integer.
        Output:
            double_fact (int):
                The double factorial of the input.
    """

    # Copy the input into a new variable.
    index = value

    if index <= 0:
        return 1

    # Initialize the output to one, compute the double factorial iteratively.
    double_fact = 1

    # Increment two at a time while the index is positive.
    while index > 0:
        double_fact = index*double_fact
        index = index - 2

    return double_fact
