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

/*  tmpl_Infinity is found here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_special_functions.h>

/*  Define the first 25 coefficients of the Taylor series.                    */
#define tmpl_BESSEL_I0_TAYLOR_00 1.0
#define tmpl_BESSEL_I0_TAYLOR_01 0.25
#define tmpl_BESSEL_I0_TAYLOR_02 1.56250e-2
#define tmpl_BESSEL_I0_TAYLOR_03 4.34027777777777777777777777778e-4
#define tmpl_BESSEL_I0_TAYLOR_04 6.78168402777777777777777777778e-6
#define tmpl_BESSEL_I0_TAYLOR_05 6.78168402777777777777777777778e-8
#define tmpl_BESSEL_I0_TAYLOR_06 4.70950279706790123456790123457e-10
#define tmpl_BESSEL_I0_TAYLOR_07 2.40280754952443940539178634417e-12
#define tmpl_BESSEL_I0_TAYLOR_08 9.38596699032984142731166540690e-15
#define tmpl_BESSEL_I0_TAYLOR_09 2.89690339207711155163940290337e-17
#define tmpl_BESSEL_I0_TAYLOR_10 7.24225848019277887909850725841e-20
#define tmpl_BESSEL_I0_TAYLOR_11 1.49633439673404522295423703686e-22
#define tmpl_BESSEL_I0_TAYLOR_12 2.59780277210771740096221707789e-25
#define tmpl_BESSEL_I0_TAYLOR_13 3.84290350903508491266600159451e-28
#define tmpl_BESSEL_I0_TAYLOR_14 4.90166263907536340901275713585e-31
#define tmpl_BESSEL_I0_TAYLOR_15 5.44629182119484823223639681761e-34
#define tmpl_BESSEL_I0_TAYLOR_16 5.31864435663559397679335626720e-37
#define tmpl_BESSEL_I0_TAYLOR_17 4.60090342269515049895619054256e-40
#define tmpl_BESSEL_I0_TAYLOR_18 3.55007980146230748376249270259e-43
#define tmpl_BESSEL_I0_TAYLOR_19 2.45850401763317692781336059736e-46
#define tmpl_BESSEL_I0_TAYLOR_20 1.53656501102073557988335037335e-49
#define tmpl_BESSEL_I0_TAYLOR_21 8.71068600351890918301219032512e-53
#define tmpl_BESSEL_I0_TAYLOR_22 4.49932128280935391684513963074e-56
#define tmpl_BESSEL_I0_TAYLOR_23 2.12633330945621640682662553438e-59
#define tmpl_BESSEL_I0_TAYLOR_24 9.22887721118149482129611777074e-63

/*  And the first 7 terms of the asymptotic series.                           */
#define tmpl_BESSEL_I0_ASYM_00 1.0
#define tmpl_BESSEL_I0_ASYM_01 0.1250
#define tmpl_BESSEL_I0_ASYM_02 0.07031250
#define tmpl_BESSEL_I0_ASYM_03 0.07324218750
#define tmpl_BESSEL_I0_ASYM_04 0.1121520996093750
#define tmpl_BESSEL_I0_ASYM_05 0.2271080017089843750
#define tmpl_BESSEL_I0_ASYM_06 0.5725014209747314453125

/*  Compute the Bessel I_0 function for a double precision value x. This      *
 *  returns double precision, maximum relative error ~1.e-9.                  */
double tmpl_Double_Bessel_I0(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double bessel_I0, arg, abs_x;

    /*  I_0 is symmetric so compute the absolute value of x and use that.     *
     *  tmpl_Abs_Double is an alias for fabs.                          */
    abs_x = tmpl_Double_Abs(x);

    /*  For small arguments, use a Taylor series to approximate I_0.          */
    if (abs_x < 16.0)
    {
        /*  The series is in powers of x^2, so use Horner's method with that. */
        arg = abs_x*abs_x;

        /*  Compute the degree 24 Taylor polynomial for bessel I0.            */
        bessel_I0 = tmpl_BESSEL_I0_TAYLOR_24;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_23;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_22;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_21;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_20;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_19;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_18;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_17;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_16;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_15;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_14;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_13;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_12;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_11;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_10;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_09;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_08;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_07;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_06;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_05;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_04;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_03;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_02;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_01;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_TAYLOR_00;
    }

    /*  For larger values, use the asymptotic expansion.                      */
    else if (abs_x < tmpl_Max_Double_Base_E)
    {
        /*  The asymptotic expansion is in terms of 1/x.                      */
        arg = 1.0/abs_x;

        /*  Compute the degree 6 polynomial term using Horner's Method.       */
        bessel_I0 = tmpl_BESSEL_I0_ASYM_06;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYM_05;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYM_04;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYM_03;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYM_02;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYM_01;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYM_00;

        /*  Multiply by the coefficient factor and return.                    */
        bessel_I0 *= tmpl_Double_Exp(abs_x) /
                     tmpl_Double_Sqrt(tmpl_Two_Pi*abs_x);
    }

    /*  For very large inputs, return infinity.                               */
    else
        bessel_I0 = tmpl_Infinity;

    return bessel_I0;
}
/*  End of tmpl_Double_Bessel_I0.                                             */

/*  Undefine all of the macros.                                               */
#undef tmpl_BESSEL_I0_TAYLOR_00
#undef tmpl_BESSEL_I0_TAYLOR_01
#undef tmpl_BESSEL_I0_TAYLOR_02
#undef tmpl_BESSEL_I0_TAYLOR_03
#undef tmpl_BESSEL_I0_TAYLOR_04
#undef tmpl_BESSEL_I0_TAYLOR_05
#undef tmpl_BESSEL_I0_TAYLOR_06
#undef tmpl_BESSEL_I0_TAYLOR_07
#undef tmpl_BESSEL_I0_TAYLOR_08
#undef tmpl_BESSEL_I0_TAYLOR_09
#undef tmpl_BESSEL_I0_TAYLOR_10
#undef tmpl_BESSEL_I0_TAYLOR_11
#undef tmpl_BESSEL_I0_TAYLOR_12
#undef tmpl_BESSEL_I0_TAYLOR_13
#undef tmpl_BESSEL_I0_TAYLOR_14
#undef tmpl_BESSEL_I0_TAYLOR_15
#undef tmpl_BESSEL_I0_TAYLOR_16
#undef tmpl_BESSEL_I0_TAYLOR_17
#undef tmpl_BESSEL_I0_TAYLOR_18
#undef tmpl_BESSEL_I0_TAYLOR_19
#undef tmpl_BESSEL_I0_TAYLOR_20
#undef tmpl_BESSEL_I0_TAYLOR_21
#undef tmpl_BESSEL_I0_TAYLOR_22
#undef tmpl_BESSEL_I0_TAYLOR_23
#undef tmpl_BESSEL_I0_TAYLOR_24
#undef tmpl_BESSEL_I0_ASYM_00
#undef tmpl_BESSEL_I0_ASYM_01
#undef tmpl_BESSEL_I0_ASYM_02
#undef tmpl_BESSEL_I0_ASYM_03
#undef tmpl_BESSEL_I0_ASYM_04
#undef tmpl_BESSEL_I0_ASYM_05
#undef tmpl_BESSEL_I0_ASYM_06
