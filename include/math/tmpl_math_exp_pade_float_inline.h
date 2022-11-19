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
 *                           tmpl_exp_pade_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (7, 7) Pade approximant of exp(x) at single precision.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Exp_Pade                                                   *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of order (7, 7) for exp.                *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      exp_x (float):                                                        *
 *          The Pade approximation of exp(x).                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *                     a0+a1*x^1+a2*x^2+a3*x^3+a4*x^4+a5*x^5+a6*x^6+a7*x^7    *
 *          exp(x) ~= ---------------------------------------------------     *
 *                     b0+b1*x^1+b2*x^2+b3*x^3+b4*x^4+b5*x^5+b6*x^6+b7*x^7    *
 *                                                                            *
 *          --------------------------------------------------                *
 *          |  n  |       an            |       bn           |                *
 *          -------------------------------------------------|                *
 *          |  0  |       1             |       1            |                *
 *          |  1  |     1 / 2           |    -1 / 2          |                *
 *          |  2  |     3 / 26          |     3 / 26         |                *
 *          |  3  |     5 / 312         |    -5 / 312        |                *
 *          |  4  |     5 / 3432        |    -5 / 3432       |                *
 *          |  5  |     1 / 11440       |    -1 / 11440      |                *
 *          |  6  |     1 / 308880      |     1 / 308880     |                *
 *          |  7  |     1 / 17297280    |    -1 / 17297280   |                *
 *          --------------------------------------------------                *
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
 *  Date:       November 9, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_EXP_PADE_FLOAT_INLINE_H
#define TMPL_MATH_EXP_PADE_FLOAT_INLINE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline support is requested.                    */
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator.                                           */
#define P0 (1.000000000000000000000000000000000000000E+00F)
#define P1 (5.000000000000000000000000000000000000000E-01F)
#define P2 (1.153846153846153846153846153846153846154E-01F)
#define P3 (1.602564102564102564102564102564102564103E-02F)
#define P4 (1.456876456876456876456876456876456876457E-03F)
#define P5 (8.741258741258741258741258741258741258741E-05F)
#define P6 (3.237503237503237503237503237503237503238E-06F)
#define P7 (5.781255781255781255781255781255781255781E-08F)

/*  Coefficients for the denominator.                                         */
#define Q0 (1.000000000000000000000000000000000000000E+00F)
#define Q1 (-5.000000000000000000000000000000000000000E-01F)
#define Q2 (1.153846153846153846153846153846153846154E-01F)
#define Q3 (-1.602564102564102564102564102564102564103E-02F)
#define Q4 (1.456876456876456876456876456876456876457E-03F)
#define Q5 (-8.741258741258741258741258741258741258741E-05F)
#define Q6 (3.237503237503237503237503237503237503238E-06F)
#define Q7 (-5.781255781255781255781255781255781255781E-08F)

/*  Function for computing the (7, 7) Pade approximant of Exp.                */
TMPL_INLINE_DECL
float tmpl_Float_Exp_Pade(float x)
{
    /*  Compute the numerator (p) and the denominator (q).                    */
    const float p = P0+x*(P1+x*(P2+x*(P3+x*(P4+x*(P5+x*(P6+x*P7))))));
    const float q = Q0+x*(Q1+x*(Q2+x*(Q3+x*(Q4+x*(Q5+x*(Q6+x*Q7))))));

    /*  Return the quotient.                                                  */
    return p / q;
}
/*  End of tmpl_Float_Exp_Pade.                                               */

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
