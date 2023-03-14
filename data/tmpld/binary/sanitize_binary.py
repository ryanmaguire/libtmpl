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
#       Removes plus and minus signs from a string that represents a number.   #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   March 13, 2023.                                                    #
################################################################################
"""

# Remove + and - from the start of a string.
def sanitize_binary(val):
    """
        Function:
            sanitize_binary
        Purpose:
            Removes plus and minus signs from the string, if they exist.
        Arguments:
            val (str):
                A string that contains numerical characters, except possibly
                a decimal point '.' and a plus / minus sign at the start.
        Outputs:
            sanitized_val (str):
                The input with the plus / minus sign removed.
    """

    # Initialize the output by copying the input.
    sanitized_val = val

    # Remove any plus or minus signs at the start.
    while sanitized_val[0] == "-" or sanitized_val[0] == "+":

        # Avoid going beyond the bounds of the string.
        if len(sanitized_val) == 0:
            break

        # Remove the first character from the string.
        sanitized_val = sanitized_val[1:]

    return sanitized_val
