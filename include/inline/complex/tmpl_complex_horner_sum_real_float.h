/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                     tmpl_complex_horner_sum_real_float                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs the Horner iterate, w = z * w + c, where c is real.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Horner_Sum_Real                                           *
 *  Purpose:                                                                  *
 *      Computes the iterate for Horner's method. Given a complex variable z, *
 *      and a real coefficient, this computes w = z * w + c. This is used for *
 *      evaluating polynomials with complex arguments.                        *
 *  Arguments:                                                                *
 *      self (tmpl_ComplexFloat * const):                                     *
 *          A pointer to a complex number. The result is stored here.         *
 *      arg (const tmpl_ComplexFloat * const):                                *
 *          The variable for the polynomial. This is z in w = z * w + c.      *
 *      coeff (const float):                                                  *
 *          The real coefficient. This is c in w = z * w + c.                 *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      A polynomial in a complex variable z is defined as a finite sum of    *
 *      powers of z. That is:                                                 *
 *                                                                            *
 *                   N                                                        *
 *                 -----                                                      *
 *                 \          n                                               *
 *          p(z) = /      c  z                                                *
 *                 -----   n                                                  *
 *                 n = 0                                                      *
 *                                                                            *
 *      where N is the degree of the polynomial, N = deg(p). In this function *
 *      we are using real coefficients, so c_n is real for each n. Horner's   *
 *      method allows us to evaluate this efficiently without explicitly      *
 *      computing powers of z. We set w_0 = c_N and then iteratively apply:   *
 *                                                                            *
 *          w    = z * w  + c                                                 *
 *           n+1        n    N-n-1                                            *
 *                                                                            *
 *      This helper function performs this iterate. Expanding w_n and z into  *
 *      real and imaginary parts gives us:                                    *
 *                                                                            *
 *          w    = (a + ib) (x  + iy ) + c                                    *
 *           n+1              n     n     N-n-1                               *
 *                                                                            *
 *                = (ax  - by  + c     ) + i (ay  + bx )                      *
 *                     n     n    N-n-1         n     n                       *
 *                                                                            *
 *      We compute by using this last expression, setting:                    *
 *                                                                            *
 *          real(self) = real(self) * real(z) - imag(self) * imag(z) + c      *
 *          imag(self) = real(self) * imag(z) + imag(self) * real(z)          *
 *                                                                            *
 *      Note that the expression for imag(self) uses real(self). To avoid     *
 *      using the incorrect value (since real(self) is overwritten), we make  *
 *      a copy of real(self) at the start of the function.                    *
 *  Error:                                                                    *
 *      Based on 134,217,728 random samples:                                  *
 *          Max Relative Error: 2.220446e-16                                  *
 *          RMS Relative Error: 3.751642e-17                                  *
 *      Values assume 100% accuracy of glibc. Actual error in glibc is        *
 *      less than 1 ULP (~2 x 10^-16).                                        *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers.                            *
 *      2.) There are no checks for NaN or Infinity.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          TMPL_INLINE_DECL macro found here.                                *
 *  2.) tmpl_complex_float.h:                                                 *
 *          Header providing single precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 17, 2025                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_HORNER_SUM_REAL_FLOAT_H
#define TMPL_COMPLEX_HORNER_SUM_REAL_FLOAT_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_float.h>

/*  Function for applying the Horner iterate for polynomial evaluation.       */
TMPL_INLINE_DECL
void
tmpl_CFloat_Horner_Sum_Real(tmpl_ComplexFloat * const self,
                            const tmpl_ComplexFloat * const arg,
                            const float coeff)
{
    /*  Save the real part of the input to avoid overwriting.                 */
    const float x = self->dat[0];

    /*  Horner's method iteratively applies:                                  *
     *                                                                        *
     *      w    = z * w  + c                                                 *
     *       n+1        n    N-n-1                                            *
     *                                                                        *
     *  where z is the argument and c_n is the coefficient of the degree n    *
     *  term. For complex numbers with real coefficients, this becomes:       *
     *                                                                        *
     *      w    = z * w  + c                                                 *
     *       n+1        n    N-n-1                                            *
     *                                                                        *
     *           = (a + bi) (x  + iy ) + c                                    *
     *                        n     n     N-n-1                               *
     *                                                                        *
     *           = (ax  - by  + c     ) + i (ay  + bx )                       *
     *                n     n    N-n-1         n     n                        *
     *                                                                        *
     *  where x_n and y_n are the real and imaginary parts of w_n,            *
     *  respectively, and a and b are the real and imaginary parts of z,      *
     *  respectively. Compute using this final expression.                    */
    self->dat[0] = x * arg->dat[0] - self->dat[1] * arg->dat[1] + coeff;
    self->dat[1] = x * arg->dat[1] + self->dat[1] * arg->dat[0];
}
/*  End of tmpl_CFloat_Horner_Sum_Real.                                       */

#endif
/*  End of include guard.                                                     */
