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
#       Convert a float to a macro for use in C code.                          #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   March 14, 2023.                                                    #
################################################################################
"""

# Functions for manipulating strings.
from tmpld.string.get_c_ext import get_c_ext
from tmpld.string.float_to_c_string import float_to_c_string

# Convert a float to a C macro.
def get_c_macro(x_val, ind, ctype = "double", label = "A"):
    """
        Function:
            get_c_macro
        Purpose:
            Converts a float to a C macro to be copy / pasted into C code.
        Arguments:
            x_val (float / mpmath.mpf):
                A real number.
            ind (int):
                The index of this number with regards to some list of numbers.
        Keywords:
            ctype (str):
                The type of the C literal.
            label (str):
                The label for the macro in the C code.
        Outputs:
            c_macro (str):
                The input float as a C macro.
    """

    # Extension for literal constants, depends on data type.
    ext = get_c_ext(ctype)

    # Convert the mpmath object to a string.
    x_string = float_to_c_string(x_val)

    # Add plus sign if the coefficient is positive.
    if x_val >= 0:
        c_macro = "#define %s%02d (+%s%s)" % (label, ind, x_string, ext)
    else:
        c_macro = "#define %s%02d (%s%s)" % (label, ind, x_string, ext)

    return c_macro
