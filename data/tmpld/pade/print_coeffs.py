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
#       Routines for computing Pade approximants.                              #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   January 8, 2023.                                                   #
################################################################################
"""

# Converts fractions to mpf objects.
from tmpld.math.fraction_to_mpf import fraction_to_mpf

# Function for manipulating strings.
from tmpld.string.get_c_macro import get_c_macro

# Print the coefficients for the (P, Q) Pade approximant in a manner that is
# easy to copy / paste into C code.
def print_coeffs(num_coeffs, den_coeffs, ctype = "double"):
    """
        Function:
            print_coeffs
        Purpose:
            Prints the coefficients of a Pade approximant.
        Arguments:
            num_coeffs (list):
                The coefficients of the numerator polynomial.
            den_coeffs (list):
                The coefficients of the denominator polynomial.
        Keywords:
            ctype (str):
                "double", "float", or "ldouble". The type of the float.
        Output:
            None.
    """

    # Index for keeping track of the coefficients.
    ind = 0

    # Comment describing what these numbers are.
    print("/*  Coefficients for the numerator of the Pade approximant."
          "                   */")

    # Loop through the numerator coefficients.
    for coeff in num_coeffs:

        # Convert the fraction to an mpf.
        x_val = fraction_to_mpf(coeff)

        # Convert and print the current value.
        print(get_c_macro(x_val, ind, ctype = ctype, label = "P"))

        ind += 1

    # Comment describing what these numbers are.
    print("\n/*  Coefficients for the denominator of the Pade approximant."
          "                 */")

    # Reset the index to zero for the denominator.
    ind = 0

    # Loop through the denominator coefficients.
    for coeff in den_coeffs:

        # Convert the fraction to an mpf.
        x_val = fraction_to_mpf(coeff)

        # Convert and print the current value.
        print(get_c_macro(x_val, ind, ctype = ctype, label = "Q"))

        ind += 1
