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
#   Date:   March 14, 2023.                                                    #
################################################################################
"""

from tmpld.pade.get_coeff_matrix import get_coeff_matrix
from tmpld.pade.get_data_vector import get_data_vector
from tmpld.pade.mp_get_coeff_matrix import mp_get_coeff_matrix
from tmpld.pade.mp_get_data_vector import mp_get_data_vector
from tmpld.pade.mp_pade import mp_pade
from tmpld.pade.mp_print_coeffs import mp_print_coeffs
from tmpld.pade.pade import pade
from tmpld.pade.print_coeffs import print_coeffs
