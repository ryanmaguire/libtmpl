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
#       Converts a float or mpmath.mpf object to a string in scientific form.  #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   March 13, 2023.                                                    #
################################################################################
"""

# mpmath is imported here.
import tmpld

# Function for converting a float to a C string.
def float_to_c_string(val, number_of_decimals = 50):
    """
        Function:
            float_to_c_string
        Purpose:
            Converts a float or mpmath.mpf object to a string that is easy to
            copy / paste into C code.
        Arguments:
            val (float / mpmath.mpf):
                The input real number.
        Keywords:
            number_of_decimals (int):
                The number of decimals to print.
        Outputs:
            val_string (str):
                The input value as a string in scientific form.
    """

    # Convert to an mpf object, if necessary.
    val_mpf = tmpld.mpmath.mpf(val)

    # Convert the mpf object to a string.
    val_string = tmpld.mpmath.nstr(
        val_mpf, number_of_decimals, show_zero_exponent = True,
        strip_zeros = False, min_fixed = 0, max_fixed = 0
    ).replace("e", "E")

    # Make the exponent two decimals by adding a zero if necessary.
    if not val_string[-2:].isnumeric():
        val_string = val_string[:-1] + "0" + val_string[-1:]

    return val_string
