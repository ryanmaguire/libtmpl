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
#       Computes the exponents of a binary number represented as a string.     #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   March 13, 2023.                                                    #
################################################################################
"""

# Function for removing + and - from a binary string.
from tmpld.binary.sanitize_binary import sanitize_binary

# Computes the exponent of a binary string.
def get_binary_expo(in_str):
    """
        Function:
            get_binary_expo
        Purpose:
            Computes the exponent of a number represented as a binary string.
        Arguments:
            in_str (str):
                The binary number represented as a string.
        Outputs:
            expo (int):
                The exponent of the input.
    """

    # Remove any plus or minus signs from the string if they exist.
    abs_in_str = sanitize_binary(in_str)

    # Initialize the exponent to zero.
    expo = 0

    # Compute the exponent by shifting to the right until we get a ".".
    while abs_in_str[expo] != ".":
        expo = expo + 1

    # The exponent can now be computed by subtracting one from the above value.
    return expo - 1
