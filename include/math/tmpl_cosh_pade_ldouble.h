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
 *                          tmpl_cosh_pade_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (8, 8) Pade approximant of cosh(x).                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Cosh_Pade                                                *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of order (8, 8) for cosh.               *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cosh_x (long double):                                                 *
 *          The Pade approximation of cosh(x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *                     a0 + a1*x^2 + a2*x^4 + a3*x^6 + a4*x^8                 *
 *          cbrt(x) ~= --------------------------------------                 *
 *                     b0 + b1*x^2 + b2*x^4 + b3*x^6 + b4*x^8                 *
 *                                                                            *
 *          -------------------------------------------------------------     *
 *          |  n  |          an               |         bn              |     *
 *          ------------------------------------------------------------|     *
 *          |  0  |          1                |         1               |     *
 *          |  2  |   260735 / 545628         |  -12079 / 545628        |     *
 *          |  4  |  4375409 / 141863280      |   34709 / 141863280     |     *
 *          |  6  |  7696415 / 13108167072    | -109247 / 65540835360   |     *
 *          |  8  | 80737373 / 23594700729600 |   11321 / 1814976979200 |     *
 *          -------------------------------------------------------------     *
 *                                                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 21, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COSH_PADE_LDOUBLE_H
#define TMPL_COSH_PADE_LDOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline support is requested.                    */
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator.                                           */
#define P0 (1.000000000000000000000000000000000000000E+00L)
#define P2 (4.778622064850044352562551775202152382209E-01L)
#define P4 (3.084243505437065884843491564554266615011E-02L)
#define P6 (5.871465444196315779152437095211293016391E-04L)
#define P8 (3.421843486182193140047209119910667485205E-06L)

/*  Coefficients for the denominator.                                         */
#define Q0 (1.000000000000000000000000000000000000000E+00L)
#define Q2 (-2.213779351499556474374482247978476177909E-02L)
#define Q4 (2.446651452017745536406602187683803729901E-04L)
#define Q6 (-1.666853945329390137941018760918032949527E-6L)
#define Q8 (6.237544679486808556431083134258191256732E-9L)

/*  Function for computing the (8, 8) Pade approximant of Cosh.               */
TMPL_INLINE_DECL
long double tmpl_LDouble_Cosh_Pade(long double x)
{
    /*  All non-zero powers of the numerator and denominator are even.        */
    const long double x2 = x*x;

    /*  Compute the numerator (p) and the denominator (q).                    */
    const long double p = P0 + x2*(P2 + x2*(P4 + x2*(P6 + x2*P8)));
    const long double q = Q0 + x2*(Q2 + x2*(Q4 + x2*(Q6 + x2*Q8)));

    /*  Return the quotient.                                                  */
    return p / q;
}
/*  End of tmpl_LDouble_Cosh_Pade.                                            */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P0
#undef P2
#undef P4
#undef P6
#undef P8
#undef Q0
#undef Q2
#undef Q4
#undef Q6
#undef Q8

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
