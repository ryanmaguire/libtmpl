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
#       Basic implementation of Chebyshev polynomials.                         #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# String converting tool found here.
from tmpld.string.get_c_macro import get_c_macro

# Print the coefficients for the Chebyshev expansion.
def print_coeffs(coeffs, ctype = "double"):
    """
        Function:
            print_coeffs
        Purpose:
            Prints the coefficients of a Chebyshev expansion.
        Arguments:
            coeffs (list):
                The coefficients of the Chebyshev expansion.
        Keywords:
            ctype (str):
                The type of the C literals.
        Outputs:
            None
    """

    # Index for keeping track of which coefficient we're printing.
    ind = 0

    # Print a comment describing what these numbers are.
    print("/*  Coefficients for the Chebyshev approximation." + (29*" ") + "*/")

    # Loop over the coefficients in the list.
    for coeff in coeffs:

        # Convert and print the current value.
        print(get_c_macro(coeff, ind, ctype = ctype, label = "C"))

        # Increment the index to the next element.
        index += 1
