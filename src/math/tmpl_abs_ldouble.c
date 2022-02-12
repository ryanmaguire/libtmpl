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
 *                           tmpl_abs_ldouble                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = |x| at long double precision.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Abs:                                                     *
 *  Purpose:                                                                  *
 *      Computes the absolute value of a real number.                         *
 *                   --                                                       *
 *                  |   x,  x >= 0                                            *
 *          |x|  =  |  -x,  else                                              *
 *                   --                                                       *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number, the argument for |x|.                              *
 *  Output:                                                                   *
 *      abs_x (long double):                                                  *
 *          The absolute value of x.                                          *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, simply set the sign bit of the      *
 *      input to 0.                                                           *
 *                                                                            *
 *      If IEEE-754 is not supported, a simple if-then statement to check if  *
 *      the input is positive or not, returning x for non-negative and -x     *
 *      otherwise.                                                            *
 *                                                                            *
 *      NOTE:                                                                 *
 *          If IEEE-754 is not supported, if the input is NaN one may get     *
 *          +/- NaN (which is still NaN). This is because NaN always          *
 *          evaluates to false when a comparison is made (==, <, >, etc.).    *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
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
 *  2021/09/10: Ryan Maguire                                                  *
 *      Moved float and long double to their own files.                       *
 ******************************************************************************/

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 long double support.                                   */
#if defined(TMPL_HAS_IEEE754_LDOUBLE) && TMPL_HAS_IEEE754_LDOUBLE == 1

/*  Long double precision absolute value function (fabsl equivalent).         */
long double tmpl_LDouble_Abs(long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of w to the input.                           */
    w.r = x;

    /*  Set the sign bit to 0, indicating positive.                           */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN \
    && TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN
    w.bits.sign = 0x0U;
#else
    w.bits.signb = w.bits.signa ^ w.bits.signb;
    w.bits.signa = 0x0U;
#endif

    /*  Return the long double part of the union.                             */
    return w.r;
}

#else
/*  For #if defined(TMPL_HAS_IEEE754_LDOUBLE) && TMPL_HAS_IEEE754_LDOUBLE == 1*/

/*  In the absence of IEEE-754 support, a simple if-then statement works and  *
 *  is portable. Use this.                                                    */

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

#endif
/*  End #if defined(TMPL_HAS_IEEE754_LDOUBLE) && TMPL_HAS_IEEE754_LDOUBLE == 1*/
