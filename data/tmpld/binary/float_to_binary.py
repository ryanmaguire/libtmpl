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
#       Converts a float or mpmath.mpf to a binary string.                     #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 10, 2023.                                                  #
################################################################################
"""

# mpmath is imported here.
import tmpld

# Some mpmath constants (in mpf form) are found here.
import tmpld.constants

# Converts a float to a binary string.
def float_to_binary(val):
    """
        Function:
            float_to_binary
        Purpose:
            Converts a float to a binary string.
        Arguments:
            val (float / mpmath.mpf):
                A real number.
        Outputs:
            val_str (str):
                The float in binary as a string.
    """

    # Convert the input to an mpmath.mpf object, if necessary.
    val_mpf = tmpld.mpmath.fabs(val)

    # Get the integer part of the string, in binary, by converting to an "int"
    # with "int(val)". Get this in binary with "bin(int(val))", and remove the
    # "0b" that a binary value starts with via bin(int(val))[2:]. Append a
    # "bit-point" at the end of this string.
    val_str = bin(int(val_mpf))[2:] + "."

    # Get the fractional part of the input.
    val_frac = val_mpf - tmpld.mpmath.mpf(int(val_mpf))

    # Compute the binary representation bit-by-bit.
    for ind in range(1, tmpld.mpmath.mp.prec):

        # If the number has been reduced to zero, we're done.
        if val_frac == tmpld.constants.zero:
            break

        # Get the current power of two.
        power = tmpld.constants.two**tmpld.mpmath.mpf(-ind)

        # If power is smaller than the fractional part, this bit contributes
        # to the number. Set it to 1.
        if power <= val_frac:
            val_str += "1"

            # Subtract off this power so we can check the next bit after.
            val_frac = val_frac - power

        # Otherwise this bit does not contribute. Set it to zero.
        else:
            val_str += "0"

    # If the input is negative, add a minus sign.
    if val < 0:
        val_str = "-" + val_str
    else:
        val_str = "+" + val_str

    return val_str
