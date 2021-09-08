/******************************************************************************
 *                                 LICENSE                                    *
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
 *                           tmpl_bessel_I0_float                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for computing the Bessel I0 function at single precision. This   *
 *      is defined as:                                                        *
 *          I_0(x)  =  J_0(ix)                                                *
 *      Where J_0 is the Bessel function of the First kind with nu = 0 and i  *
 *      is the imaginary unit.                                                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Bessel_I0:                                                 *
 *  Purpose:                                                                  *
 *      Compute the I_0 bessel function for a real argument.                  *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the argument for I_0(x).                           *
 *  Output:                                                                   *
 *      bessel_I0:                                                            *
 *          The Bessel function I_0(x).                                       *
 *  Method:                                                                   *
 *      This uses the standard Taylor series for small inputs, and            *
 *      asymptotic expansions for large inputs. The Taylor series is:         *
 *                                                                            *
 *                   ___                                                      *
 *                   \           x^(2n)                                       *
 *        I0(x)=     /__     --------------                                   *
 *                   n = 0   ((n)! * 2^n)^2                                   *
 *                                                                            *
 *      This can be obtained by simply evaluating ix into the J_0 function.   *
 *      The asymptotic expansions is of the form:                             *
 *                                                                            *
 *          I_0(x)  ~   exp(x) / sqrt(2 * pi * x)                             *
 *                                                                            *
 *      For very large values, we simply return infinity.                     *
 *  Error:                                                                    *
 *      In the region in which the Taylor series is used, relative error is   *
 *      10^-8. In the hand-off region with the asymptotic expansion, the      *
 *      error is 10^-6 but quickly drops back to 10^-8.                       *
 *      The regions where the Taylor series is used are listed below:         *
 *          float:           (-3.46, 3.46)                                    *
 *          double:          (-4.00, 4.00)                                    *
 *          long double:     (-4.35, 4.35)                                    *
 *  Notes:                                                                    *
 *      This code was written with an emphasis on clarity and accessibility   *
 *      to a wide audience without the need for anything too sophisticated.   *
 *      More accurate methods involving rational functions and Chebyshev      *
 *      polynomials exist. See the GNU Scientific Library for source code.    *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing infinity, nan, and other math tools.       *
 *  2.) tmpl_special_functions.h:                                             *
 *          Header file containing the functions prototype.                   *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       June 23, 2021                                                 *
 ******************************************************************************
 *                                History                                     *
 ******************************************************************************
 *  2019/09/15  Ryan Maguire:                                                 *
 *      Created file (Wellesley college for librssringoccs).                  *
 *  2020/09/12  Ryan Maguire:                                                 *
 *      Made code compliant with the C89 standard. Added comments.            *
 *  2021/06/23  Ryan Maguire:                                                 *
 *      Moved to libtmpl. Made changes so -Weverything mode in LLVM's clang   *
 *      does not complain.                                                    *
 ******************************************************************************/

/*  TMPL_INFINITY is found here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_special_functions.h>

/*  Define the first 29 coefficients of the Taylor series.                    */
#define tmpl_BESSEL_I0_TAYLORL_00 1.0L
#define tmpl_BESSEL_I0_TAYLORL_01 0.25L
#define tmpl_BESSEL_I0_TAYLORL_02 1.56250e-2L
#define tmpl_BESSEL_I0_TAYLORL_03 4.34027777777777777777777777778e-4L
#define tmpl_BESSEL_I0_TAYLORL_04 6.78168402777777777777777777778e-6L
#define tmpl_BESSEL_I0_TAYLORL_05 6.78168402777777777777777777778e-8L
#define tmpl_BESSEL_I0_TAYLORL_06 4.70950279706790123456790123457e-10L
#define tmpl_BESSEL_I0_TAYLORL_07 2.40280754952443940539178634417e-12L
#define tmpl_BESSEL_I0_TAYLORL_08 9.38596699032984142731166540690e-15L
#define tmpl_BESSEL_I0_TAYLORL_09 2.89690339207711155163940290337e-17L
#define tmpl_BESSEL_I0_TAYLORL_10 7.24225848019277887909850725841e-20L
#define tmpl_BESSEL_I0_TAYLORL_11 1.49633439673404522295423703686e-22L
#define tmpl_BESSEL_I0_TAYLORL_12 2.59780277210771740096221707789e-25L
#define tmpl_BESSEL_I0_TAYLORL_13 3.84290350903508491266600159451e-28L
#define tmpl_BESSEL_I0_TAYLORL_14 4.90166263907536340901275713585e-31L
#define tmpl_BESSEL_I0_TAYLORL_15 5.44629182119484823223639681761e-34L
#define tmpl_BESSEL_I0_TAYLORL_16 5.31864435663559397679335626720e-37L
#define tmpl_BESSEL_I0_TAYLORL_17 4.60090342269515049895619054256e-40L
#define tmpl_BESSEL_I0_TAYLORL_18 3.55007980146230748376249270259e-43L
#define tmpl_BESSEL_I0_TAYLORL_19 2.45850401763317692781336059736e-46L
#define tmpl_BESSEL_I0_TAYLORL_20 1.53656501102073557988335037335e-49L
#define tmpl_BESSEL_I0_TAYLORL_21 8.71068600351890918301219032512e-53L
#define tmpl_BESSEL_I0_TAYLORL_22 4.49932128280935391684513963074e-56L
#define tmpl_BESSEL_I0_TAYLORL_23 2.12633330945621640682662553438e-59L
#define tmpl_BESSEL_I0_TAYLORL_24 9.22887721118149482129611777074e-63L
#define tmpl_BESSEL_I0_TAYLORL_25 3.69155088447259792851844710830e-66L
#define tmpl_BESSEL_I0_TAYLORL_26 1.36521852236412645285445529153e-69L
#define tmpl_BESSEL_I0_TAYLORL_27 4.68181934967121554476836519729e-73L
#define tmpl_BESSEL_I0_TAYLORL_28 1.49292708854311720177562665730e-76L

/*  And the first 9 terms of the asymptotic series.                           */
#define tmpl_BESSEL_I0_ASYML_00 1.0L
#define tmpl_BESSEL_I0_ASYML_01 0.1250L
#define tmpl_BESSEL_I0_ASYML_02 0.07031250L
#define tmpl_BESSEL_I0_ASYML_03 0.07324218750L
#define tmpl_BESSEL_I0_ASYML_04 0.1121520996093750L
#define tmpl_BESSEL_I0_ASYML_05 0.2271080017089843750L
#define tmpl_BESSEL_I0_ASYML_06 0.57250142097473144531250L
#define tmpl_BESSEL_I0_ASYML_07 1.72772750258445739746093750L
#define tmpl_BESSEL_I0_ASYML_08 6.07404200127348303794860839844L

/*  Compute the Bessel I_0 function for a long double precision value x. This *
 *  returns long double precision, maximum relative error ~1.e-14.            */
long double tmpl_LDouble_Bessel_I0(long double x)
{
    /*  Declare necessary variables.                                          */
    long double bessel_I0, arg, abs_x;

    /*  I_0 is symmetric so compute the absolute value of x and use that.     *
     *  Abs_LongDouble is defined in rss_ringoccs_math.h, it is an alias for  *
     *  fabsl, if available, and fabs otherwise.                              */
    abs_x = tmpl_LDouble_Abs(x);

    /*  For small arguments, use a Taylor series to approximate I_0.          */
    if (abs_x < 19.0L)
    {
        /*  The series is in powers of x^2, so use Horner's method with that. */
        arg = abs_x*abs_x;

        /*  Compute the degree 28 Taylor polynomial for bessel I0.            */
        bessel_I0 = tmpl_BESSEL_I0_TAYLORL_28;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_27;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_26;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_25;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_24;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_23;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_22;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_21;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_20;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_19;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_18;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_17;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_16;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_15;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_14;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_13;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_12;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_11;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_10;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_09;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_08;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_07;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_06;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_05;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_04;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_03;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_02;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_01;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLORL_00;
    }

    /*  For larger values, use the asymptotic expansion. MAX_LDOUBLE_BASE_E   *
     *  is defined in rss_ringoccs_math.h, it's the largest value for a       *
     *  long double which won't return INFINITY for exp(x).                   */
    else if (abs_x < tmpl_Max_LDouble_Base_E)
    {
        /*  The asymptotic expansion is in terms of 1/x.                      */
        arg = 1.0L/abs_x;

        /*  Compute the degree 6 polynomial term using Horner's Method.       */
        bessel_I0 = tmpl_BESSEL_I0_ASYML_08;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYML_07;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYML_06;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYML_05;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYML_04;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYML_03;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYML_02;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYML_01;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYML_00;

        /*  Multiply by the coefficient factor and return.                    */
        bessel_I0 *= tmpl_LDouble_Exp(abs_x) /
                     tmpl_LDouble_Sqrt(tmpl_Two_Pi_L*abs_x);
    }

    /*  For very large inputs, return infinity.                               */
    else
        bessel_I0 = TMPL_INFINITYL;

    return bessel_I0;
}
/*  End of tmpl_LDouble_Bessel_I0.                                            */

#undef tmpl_BESSEL_I0_TAYLORL_00
#undef tmpl_BESSEL_I0_TAYLORL_01
#undef tmpl_BESSEL_I0_TAYLORL_02
#undef tmpl_BESSEL_I0_TAYLORL_03
#undef tmpl_BESSEL_I0_TAYLORL_04
#undef tmpl_BESSEL_I0_TAYLORL_05
#undef tmpl_BESSEL_I0_TAYLORL_06
#undef tmpl_BESSEL_I0_TAYLORL_07
#undef tmpl_BESSEL_I0_TAYLORL_08
#undef tmpl_BESSEL_I0_TAYLORL_09
#undef tmpl_BESSEL_I0_TAYLORL_10
#undef tmpl_BESSEL_I0_TAYLORL_11
#undef tmpl_BESSEL_I0_TAYLORL_12
#undef tmpl_BESSEL_I0_TAYLORL_13
#undef tmpl_BESSEL_I0_TAYLORL_14
#undef tmpl_BESSEL_I0_TAYLORL_15
#undef tmpl_BESSEL_I0_TAYLORL_16
#undef tmpl_BESSEL_I0_TAYLORL_17
#undef tmpl_BESSEL_I0_TAYLORL_18
#undef tmpl_BESSEL_I0_TAYLORL_19
#undef tmpl_BESSEL_I0_TAYLORL_20
#undef tmpl_BESSEL_I0_TAYLORL_21
#undef tmpl_BESSEL_I0_TAYLORL_22
#undef tmpl_BESSEL_I0_TAYLORL_23
#undef tmpl_BESSEL_I0_TAYLORL_24
#undef tmpl_BESSEL_I0_TAYLORL_25
#undef tmpl_BESSEL_I0_TAYLORL_26
#undef tmpl_BESSEL_I0_TAYLORL_27
#undef tmpl_BESSEL_I0_TAYLORL_28
#undef tmpl_BESSEL_I0_ASYML_00
#undef tmpl_BESSEL_I0_ASYML_01
#undef tmpl_BESSEL_I0_ASYML_02
#undef tmpl_BESSEL_I0_ASYML_03
#undef tmpl_BESSEL_I0_ASYML_04
#undef tmpl_BESSEL_I0_ASYML_05
#undef tmpl_BESSEL_I0_ASYML_06
#undef tmpl_BESSEL_I0_ASYML_07
#undef tmpl_BESSEL_I0_ASYML_08
