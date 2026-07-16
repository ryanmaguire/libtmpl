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
 *                       tmpl_guarded_subtract_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs subtraction with a guard against optimizations.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Guarded_Subtract                                         *
 *  Purpose:                                                                  *
 *      Computes a - b, guarding this from aggressive compiler optimizations. *
 *  Arguments:                                                                *
 *      a (const long double):                                                *
 *          A real number.                                                    *
 *      b (const long double):                                                *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      diff (long double):                                                   *
 *          The floating-point difference a - b.                              *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a barrier to protect a and b from aggressive optimizations like   *
 *      -ffast-math and then perform the difference.                          *
 *  Notes:                                                                    *
 *      1.) Depending on compiler, floating-point barriers may produce a      *
 *          no-op, or they may use volatile.                                  *
 *                                                                            *
 *      2.) This function is really only useful for when you have:            *
 *                                                                            *
 *              val = a - b                                                   *
 *              ...                                                           *
 *              val = val + b                                                 *
 *                                                                            *
 *          When -ffast-math or similar optimizations are enabled, this may   *
 *          contract to val = a, which ignores the fact that floating-point   *
 *          arithmetic is not associative. This can ruin splitting methods    *
 *          like the one used to compute exp(x).                              *
 *                                                                            *
 *      3.) Non-destructive optimizations will still work with this function. *
 *          For example, on x86-64 machine this compiles to (GCC 16.1, -O3):  *
 *                                                                            *
 *              fld     TBYTE PTR [rsp+8]                                     *
 *              fld     TBYTE PTR [rsp+24]                                    *
 *              fsubp   st(1), st                                             *
 *              ret                                                           *
 *                                                                            *
 *          This function will also be inlined across translation units when  *
 *          link-time optimization is enabled.                                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Contains several configuration macros.                            *
 *  2.) tmpl_float_barrier.h:                                                 *
 *          Provides macros to protect against aggressive optimizations.      *
 *  3.) tmpl_split.h:                                                         *
 *          Function prototype / forward declaration provided here.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 15, 2026                                                 *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE found here.                                            */
#include <libtmpl/include/tmpl_config.h>

/*  Macros preventing aggressive compiler optimizations given here.           */
#include <libtmpl/include/tmpl_float_barrier.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_split.h>

/*  Function for subtracting two long doubles with compiler barriers.         */
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Guarded_Subtract(const long double a, const long double b)
{
    /*  Declare variables for the intermediate steps.                         */
    long double a_val, b_val, diff;

    /*  A barrier is needed at the start of the function in case this routine *
     *  is inlined. We need to separate lines in the calling function from    *
     *  the difference performed in this function. Make a copy and a barrier. */
    a_val = a;
    TMPL_LDOUBLE_BARRIER(a_val);

    /*  Provide the same protection for b.                                    */
    b_val = b;
    TMPL_LDOUBLE_BARRIER(b_val);

    /*  a and b are now guarded from aggressive optimizations, subtract them. */
    diff = a_val - b_val;

    /*  A final barrier to separate the end of this function from any calling *
     *  functions. This is necessary since this function will likely be       *
     *  inlined when link-time optimization is enabled.                       */
    TMPL_LDOUBLE_BARRIER(diff);
    return diff;
}
/*  End of tmpl_LDouble_Guarded_Subtract.                                     */
