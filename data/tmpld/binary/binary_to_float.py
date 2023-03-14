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
#       Routines for working with binary representations of floats.            #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 10, 2023.                                                  #
################################################################################
"""

# mpmath is imported here.
import tmpld

# Some mpmath constants (in mpf form) are found here.
import tmpld.constants

# Function from remove + and - from a string.
from tmpld.binary.sanitize_binary import sanitize_binary

# Computes the exponents of a binary number.
from tmpld.binary.get_binary_expo import get_binary_expo

# Converts a string in binary to a mpmath.mpf object.
def binary_to_float(in_str):
    """
        Function:
            binary_to_float
        Purpose:
            Converts a binary string to a floating point number.
        Arguments:
            in_str (string):
                The binary number, as a string.
        Outputs:
            in_as_float (mpmath.mpf):
                The binary number as an mpf object.
    """

    # Remove any plus or minus signs from the string if they exist.
    abs_in_str = sanitize_binary(in_str)

    # There should be decimal point in the number, subtract 1 to get the length.
    num_len = len(abs_in_str) - 1

    # Compute the exponent of the input.
    expo = get_binary_expo(abs_in_str)

    # Remove the decimal from the number.
    abs_in_str = abs_in_str.replace(".", "")

    # Initialize the output to zero. It is computed iteratively.
    in_as_float = tmpld.constants.zero

    # Convert the string to a float by looping over the bits and adding.
    for ind in range(num_len):
        power = tmpld.constants.two ** tmpld.mpmath.mpf(expo - ind)
        in_as_float += tmpld.mpmath.mpf(int(abs_in_str[ind]) * power)

    # If the number started with a minus sign, it is negative. Negate.
    if in_str[0] == "-":
        return -in_as_float

    # Otherwise it is non-negative, simply return the value.
    return in_as_float
