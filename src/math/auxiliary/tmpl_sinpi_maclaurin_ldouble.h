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
 *                         tmpl_sinpi_maclaurin_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of normalized sine.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_SinPi_Maclaurin                                          *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of normalized sine small values x.      *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sinpi_x (long double):                                                *
 *          The Maclaurin series of normalized sine.                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \         (-1)^n pi^{2n+1}                          *
 *          sin(pi x) =   /        ------------------ * x^{2n+1}              *
 *                        -----          (2n+1)!                              *
 *                        n = 0                                               *
 *                                                                            *
 *      Use the first few terms and compute.                                  *
 *  Notes:                                                                    *
 *      Only accurate for values near 0.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 25, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SINPI_MACLAURIN_LDOUBLE_H
#define TMPL_SINPI_MACLAURIN_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double uses the same number of terms as double.               */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                          64 BIT DOUBLE PRECISION                           *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at long double precision.           */
#define A0 (+3.141592653589793238462643383279502884197E+00L)
#define A1 (-5.167712780049970029246052511183565867038E+00L)
#define A2 (+2.550164039877345443856177583695296720669E+00L)
#define A3 (-5.992645293207920768877393835460400460154E-01L)

/*  Maclaurin series for sine in degrees.                                     */
TMPL_STATIC_INLINE
long double tmpl_LDouble_SinPi_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0 + x2*(A1 + x2*(A2 + x2*A3)));
}
/*  End of tmpl_LDouble_SinPi_Maclaurin.                                      */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3

/*  128-bit quadruple and double-double, a few more terms.                    */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN    || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *                        128 BIT QUADRUPLE PRECISION                         *
 *                                    and                                     *
 *                      128 BIT DOUBLE-DOUBLE PRECISION                       *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at long double precision.           */
#define A0 (+3.141592653589793238462643383279502884197E+00L)
#define A1 (-5.167712780049970029246052511183565867038E+00L)
#define A2 (+2.550164039877345443856177583695296720669E+00L)
#define A3 (-5.992645293207920768877393835460400460154E-01L)
#define A4 (+8.214588661112822879880236552369834480784E-02L)
#define A5 (-7.370430945714350777259089957290781501212E-03L)
#define A6 (+4.663028057676125644206289144702717438282E-04L)

/*  Maclaurin series for sine in degrees.                                     */
TMPL_STATIC_INLINE
long double tmpl_LDouble_SinPi_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*(A4 + x2*(A5 + x2*A6))))));
}
/*  End of tmpl_LDouble_SinPi_Maclaurin.                                      */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6

#else
/*  End of 128-quadruple / 128-bit double-double version.                     */

/******************************************************************************
 *                         80 BIT EXTENDED PRECISION                          *
 *                                    and                                     *
 *                                  PORTABLE                                  *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at long double precision.           */
#define A0 (+3.141592653589793238462643383279502884197E+00L)
#define A1 (-5.167712780049970029246052511183565867038E+00L)
#define A2 (+2.550164039877345443856177583695296720669E+00L)
#define A3 (-5.992645293207920768877393835460400460154E-01L)
#define A4 (+8.214588661112822879880236552369834480784E-02L)

/*  Maclaurin series for sine in degrees.                                     */
TMPL_STATIC_INLINE
long double tmpl_LDouble_SinPi_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*A4))));
}
/*  End of tmpl_LDouble_SinPi_Maclaurin.                                      */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4

#endif
/*  End of portable version.                                                  */

#endif
/*  End of include guard.                                                     */
