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
#       Provides a class for computing the coefficients of a rational          #
#       approximation for J0 near its zeros.                                   #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   October 5, 2023.                                                   #
################################################################################
"""
import tmpld.remez
import tmpld.pade
import tmpld.binary
import tmpld.poly

class GetCoeffs:
    """
        Class:
            GetCoeffs
        Purpose:
            Simple class for printing the coefficients of the approximation.
    """
    def __init__(self, index, xstart, xend, num_deg, den_deg):
        self.jzero = tmpld.mpmath.besseljzero(0, index)
        self.coeffs = [self.coefficient(k) for k in range(80)]
        (self.num_pade, self.den_pade) = tmpld.pade.mp_pade(self.coeffs, 30, 30)
        self.num_pade = self.num_pade[1:]

        start = xstart - self.jzero
        end = xend - self.jzero

        remez = tmpld.remez.rat_remez(self.shift, num_deg, den_deg, start, end)
        tmpld.remez.print_rat_coeffs(remez[0], remez[1])
        tmpld.poly.print_poly_helper(num_deg, label = "P")
        tmpld.poly.print_poly_helper(den_deg, label = "Q")
        self.print_zero()

    def coefficient(self, k_ind):
        """
            Function:
                coefficient
            Purpose:
                Computes the Taylor coefficient of J0 at j_{0, 2}
        """
        num = tmpld.mpmath.besselj(0, self.jzero, derivative = k_ind)
        den = tmpld.mpmath.factorial(k_ind)
        return num / den

    def pade_eval(self, x_in):
        """
            Function:
                pade_eval
            Purpose:
                Evaluates the Pade approximation for J0.
        """
        x_val = tmpld.mpmath.mpf(x_in) - self.jzero
        return tmpld.rat.rat_eval(self.num_pade, self.den_pade, x_val)

    def shift(self, x_in):
        """
            Function:
                shift
            Purpose:
                Compues a shifted J0 function.
        """
        x_val = tmpld.mpmath.mpf(x_in) + self.jzero
        return self.pade_eval(x_val)

    def print_zero(self):
        """
            Function:
                print_zero
            Purpose:
                Prints the zero value of J0 to double-double precision.
        """
        binary = tmpld.binary.float_to_binary(self.jzero)
        rounded_binary = tmpld.binary.round_up_binary(binary, 53)
        rounded_val = tmpld.binary.binary_to_float(rounded_binary)
        high = float(rounded_val)
        low = float(self.jzero - high)

        print("#define J0_HI (%.30E)\n#define J0_LO (%.30E)" % (high, low))
