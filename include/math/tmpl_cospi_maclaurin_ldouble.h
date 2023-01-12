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
 *                         tmpl_cospi_maclaurin_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of normalized cosine, cos(pi x).        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_CosPi_Maclaurin                                          *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of normalized cosine for small values x.*
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cospi_x (long double):                                                *
 *          The Maclaurin series of normalized cosine, cos(pi x).             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \        (-1)^n pi^{2n}                             *
 *          cos(pi x) =   /        -------------- * x^{2n}                    *
 *                        -----         (2n)!                                 *
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
 *  Date:       November 8, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COSPI_MACLAURIN_LDOUBLE_H
#define TMPL_COSPI_MACLAURIN_LDOUBLE_H

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
#define A0 (1.000000000000000000000000000000000000000E+00L)
#define A1 (-4.934802200544679309417245499938075567657E+00L)
#define A2 (4.058712126416768218185013862029379635405E+00L)
#define A3 (-1.335262768854589495875304782850583192871E+00L)
#define A4 (2.353306303588932045418793527754654215451E-01L)

/*  Maclaurin series for cosine in degrees.                                   */
TMPL_INLINE_DECL
long double tmpl_LDouble_CosPi_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*A4)));
}
/*  End of tmpl_LDouble_CosPi_Maclaurin.                                      */

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
#define A0 (1.000000000000000000000000000000000000000E+00L)
#define A1 (-4.934802200544679309417245499938075567657E+00L)
#define A2 (4.058712126416768218185013862029379635405E+00L)
#define A3 (-1.335262768854589495875304782850583192871E+00L)
#define A4 (2.353306303588932045418793527754654215451E-01L)
#define A5 (-2.580689139001406001259829425289884965719E-02L)
#define A6 (1.929574309403923047903345563685957640168E-03L)
#define A7 (-1.046381049248457071180167283522393276103E-04L)

/*  Maclaurin series for cosine in degrees.                                   */
TMPL_INLINE_DECL
long double tmpl_LDouble_CosPi_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return A0+x2*(A1+x2*(A2+x2*(A3+x2*(A4+x2*(A5+x2*(A6+x2*A7))))));
}
/*  End of tmpl_LDouble_CosPi_Maclaurin.                                      */

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
#define A0 (1.000000000000000000000000000000000000000E+00L)
#define A1 (-4.934802200544679309417245499938075567657E+00L)
#define A2 (4.058712126416768218185013862029379635405E+00L)
#define A3 (-1.335262768854589495875304782850583192871E+00L)
#define A4 (2.353306303588932045418793527754654215451E-01L)
#define A5 (-2.580689139001406001259829425289884965719E-02L)

/*  Maclaurin series for cosine in degrees.                                   */
TMPL_INLINE_DECL
long double tmpl_LDouble_CosPi_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*(A4 + x2*A5))));
}
/*  End of tmpl_LDouble_CosPi_Maclaurin.                                      */

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
