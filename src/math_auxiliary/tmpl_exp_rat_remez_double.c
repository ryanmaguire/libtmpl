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
 *                          tmpl_exp_rat_remez_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a rational Remez approximation for exp(x) at double          *
 *      precision.                                                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Exp_Rat_Remez                                             *
 *  Purpose:                                                                  *
 *      Computes a degree (5, 4) rational Remez approximation for exp(x) with *
 *      |x| < 1 / 2.                                                          *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [-1/2, 1/2].                        *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          exp(x) to double precision.                                       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The degree (5, 4) rational Remez approximation for the function       *
 *      f(x) = (exp(x) - x - 1) / x^2 on the interval [-1/2, 1/2] has been    *
 *      computed and from this we can compute                                 *
 *                                                                            *
 *                             2 p(x)                                         *
 *          exp(x) ~= 1 + x + x  ----                                         *
 *                               q(x)                                         *
 *                                                                            *
 *      where p and q are the numerator and denominator for the rational      *
 *      Remez approximation, respectively. Scaling the ration p(x) / q(x) by  *
 *      x^2 ensures that the relative error is bounded by 1 ULP.              *
 *  Notes:                                                                    *
 *      1.) Accurate to double precision for |x| < 1 / 2. There are no        *
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

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+5.0000000000000001139464723731863581210527383588422E-01)
#define A01 (-1.5021092072734530103498987401467892307553894302446E-02)
#define A02 (+8.3316800886549523102187998260369345703544269935564E-03)
#define A03 (+2.5425701958764542252018254469103777311387685394622E-04)
#define A04 (+2.1127484746168657182663579931753831703545788556606E-05)
#define A05 (+6.0423918212072851946996474573188152415681984747586E-07)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (-3.6337551747880257382125769757576138330619516944007E-01)
#define B02 (+5.4455199336915358976051256287068883222936135738660E-02)
#define B03 (-4.0285926165518964447061348536092813452789142058479E-03)
#define B04 (+1.2566674365482457416981064140319455323503160431520E-04)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) \
A00 + z * (A01 + z * (A02 + z * (A03 + z * (A04 + z * A05))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) B00 + z * (B01 + z * (B02 + z * (B03 + z * B04)))

/*  Computes a rational Remez approximation for exp(x) on [-1/2, 1/2].        */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
double
tmpl_Double_Exp_Rat_Remez(const double x)
TMPL_UNSEQUENCED
{
    /*  Evaluate the rational approximation using Horner's method.            */
    const double num = TMPL_NUM_EVAL(x);
    const double den = TMPL_DEN_EVAL(x);
    const double rat = num / den;

    /*  The ratio approximates (exp(x) - x - 1) / x^2. We can compute exp(x)  *
     *  from this using Horner's method again.                                */
    return 1.0 + x * (1.0 + x * rat);
}
/*  End of tmpl_Double_Exp_Rat_Remez.                                         */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
