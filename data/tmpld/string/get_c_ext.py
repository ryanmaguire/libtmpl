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
#       Gets the extension for a C literals (float, double, long double).      #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   March 13, 2023.                                                    #
################################################################################
"""

# Get the extension for a C literal constant.
def get_c_ext(ctype):
    """
        Function:
            get_c_ext
        Purpose:
            Gets the extension of a C literal constant.
        Arguments:
            ctype (str):
                The type of the C value (float, double, or long double).
        Outputs:
            ext (str):
                The extension for the literal.
    """

    # Extension for literal constants, depends on data type.
    if ctype == "ldouble":
        ext = "L"
    elif ctype == "float":
        ext = "F"
    else:
        ext = ""

    return ext
