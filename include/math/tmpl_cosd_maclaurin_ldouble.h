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
 *                         tmpl_cosd_maclaurin_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of cosine in degrees.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Cosd_Maclaurin                                           *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of cosine in degrees for small values x.*
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cosd_x (long double):                                                 *
 *          The Maclaurin series of cosine in degrees.                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \        (-1)^n pi^{2n}                             *
 *          cosd(x)   =   /        -------------- * x^{2n}                    *
 *                        -----    (2n)! 180^{2n}                             *
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
#ifndef TMPL_COSD_MACLAURIN_LDOUBLE_H
#define TMPL_COSD_MACLAURIN_LDOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline support is requested.                    */
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  64-bit long double uses the same number of terms as double.               */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                          64 BIT DOUBLE PRECISION                           *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at long double precision.           */
#define A0 (1.0000000000000000000000000000000000000000E+00L)
#define A1 (-1.5230870989335429967337177468944677677953E-04L)
#define A2 (3.8663238515629936539637763508129283220977E-09L)
#define A3 (-3.9258319857430948822261807485761095565851E-14L)
#define A4 (2.1354943035949859694115057492512886240753E-19L)

/*  Maclaurin series for cosine in degrees.                                   */
TMPL_INLINE_DECL
long double tmpl_LDouble_Cosd_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*A4)));
}
/*  End of tmpl_LDouble_Cosd_Maclaurin.                                       */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4

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
#define A0 (1.0000000000000000000000000000000000000000E+00L)
#define A1 (-1.5230870989335429967337177468944677677953E-04L)
#define A2 (3.8663238515629936539637763508129283220977E-09L)
#define A3 (-3.9258319857430948822261807485761095565851E-14L)
#define A4 (2.1354943035949859694115057492512886240753E-19L)
#define A5 (-7.2278751636702086648611864463100576055221E-25L)
#define A6 (1.6679823355285250582920873136681179270141E-30L)
#define A7 (-2.7917388752665239068819570004398031465163E-36L)

/*  Maclaurin series for cosine in degrees.                                   */
TMPL_INLINE_DECL
long double tmpl_LDouble_Cosd_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return A0+x2*(A1+x2*(A2+x2*(A3+x2*(A4+x2*(A5+x2*(A6+x2*A7))))));
}
/*  End of tmpl_LDouble_Cosd_Maclaurin.                                       */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7

#else
/*  End of 128-quadruple / 128-bit double-double version.                     */

/******************************************************************************
 *                         80 BIT EXTENDED PRECISION                          *
 *                                    and                                     *
 *                                  PORTABLE                                  *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at long double precision.           */
#define A0 (1.0000000000000000000000000000000000000000E+00L)
#define A1 (-1.5230870989335429967337177468944677677953E-04L)
#define A2 (3.8663238515629936539637763508129283220977E-09L)
#define A3 (-3.9258319857430948822261807485761095565851E-14L)
#define A4 (2.1354943035949859694115057492512886240753E-19L)
#define A5 (-7.2278751636702086648611864463100576055221E-25L)

/*  Maclaurin series for cosine in degrees.                                   */
TMPL_INLINE_DECL
long double tmpl_LDouble_Cosd_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*(A4 + x2*A5))));
}
/*  End of tmpl_LDouble_Cosd_Maclaurin.                                       */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#endif
/*  End of portable version.                                                  */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
