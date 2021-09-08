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

/*  Define the first 17 Taylor series coefficients for small values.          */
#define tmpl_BESSEL_IO_TAYLORF_00 1.0F
#define tmpl_BESSEL_IO_TAYLORF_01 0.25F
#define tmpl_BESSEL_IO_TAYLORF_02 1.56250E-2F
#define tmpl_BESSEL_IO_TAYLORF_03 4.34027777777777777777777777778E-4F
#define tmpl_BESSEL_IO_TAYLORF_04 6.78168402777777777777777777778E-6F
#define tmpl_BESSEL_IO_TAYLORF_05 6.78168402777777777777777777778E-8F
#define tmpl_BESSEL_IO_TAYLORF_06 4.70950279706790123456790123457E-10F
#define tmpl_BESSEL_IO_TAYLORF_07 2.40280754952443940539178634417E-12F
#define tmpl_BESSEL_IO_TAYLORF_08 9.38596699032984142731166540690E-15F
#define tmpl_BESSEL_IO_TAYLORF_09 2.89690339207711155163940290337E-17F
#define tmpl_BESSEL_IO_TAYLORF_10 7.24225848019277887909850725841E-20F
#define tmpl_BESSEL_IO_TAYLORF_11 1.49633439673404522295423703686E-22F
#define tmpl_BESSEL_IO_TAYLORF_12 2.59780277210771740096221707789E-25F
#define tmpl_BESSEL_IO_TAYLORF_13 3.84290350903508491266600159451E-28F
#define tmpl_BESSEL_IO_TAYLORF_14 4.90166263907536340901275713585E-31F
#define tmpl_BESSEL_IO_TAYLORF_15 5.44629182119484823223639681761E-34F
#define tmpl_BESSEL_IO_TAYLORF_16 5.31864435663559397679335626720E-37F

/*  Define the first 5 coefficients of the asymptotic series.                 */
#define tmpl_BESSEL_I0_ASYMF_00 1.0F
#define tmpl_BESSEL_I0_ASYMF_01 0.1250F
#define tmpl_BESSEL_I0_ASYMF_02 0.07031250F
#define tmpl_BESSEL_I0_ASYMF_03 0.07324218750F
#define tmpl_BESSEL_I0_ASYMF_04 0.1121520996093750F

/*  Compute the Bessel I_0 function for a floating point number x. This       *
 *  returns floating point precision, maximum relative error ~1.e-6.          */
float tmpl_Float_Bessel_I0(float x)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    float bessel_I0, arg;

    /*  I_0 is an even function, so compute the absolute value of x.          */
    const float abs_x = tmpl_Float_Abs(x);

    /*  For small arguments, use a Taylor series to approximate I_0.          */
    if (abs_x < 12.0F)
    {
        /*  The series is in powers of x^2, so use Horner's method of         *
         *  polynomial computation with that.                                 */
        arg = x*x;

        /*  Compute the degree 16 Taylor polynomial for bessel I0.            */
        bessel_I0 = tmpl_BESSEL_IO_TAYLORF_16;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_15;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_14;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_13;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_12;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_11;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_10;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_09;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_08;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_07;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_06;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_05;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_04;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_03;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_02;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_01;
        bessel_I0 = arg*bessel_I0 + tmpl_BESSEL_IO_TAYLORF_00;
    }

    /*  For larger values, use the asymptotic expansion. The constant         *
     *  tmpl_Max_Float_Base_E is the largest value such that exp(x) does not  *
     *  return infinity. It is defined in tmpl_math.h.                        */
    else if (abs_x < tmpl_Max_Float_Base_E)
    {
        /*  The asymptotic expansion is in terms of 1/x.                      */
        arg = 1.0F/abs_x;

        /*  Compute the degree 4 polynomial term using Horner's Method.       */
        bessel_I0 = tmpl_BESSEL_I0_ASYMF_04;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYMF_03;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYMF_02;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYMF_01;
        bessel_I0 = arg * bessel_I0 + tmpl_BESSEL_I0_ASYMF_00;

        /*  Multiply by the coefficient factor and return.                    */
        bessel_I0 *= tmpl_Float_Exp(abs_x)/tmpl_Float_Sqrt(tmpl_Two_Pi_F*abs_x);
    }

    /*  For very large inputs, return infinity.                               */
    else
        bessel_I0 = TMPL_INFINITYF;

    return bessel_I0;
}
/*  End of tmpl_Float_Bessel_I0.                                              */

#undef tmpl_BESSEL_IO_TAYLORF_00
#undef tmpl_BESSEL_IO_TAYLORF_01
#undef tmpl_BESSEL_IO_TAYLORF_02
#undef tmpl_BESSEL_IO_TAYLORF_03
#undef tmpl_BESSEL_IO_TAYLORF_04
#undef tmpl_BESSEL_IO_TAYLORF_05
#undef tmpl_BESSEL_IO_TAYLORF_06
#undef tmpl_BESSEL_IO_TAYLORF_07
#undef tmpl_BESSEL_IO_TAYLORF_08
#undef tmpl_BESSEL_IO_TAYLORF_09
#undef tmpl_BESSEL_IO_TAYLORF_10
#undef tmpl_BESSEL_IO_TAYLORF_11
#undef tmpl_BESSEL_IO_TAYLORF_12
#undef tmpl_BESSEL_IO_TAYLORF_13
#undef tmpl_BESSEL_IO_TAYLORF_14
#undef tmpl_BESSEL_IO_TAYLORF_15
#undef tmpl_BESSEL_IO_TAYLORF_16
#undef tmpl_BESSEL_I0_ASYMF_00
#undef tmpl_BESSEL_I0_ASYMF_01
#undef tmpl_BESSEL_I0_ASYMF_02
#undef tmpl_BESSEL_I0_ASYMF_03
#undef tmpl_BESSEL_I0_ASYMF_04
