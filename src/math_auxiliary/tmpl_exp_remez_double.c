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
 *      Computes a degree 8 Remez polynomial for exp(x) with |x| < 1 / 8.     *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [-1/8, 1/8].                        *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          exp(x) to double precision.                                       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Evaluate the Remez polynomial using Horner's method and return.       *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for |x| < 1 / 8. There are no        *
 *          checks that the input falls within this interval.                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_ALWAYS_INLINE macro.                  *
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

/*  Coefficients for the degree 8 Remez polynomial of exp(x) on [-1/8, 1/8].  */
#define A00 (+1.0000000000000000009215954049308762993776079110806E+00)
#define A01 (+9.9999999999999422858577790154336363792140811516342E-01)
#define A02 (+4.9999999999999757611072971090428417591446673276834E-01)
#define A03 (+1.6666666667159260229087648216051748753310171715933E-01)
#define A04 (+4.1666666667737189961005686734891388252243039602894E-02)
#define A05 (+8.3333321981851822581882041523152814683308361502494E-03)
#define A06 (+1.3888887175298673340871982748810668217502549634535E-03)
#define A07 (+1.9850957901180098921215373620687628363139012571968E-04)
#define A08 (+2.4813083528278511384612204918196668939477127183945E-05)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*A08\
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
    return TMPL_POLY_EVAL(x);
}
/*  End of tmpl_Double_Exp_Remez.                                             */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
