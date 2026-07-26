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
 *                               tmpl_abs_llong                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(n) = |n|, the absolute value of n.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LLong_Abs                                                        *
 *  Purpose:                                                                  *
 *      Computes the absolute value of an integer.                            *
 *                   --                                                       *
 *                  |   n,  n >= 0                                            *
 *          |n|  =  |  -n,  else                                              *
 *                   --                                                       *
 *  Arguments:                                                                *
 *      n (const signed long long int):                                       *
 *          An integer.                                                       *
 *  Output:                                                                   *
 *      abs_n (signed long long int):                                         *
 *          The absolute value of n.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a simple if-then statement. Bit tricks using 2's complement,      *
 *      1's complement, or sign-and-magnitude do not make the computation any *
 *      faster and can be avoided.                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_inttype.h:                                                       *
 *          Location of the TMPL_HAS_LONGLONG macro.                          *
 *  2.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  3.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 *  4.) tmpl_cast.h:                                                          *
 *          Contains the TMPL_CAST macro.                                     *
 *  5.) tmpl_integer.h:                                                       *
 *          Function prototype / forward declaration found here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 19, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/05/17: Ryan Maguire                                                  *
 *      Moved all versions to their own files.                                *
 *  2026/07/26: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes, removed  *
 *      undefined behavior when using two's complement.                       *
 ******************************************************************************/

/*  TMPL_HAS_LONGLONG macro found here.                                       */
#include <libtmpl/include/tmpl_inttype.h>

/*  Only implemented if long long support is available and requested.         */
#if TMPL_HAS_LONGLONG == 1

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  TMPL_CAST found here, used for casting with C vs. C++ compatibility.      */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Function prototype / forward declaration provided here.                   */
#include <libtmpl/include/tmpl_integer.h>

/*  Computes the absolute value of a signed long long int.                    */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
signed long long int tmpl_LLong_Abs(const signed long long int n)
TMPL_UNSEQUENCED
{
    /*  For negative inputs we carefully negate and return.                   */
    if (n < 0LL)
    {
        /*  On two's complement machines, negating the most negative value    *
         *  produces undefined behavior. What is defined is casting the       *
         *  result to unsigned, negating this, and then casting back to       *
         *  signed. For all other inputs, this produces the absolute value.   *
         *  For the most negative two's complement integer, this produces 0,  *
         *  which is the absolute value mod 2^width, where width is the       *
         *  number of bits in the unsigned type.                              */
        const unsigned long long int n_u = TMPL_CAST(n, unsigned long long int);
        return TMPL_CAST(-n_u, signed long long int);
    }

    /*  Otherwise, nothing to do. Return the input.                           */
    return n;
}
/*  End of tmpl_LLong_Abs.                                                    */

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */
