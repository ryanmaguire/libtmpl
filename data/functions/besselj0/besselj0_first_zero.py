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
#       Gives the coefficients for a rational approximation near j_{0, 1}.     #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   October 5, 2023.                                                   #
################################################################################
"""
from besselj0_get_coeffs import GetCoeffs

if __name__ == "__main__":
    INDEX = 1
    START = 2.0
    END = 4.0
    NUM_DEG = 7
    DEN_DEG = 6
    GetCoeffs(INDEX, START, END, NUM_DEG, DEN_DEG)
