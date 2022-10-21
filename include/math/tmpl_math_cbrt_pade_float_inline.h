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
 *                           tmpl_cbrt_pade_float                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (7, 7) Pade approximant of cbrt(x) at single precision.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Cbrt_Pade                                                  *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of order (7, 7) for cbrt.               *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cbrt_x (float):                                                       *
 *          The Pade approximation of cbrt(x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *                     a0+a1*s^1+a2*s^2+a3*s^3+a4*s^4+a5*s^5+a6*s^6+a7*s^7    *
 *          cbrt(x) ~= --------------------------------------------------     *
 *                     b0+b1*s^1+b2*s^2+b3*s^3+b4*s^4+b5*s^5+b6*s^6+b7*s^7    *
 *                                                                            *
 *      Where s = x - 1.                                                      *
 *      Label the rational function as rat and return x*(rat + 1).            *
 *          ----------------------------------------------                    *
 *          |  n  |        an         |        bn        |                    *
 *          ----------------------------------------------                    *
 *          |  0  |         1         |        1         |                    *
 *          |  1  |      11 / 3       |     10 / 3       |                    *
 *          |  2  |     209 / 39      |    170 / 39      |                    *
 *          |  3  |    4180 / 1053    |   2975 / 1053    |                    *
 *          |  4  |     380 / 243     |   2975 / 3159    |                    *
 *          |  5  |      76 / 243     |    476 / 3159    |                    *
 *          |  6  |     532 / 19683   |   2380 / 255879  |                    *
 *          |  7  |      38 / 59049   |     85 / 767637  |                    *
 *          ----------------------------------------------                    *
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
#ifndef TMPL_MATH_CBRT_PADE_FLOAT_INLINE_H
#define TMPL_MATH_CBRT_PADE_FLOAT_INLINE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator.                                           */
#define P0 (1.000000000000000000000000000000000000000E+00F)
#define P1 (3.666666666666666666666666666666666666667E+00F)
#define P2 (5.358974358974358974358974358974358974359E+00F)
#define P3 (3.969610636277302943969610636277302943970E+00F)
#define P4 (1.563786008230452674897119341563786008230E+00F)
#define P5 (3.127572016460905349794238683127572016461E-01F)
#define P6 (2.702840014225473759081440837270741248793E-02F)
#define P7 (6.435333367203508950193906755406526782841E-04F)

/*  Coefficients for the denominator.                                         */
#define Q0 (1.000000000000000000000000000000000000000E+00F)
#define Q1 (3.333333333333333333333333333333333333333E+00F)
#define Q2 (4.358974358974358974358974358974358974359E+00F)
#define Q3 (2.825261158594491927825261158594491927825E+00F)
#define Q4 (9.417537195314973092750870528648306426084E-01F)
#define Q5 (1.506805951250395694840139284583729028173E-01F)
#define Q6 (9.301271304014788239753946201134129803540E-03F)
#define Q7 (1.107294202858903361875469785849301167088E-04F)

/*  Function for computing the (7, 7) Pade approximate of cbrt(x) at x = 1.   */
TMPL_INLINE_DECL
float tmpl_Float_Cbrt_Pade(float x)
{
    /*  The approximant is computed at x = 1. Shift the input.                */
    const float xs = x - 1.0F;

    /*  Use Horner's method to evaluate the numerator and denominator.        */
    const float p = P0+xs*(P1+xs*(P2+xs*(P3+xs*(P4+xs*(P5+xs*(P6+xs*P7))))));
    const float q = Q0+xs*(Q1+xs*(Q2+xs*(Q3+xs*(Q4+xs*(Q5+xs*(Q6+xs*Q7))))));

    /*  Return the fraction.                                                  */
    return p/q;
}
/*  End of tmpl_Float_Cbrt_Pade.                                              */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P0
#undef P1
#undef P2
#undef P3
#undef P4
#undef P5
#undef P6
#undef P7
#undef Q0
#undef Q1
#undef Q2
#undef Q3
#undef Q4
#undef Q5
#undef Q6
#undef Q7

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */

