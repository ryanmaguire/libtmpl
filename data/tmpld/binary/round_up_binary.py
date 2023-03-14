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
#       Rounds a binary number to a given bit.                                 #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 10, 2023.                                                  #
################################################################################
"""

# Function to remove + and - from a string.
from tmpld.binary.sanitize_binary import sanitize_binary

# Computes the exponents of a binary number.
from tmpld.binary.get_binary_expo import get_binary_expo

# Rounds up a binary number in the corresponding place.
def round_up_binary(val, bit_place):
    """
        Function:
            round_up_binary
        Purpose:
            Rounds a value up in the "bit_place"th bit in binary.
        Arguments:
            val (str):
                The binary number to be rounded as a string.
            bit_place (int):
                The bit that will be rounded.
        Outputs:
            rounded_val (str):
                The input rounded up at bit_place.
    """

    # Remove any plus or minus signs at the start.
    val_str = sanitize_binary(val)

    # Compute the exponent of the input.
    expo = get_binary_expo(val_str)

    # The index of the bit is the exponent plus the bit-place plus one, the one
    # is for the "bit-point".
    ind = expo + bit_place + 1

    # If the input string doesn't have this bit, it is already rounded.
    if len(val_str) <= ind:

        # Add a minus sign if the input was negative.
        if val[0] == "-":
            return "-" + val_str

        # Otherwise return the already rounded input.
        return "+" + val_str

    # Otherwise, the rounded string is the first "ind" bits, plus the round.
    rounded_string = val_str[0:ind]

    # Check if we round up to "1" or down to "0".
    if val_str[ind+1] == "1" or val_str[ind] == "1":
        rounded_string += "1"
    else:
        rounded_string += "0"

    # If the input was negative, prepend a minus sign.
    if val[0] == "-":
        rounded_string = "-" + rounded_string

    return "+" + rounded_string
