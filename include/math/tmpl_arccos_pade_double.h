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
 *                          tmpl_arccos_pade_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (12, 12) Pade approximant of acos(x) at double precision.*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arccos_Pade                                               *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of order (12, 12) for arccos.           *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (double):                                                      *
 *          The Pade approximation of acos(x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *          acos(x)+x-pi/2   a0 + a1*x^2 + ... + a5*x^10 + a6*x^12            *
 *          -------------- = -------------------------------------            *
 *               x^3          1 + b1*x^2 + ... + a5*x^10 + b6*x^12            *
 *  Notes:                                                                    *
 *      Accurate for |x| < 0.6. For |x| < 0.9 this is accurate to about       *
 *      single precision (10^-7 relative error). Not accurate for |x| near 1. *
 *                                                                            *
 *      It is a lot faster (~2-3x) to call this function than the main        *
 *      arccos routine. If you don't need perfect accuracy, and if |x| is not *
 *      near 1, you may benefit from using this.                              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_pade_double.c to just include this file. *
 *  2023/05/14: Ryan Maguire                                                  *
 *      Changed so that this computes an actual Pade approximant. It was a    *
 *      Remez rational minimax approximation before, improperly labelled.     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_PADE_DOUBLE_H
#define TMPL_ARCCOS_PADE_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P0 (+1.6666666666666666666666666666666666666666666666667E-01)
#define P1 (-4.5183467789315450573566044285447580081757824962844E-01)
#define P2 (+4.5268338285839953885847747489466534382453836599311E-01)
#define P3 (-2.0451170074586957459619221134199241262964264122754E-01)
#define P4 (+4.0161699156136797388526896443437389593682105247059E-02)
#define P5 (-2.6043612272315037174810668430207303056407157408729E-03)
#define P6 (+8.5298365158969137130716621168483153368286640425841E-06)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q0 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q1 (-3.1610080673589270344139626571268548049054694977706E+00)
#define Q2 (+3.8706967846047715414942909022179338680118343270983E+00)
#define Q3 (-2.3044768347428901379839394147005695603073114886090E+00)
#define Q4 (+6.8318346338074073586036792129413385817260793401216E-01)
#define Q5 (-9.1189047491786682631147583983250333633502470655541E-02)
#define Q6 (+3.9268447888541310343247866236378900929051188393826E-03)

/*  Helper macros for evaluating a polynomial via Horner's method.            */
#define TMPL_NUM_EVAL(z) P0 + z*(P1 + z*(P2 + z*(P3 + z*(P4 + z*(P5 + z*P6)))))
#define TMPL_DEN_EVAL(z) Q0 + z*(Q1 + z*(Q2 + z*(Q3 + z*(Q4 + z*(Q5 + z*Q6)))))

/*  Function for computing the (12, 12) Pade approximant of acos(x).          */
TMPL_INLINE_DECL
double tmpl_Double_Arccos_Pade(double x)
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const double x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const double p = TMPL_NUM_EVAL(x2);
    const double q = TMPL_DEN_EVAL(x2);
    const double r = x2*p/q;

    /*  p/q is the Pade approximant for (acos(x) - pi/2 + x) / x^3.           */
    return tmpl_Pi_By_Two - (x + x*r);
}
/*  End of tmpl_Double_Arccos_Pade.                                           */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P6
#undef P5
#undef P4
#undef P3
#undef P2
#undef P1
#undef P0
#undef Q6
#undef Q5
#undef Q4
#undef Q3
#undef Q2
#undef Q1
#undef Q0
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
/*  End of include guard.                                                     */
