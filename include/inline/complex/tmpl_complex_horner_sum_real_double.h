
/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_HORNER_SUM_REAL_DOUBLE_H
#define TMPL_COMPLEX_HORNER_SUM_REAL_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  Function for applying the Horner iterate for polynomial evaluation.       */
TMPL_INLINE_DECL
void
tmpl_CDouble_Horner_Sum_Real(tmpl_ComplexDouble * const self,
                             const tmpl_ComplexDouble arg,
                             const double coeff)
{
    /*  Save the real part of the input to avoid overwriting.                 */
    const double x = self->dat[0];

    /*  Horner's method iteratively applies:                                  *
     *                                                                        *
     *      w    = z * w  + c                                                 *
     *       n+1        n    n+1                                              *
     *                                                                        *
     *  where z is the argument and c_n is the coefficient of the degree d-n  *
     *  term, where d is the degree of the polynomial. For complex numbers    *
     *  with real coefficients, this becomes:                                 *
     *                                                                        *
     *      w    = z * w  + c                                                 *
     *       n+1        n    n                                                *
     *                                                                        *
     *           = (a + bi) (x  + iy ) + c                                    *
     *                        n     n     n                                   *
     *                                                                        *
     *           = (ax  - by  + c ) + i (ay  + bx )                           *
     *                n     n    n         n     n                            *
     *                                                                        *
     *  where x_n and y_n are the real and imaginary parts of w_n,            *
     *  respectively, and a and b are the real and imaginary parts of z,      *
     *  respectively.                                                         */
    self->dat[0] = x * arg.dat[0] - self->dat[1] * arg.dat[1] + coeff;
    self->dat[1] = x * arg.dat[1] + self->dat[1] * arg.dat[0];
}

#endif
/*  End of include guard.                                                     */
