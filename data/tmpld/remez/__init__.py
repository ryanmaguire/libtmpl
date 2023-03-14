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
#       Routines for computing Remez polynomials.                              #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   March 14, 2023.                                                    #
################################################################################
"""

from tmpld.remez.get_coeff_matrix import get_coeff_matrix
from tmpld.remez.get_rat_coeff_matrix import get_rat_coeff_matrix
from tmpld.remez.perform_rational_remez_exchange import \
     perform_rational_remez_exchange
from tmpld.remez.perform_remez_exchange import perform_remez_exchange
from tmpld.remez.print_coeffs import print_coeffs
from tmpld.remez.print_rat_coeffs import print_rat_coeffs
from tmpld.remez.rat_remez import rat_remez
from tmpld.remez.remez import remez
from tmpld.remez.reset_samples import reset_samples
from tmpld.remez.start_exchange import start_exchange
