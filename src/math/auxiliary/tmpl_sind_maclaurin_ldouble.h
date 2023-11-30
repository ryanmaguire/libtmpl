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
 *                         tmpl_sind_maclaurin_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of sine in degrees.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Sind_Maclaurin                                           *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of sine in degrees for small values x.  *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sind_x (long double):                                                 *
 *          The Maclaurin series of sine in degrees.                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \         (-1)^n pi^{2n+1}                          *
 *          sind(x)   =   /        ------------------ * x^{2n}                *
 *                        -----    (2n+1)! 180^{2n+1}                         *
 *                        n = 0                                               *
 *                                                                            *
 *      Use the first few terms and compute.                                  *
 *  Notes:                                                                    *
 *      Only accurate for values near 0.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 25, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SIND_MACLAURIN_LDOUBLE_H
#define TMPL_SIND_MACLAURIN_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double uses the same number of terms as double.               */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                          64 BIT DOUBLE PRECISION                           *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at long double precision.           */
#define A0 (+1.7453292519943295769236907684886127134429E-02L)
#define A1 (-8.8609615570129801598869213154725066307228E-07L)
#define A2 (+1.3496016231632550105929914052816816969112E-11L)
#define A3 (-9.7883848616177276095359680022041494717926E-17L)

/*  Maclaurin series for sine in degrees.                                     */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Sind_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0 + x2*(A1 + x2*(A2 + x2*A3)));
}
/*  End of tmpl_LDouble_Sind_Maclaurin.                                       */

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
#define A0 (+1.7453292519943295769236907684886127134429E-02L)
#define A1 (-8.8609615570129801598869213154725066307228E-07L)
#define A2 (+1.3496016231632550105929914052816816969112E-11L)
#define A3 (-9.78838486161772760953596800220414947179257E-17L)
#define A4 (+4.14126741725732068529449587689393809274778E-22L)
#define A5 (-1.14682017753790161396412139175844787354022E-27L)
#define A6 (+2.23936797077519653778917540987515319909871E-33L)

/*  Maclaurin series for sine in degrees.                                     */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Sind_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*(A4 + x2*(A5 + x2*A6))))));
}
/*  End of tmpl_LDouble_Sind_Maclaurin.                                       */

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
#define A0 (+1.7453292519943295769236907684886127134429E-02L)
#define A1 (-8.8609615570129801598869213154725066307228E-07L)
#define A2 (+1.3496016231632550105929914052816816969112E-11L)
#define A3 (-9.7883848616177276095359680022041494717926E-17L)
#define A4 (+4.1412674172573206852944958768939380927477E-22L)

/*  Maclaurin series for sine in degrees.                                     */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Sind_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*A4))));
}
/*  End of tmpl_LDouble_Sind_Maclaurin.                                       */

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
