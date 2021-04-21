/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of rss_ringoccs.                                        *
 *                                                                            *
 *  rss_ringoccs is free software: you can redistribute it and/or modify it   *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  rss_ringoccs is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with rss_ringoccs.  If not, see <https://www.gnu.org/licenses/>.    *
 ******************************************************************************
 *                                Bessel I0                                   *
 ******************************************************************************
 *  This file contains functions for computing the Bessel I0 function.        *
 *  We define I_0(x) as follows:                                              *
 *                                                                            *
 *      I_0(x)  =  J_0(ix)                                                    *
 *                                                                            *
 *  Where J_0 is the Bessel function of the First kind with nu = 0 and i is   *
 *  the imaginary unit.                                                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  BesselI0:                                                                 *
 *  Purpose:                                                                  *
 *      Compute the I_0 bessel function for a real argument.                  *
 *  Arguments:                                                                *
 *      x (float/double)                                                      *
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
 *                                                                            *
 *      The asymptotic expansions is of the form:                             *
 *                                                                            *
 *          I_0(x)  ~   exp(x) / sqrt(2 * pi * x)                             *
 *                                                                            *
 *      For very large values, we simply return infinity.                     *
 *  Error:                                                                    *
 *      In the region in which the Taylor series is used, relative error is   *
 *      10^-16. In the hand-off region with the asymptotic expansion, the     *
 *      error is 10^-9 but quickly drops back to 10^-16.                      *
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
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in configspecialfunctions.sh uses gcc and has the *
 *  -pedantic and =std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) math.h:                                                               *
 *      Standard library for mathematical functions like sin, cos, atan.      *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/NASA-Planetary-Science/rss_ringoccs/issues             *
 ******************************************************************************
 *                          A NOTE ON CONVENTIONS                             *
 ******************************************************************************
 *  1.) i is a complex number, we'll use n for indexing. Max index values for *
 *      a for loop or while loop should be either capital N, or preferrably   *
 *      a variable name describing what this limit is. i.e. if it's the size  *
 *      of an array, call it arr_size.                                        *
 *  2.) Do not cast malloc. While this is required in C++, it is not in C and *
 *      the official documentation even frowns upon it. That is, do this:     *
 *          double *ptr;                                                      *
 *          long N;                                                           *
 *          ...                                                               *
 *          ptr = malloc(sizeof(*ptr) * N);                                   *
 *      and not:                                                              *
 *          ptr = (double *)malloc(sizeof(*ptr) * N);                         *
 *      malloc returns a void pointer and this is automatically and safely    *
 *      promoted to whatever the type of ptr is.                              *
 *  3.) While not frowned upon, the following makes maintenance easier.       *
 *      Instead of using malloc like (for a pointer to a double):             *
 *          ptr = malloc(sizeof(double) * N);                                 *
 *      Use:                                                                  *
 *          ptr = malloc(sizeof(*ptr) * N);                                   *
 *  4.) Declare variables towards the top of the code and not inside a for    *
 *      loop. It's extremely ugly. The following is good:                     *
 *          long k;                                                           *
 *          long N = 100;                                                     *
 *          for (k=0; k<N; ++k)                                               *
 *              do stuff                                                      *
 *      And this looks horrid:                                                *
 *          long N = 100;                                                     *
 *          for (long k=0; k<N; ++k)                                          *
 *              do stuff                                                      *
 *      While legal in C99, it is not in C89 and the way the config script is *
 *      is set up will cause compiler errors.                                 *
 *  5.) If a number is needed in a for loop, even once, declare or set it as  *
 *      a macro, rather than having the number verbatim in the loop. If the   *
 *      the number needs to change it's easier to keep track this way.        *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       September 15, 2019                                            *
 ******************************************************************************
 *                                History                                     *
 ******************************************************************************
 *  2020/09/12 (Ryan Maguire):                                                *
 *      Made code compliant with the C89 standard. Added comments.            *
 ******************************************************************************/

/*  The C standard library header math.h is included here, as are aliases for *
 *  various functions, the macros INFINITY and NAN, as well as the max legal  *
 *  values for the exponential function which don't return INFINITY.          */
#include <libtmpl/include/tmpl_math.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_special_functions.h>

/*  Compute the Bessel I_0 function for a floating point number x. This       *
 *  returns floating point precision, maximum relative error ~1.e-6.          */
float tmpl_Float_Bessel_I0(float x)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    float bessel_I0, arg, abs_x;

    /*  I_0 is an even function, so compute the absolute value of x.          *
     *  tmpl_Abs_Float is a macro for fabsf, if your system provides   *
     *  it (C99 math.h) and fabs if not, defined in rss_ringoccs_math.h.      */
    abs_x = tmpl_Float_Abs(x);

    /*  For small arguments, use a Taylor series to approximate I_0.          */
    if (abs_x < 12.0F)
    {
        /*  The series is in powers of x^2, so use Horner's method of         *
         *  polynomial computation with that.                                 */
        arg = abs_x*abs_x;

        /*  Compute the degree 16 Taylor polynomial for bessel I0.            */
        bessel_I0 =
            tmpl_Real_Poly_Float_Coeffs(tmpl_Float_Bessel_I0_Taylor, 16, arg);
    }

    /*  For larger values, use the asymptotic expansion. MAX_FLOAT_BASE_E is  *
     *  the largest float x which doesn't return INFINITY. It is defined in   *
     *  rss_ringocc_math.h.                                                   */
    else if (abs_x < tmpl_Max_Float_Base_E)
    {
        /*  The asymptotic expansion is in terms of 1/x.                      */
        arg = 1.0F/abs_x;

        /*  Compute the degree 4 polynomial term using Horner's Method.       */
        bessel_I0 =
            tmpl_Real_Poly_Float_Coeffs(tmpl_Float_Bessel_I0_Asym, 4, arg);

        /*  Multiply by the coefficient factor and return. Exp_Float and      *
         *  Sqrt_Float are aliases for expf and sqrtf, respectively, if your  *
         *  platform provides it, and exp and sqrt, respectively, otherwise.  *
         *  They are defined in rss_ringoccs_math.h. The tmpl_Two_Pi macros is*
         *  defined in rss_ringoccs_math.h.                                   */
        bessel_I0 *= tmpl_Float_Exp(abs_x)/tmpl_Float_Sqrt(tmpl_Two_Pi_F*abs_x);
    }

    /*  For very large inputs, return INFINITY. INFINITY is standard in C99,  *
     *  but defined in rss_ringoccs_math.h if not available.                  */
    else
        bessel_I0 = tmpl_Infinity_F;

    return bessel_I0;
}

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
        bessel_I0 =
            tmpl_Real_Poly_Double_Coeffs(tmpl_Double_Bessel_I0_Taylor, 24, arg);
    }

    /*  For larger values, use the asymptotic expansion. MAX_DOUBLE_BASE_E is *
     *  defined in rss_ringoccs_math.h, it's the largest value for a double   *
     *  which won't return INFINITY for exp(x).                               */
    else if (abs_x < tmpl_Max_Double_Base_E)
    {
        /*  The asymptotic expansion is in terms of 1/x.                      */
        arg = 1.0/abs_x;

        /*  Compute the degree 6 polynomial term using Horner's Method.       */
        bessel_I0 =
            tmpl_Real_Poly_Double_Coeffs(tmpl_Double_Bessel_I0_Asym, 6, arg);

        /*  Multiply by the coefficient factor and return. Exp_Double and     *
         *  Sqrt_Double are aliases for exp and sqrt, respectively, defined   *
         *  in rss_ringoccs_math.h. tmpl_Two_Pi is in rss_ringoccs_math.h.         */
        bessel_I0 *= tmpl_Double_Exp(abs_x) /
                     tmpl_Double_Sqrt(tmpl_Two_Pi*abs_x);
    }

    /*  For very large inputs, return INFINITY. INFINITY is standard in C99,  *
     *  and provided in rss_ringoccs_math.h otherwise.                        */
    else
        bessel_I0 = tmpl_Infinity;

    return bessel_I0;
}

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
        bessel_I0 = tmpl_Real_Poly_LDouble_Coeffs(tmpl_LDouble_Bessel_I0_Taylor,
                                                  28, arg);
    }

    /*  For larger values, use the asymptotic expansion. MAX_LDOUBLE_BASE_E   *
     *  is defined in rss_ringoccs_math.h, it's the largest value for a       *
     *  long double which won't return INFINITY for exp(x).                   */
    else if (abs_x < tmpl_Max_LDouble_Base_E)
    {
        /*  The asymptotic expansion is in terms of 1/x.                      */
        arg = 1.0L/abs_x;

        /*  Compute the degree 6 polynomial term using Horner's Method.       */
        bessel_I0 =
            tmpl_Real_Poly_LDouble_Coeffs(tmpl_LDouble_Bessel_I0_Asym, 8, arg);

        /*  Multiply by the coefficient factor and return. Exp_LongDouble and *
         *  Sqrt_LongDouble are aliases for expl and sqrtl, respectively, if  *
         *  available, and exp and sqrt otherwise. They are defined in        *
         *  rss_ringoccs_math.h. tmpl_Two_Pi is in rss_ringoccs_math.h.            */
        bessel_I0 *= tmpl_LDouble_Exp(abs_x) /
                     tmpl_LDouble_Sqrt(tmpl_Two_Pi_L*abs_x);
    }

    /*  For very large inputs, return INFINITY. This is standard in C99, and  *
     *  provided in rss_ringoccs_math.h otherwise.                            */
    else
        bessel_I0 = tmpl_Infinity_L;

    return bessel_I0;
}

