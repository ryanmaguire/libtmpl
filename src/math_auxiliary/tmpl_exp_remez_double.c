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
 *                            tmpl_exp_remez_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez polynomial for exp(x) at double precision.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Exp_Remez                                                 *
 *  Purpose:                                                                  *
 *      Computes a degree 9 Remez polynomial for exp(x) with |x| < 1 / 8.     *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [-1/8, 1/8].                        *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          exp(x) to double precision.                                       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Evaluate the degree 8 Remez polynomial for (exp(x) - 1) / x on the    *
 *      interval [-1/8, 1/8] and return 1 + x * p(x) where p is the Remez     *
 *      polynomial. p(x) is evaluated using Horner's method.                  *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for |x| < 1 / 8. There are no        *
 *          checks that the input falls within this interval.                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_math_auxiliary.h:                                                *
 *          Header file where the function declaration is found.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 2, 2026                                               *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

/*  Coefficients for a degree 9 Remez polynomial of exp(x) on [-1/8, 1/8].    */
#define A00 (+1.0000000000000000000830453730224914834530830068564E+00)
#define A01 (+4.9999999999999942289142137687298374815863363172229E-01)
#define A02 (+1.6666666666666644819607194155409874903880917737901E-01)
#define A03 (+4.1666666667159233800833111760173861976292059718626E-02)
#define A04 (+8.3333333334299309224482374883267402582196199527828E-03)
#define A05 (+1.3888887753795082297905428529652645349820378910564E-03)
#define A06 (+1.9841268292100781144760395238799382109603178794627E-04)
#define A07 (+2.4811275012614269165422523044901871010406575830516E-05)
#define A08 (+2.7567738657216295347347902201602657555824095019714E-06)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * (\
                        A06 + z * (\
                            A07 + z * A08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Computes a Remez polynomial for exp(x) on [-1/8, 1/8].                    */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Exp_Remez(const double x)
TMPL_UNSEQUENCED
{
    /*  Evaluate the Remez polynomial using Horner's method and return.       */
    const double poly = TMPL_POLY_EVAL(x);
    return 1.0 + x * poly;
}
/*  End of tmpl_Double_Exp_Remez.                                             */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
