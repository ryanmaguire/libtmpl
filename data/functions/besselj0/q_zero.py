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
#       Computes the coefficients for the Remez approximation of Q_0(x).       #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   October 5, 2023.                                                   #
################################################################################
"""
import tmpld
import tmpld.remez
import hankel_expansion

def shifted_q_zero(x_in):
    x_val = tmpld.mpmath.mpf(x_in)
    y_val = tmpld.mpmath.mpf(32.0) / (x_val + tmpld.mpmath.mpf(1.0))

    return hankel_expansion.qzero(y_val)

start = -9.999999999999998889776975e-01
end = 1.0
remez = tmpld.remez.rat_remez(shifted_q_zero, 5, 4, start, end)

tmpld.remez.print_rat_coeffs(remez[0], remez[1])
