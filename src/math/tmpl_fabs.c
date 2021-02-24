/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                                 tmpl_fabs                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the absolute value function for floating *
 *      point data types (float, double, long double).                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Abs:                                                       *
 *      tmpl_Double_Abs:                                                      *
 *      tmpl_LDouble_Abs:                                                     *
 *  Purpose:                                                                  *
 *      Computes the absolute value of a real number.                         *
 *                   --                                                       *
 *                  |   x,  x > 0                                             *
 *          |x|  =  |  -x,  else                                              *
 *                   --                                                       *
 *  Arguments:                                                                *
 *      x (float/double/long double):                                         *
 *          A real number, the argument for |x|.                              *
 *  Output:                                                                   *
 *      abs_x (float/double/long double):                                     *
 *          The absolute value of x.                                          *
 *  Method:                                                                   *
 *      This uses a simple if-then statement to check if the input is         *
 *      positive or not, returning x for non-negative and -x otherwise.       *
 *                                                                            *
 *      If the __TMPL_USE_IEEE754_ALGORITHMS__ macro is set to 1 in           *
 *      tmpl_config.h, the algorithm uses the IEEE 754 format to compute the  *
 *      absolute value by switching the "sign" bit of a floating point number *
 *      to zero, meaning the number is non-negative.                          *
 *  Notes:                                                                    *
 *      fabsf and fabsl are not provided in C89/C90 implementations of the    *
 *      language, and instead type conversions are made in the fabs function. *
 *      Since the absolute value function is very simple, we simply provide   *
 *      the algorithms here rather than pass the arguments to fabs, fabsf, or *
 *      fabsfl. There is essentially no time difference. Using gcc with -O2   *
 *      optimization on an array of 1 million random elements in [-1, 1] gave *
 *      the following times (in seconds):                                     *
 *          fabs:         0.003328                                            *
 *          libtmpl:      0.003743                                            *
 *      -O3 optimization gives:                                               *
 *          fabs:         0.003409                                            *
 *          libtmpl:      0.003493                                            *
 *      So, no real difference. These times were computed on an iMac 2017     *
 *      3.4GHz quad-core running MacOS Catalina 10.15.7. Converting a long    *
 *      double to a double may lose precision, hence the reason we provide    *
 *      this simple code.                                                     *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
 *  2.) tmpl_ieee754.h:                                                       *
 *          Header file that contains union data types for working with       *
 *          floating point numbers using 32 and 64 bit integer data types.    *
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
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/01: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/08: Ryan Maguire                                                  *
 *      Frozen for v1.3 of librssringoccs.                                    *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied file from rss_ringoccs.                                        *
 *  2021/02/24: Ryan Maguire                                                  *
 *      Added IEEE 754 code for computing the absolute value function.        *
 ******************************************************************************/

/*  Header file where the prototypes for these functions are defined.         */
#include <libtmpl/include/tmpl_math.h>

/*  If your compiler supports the IEEE 754 format, we can use a single        *
 *  bit-wise AND statement to compute the absolute value function.            */
#if __TMPL_USE_IEEE754_ALGORITHMS__ == 1

/*  IEEE754 union data types and functions are found here.                    */
#include <libtmpl/include/tmpl_ieee754.h>

/*  Single precision absolute value function (fabsf equivalent).              */
float tmpl_Float_Abs(float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEE754_Word32 w;

    /*  Set the float part of the word to the input x.                        */
    w.real = x;

    /*  Use bit-wise AND to set the first bit to zero. A 32 bit floating      *
     *  point number is represented by:                                       *
     *      s eeeeeeee xxxxxxxxxxxxxxxxxxxxxxx                                *
     *      - -------- -----------------------                                *
     *    Sign  Exp           Fraction                                        *
     *  We can use bit-wise AND to set the sign bit to zero. We need the      *
     *  number that is 0 in the zeroth bit, and 1 in all of the others. In    *
     *  hexidecimal, this is 7FFFFFFF, which we represent in the C            *
     *  programming language via 0x7FFFFFFF. The bit-wise AND is represented  *
     *  by a single ampersand, &.                                             */
    w.integer = 0x7FFFFFFF & w.integer;

    /*  Now that we've set the integer part of our union to have its zeroth   *
     *  bit set to zero, return the float part of the union.                  */
    return w.real;
}
/*  End of tmpl_Float_Abs.                                                    */

/*  Single precision absolute value function (fabsf equivalent).              */
double tmpl_Double_Abs(double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEE754_Word64 w;

    /*  Set the double part of the word to the input x.                       */
    w.real = x;

    /*  Use bit-wise AND to set the first bit to zero. A 64 bit floating      *
     *  point number is represented by:                                       *
     *    s eeeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  *
     *    - ----------- ----------------------------------------------------  *
     *  Sign  Exponent                     Fraction                           *
     *  We can use bit-wise AND to set the sign bit to zero. We need the      *
     *  number that is 0 in the zeroth bit, and 1 in all of the others. In    *
     *  hexidecimal, this is 7FFFFFFFFFFFFFFF, which we represent in the C    *
     *  programming language via 0x7FFFFFFFFFFFFFFF. The bit-wise AND is      *
     *  represented by a single ampersand, &.                                 */
    w.integer = 0x7FFFFFFFFFFFFFFF & w.integer;

    return w.real;
}
/*  End of tmpl_Double_Abs.                                                   */

#else
/*  Else statement for #if __TMPL_USE_IEEE754_ALGORITHMS__ == 1.              */

/*  Single precision absolute value function (fabsf equivalent).              */
float tmpl_Float_Abs(float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float abs_x;

    /*  If x is positive return it, otherwise return its negative.            */
    if (x >= 0.0F)
        abs_x = x;
    else
        abs_x = -x;

    return abs_x;
}
/*  End of tmpl_Float_Abs.                                                    */

/*  Double precision absolute value function (fabs equivalent).               */
double tmpl_Double_Abs(double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double abs_x;

    /*  If x is positive return it, otherwise return its negative.            */
    if (x >= 0.0)
        abs_x = x;
    else
        abs_x = -x;

    return abs_x;
}
/*  End of tmpl_Double_Abs.                                                   */

#endif

/*  libtmpl does not implement IEEE754 support for long double extended       *
 *  precision. This is because extended precision can be 80, 96, or 128 bit.  *
 *  Guessing which one is being used would break portability.                 */

/*  Long double precision absolute value function (fabsl equivalent).         */
long double tmpl_LDouble_Abs(long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double abs_x;

    /*  If x is positive return it, otherwise return its negative.            */
    if (x >= 0.0L)
        abs_x = x;
    else
        abs_x = -x;

    return abs_x;
}
/*  End of tmpl_LDouble_Abs.                                                  */

