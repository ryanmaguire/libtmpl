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
 *                               tmpl_gcd_uint                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the GCD of two unsigned integers.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UInt_GCD                                                         *
 *  Purpose:                                                                  *
 *      Computes GCD(m, n), the greatest common divisor of m and n.           *
 *  Arguments:                                                                *
 *      m (const unsigned int):                                               *
 *          An integer.                                                       *
 *      n (const unsigned int):                                               *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      gcd (unsigned int):                                                   *
 *          The greatest common divisor of m and n.                           *
 *  Method:                                                                   *
 *      Inspect the TMPL_GCD_ALGORITHM macro and use the corresponding        *
 *      function. The default is the mixed-binary method.                     *
 *  Notes:                                                                    *
 *      1.) Benchmarks using GCC and clang on Debian GNU/Linux (x86_64) show  *
 *          that mixed-binary is the fastest algorithm, being nearly twice as *
 *          fast as the binary algorithm, and more than twice as fast as the  *
 *          Euclidean algorithm. With other compilers and operating systems   *
 *          the binary algorithm is the fastest, and the mixed-binary method  *
 *          may be slower than the Euclidean algorithm. Usually there are two *
 *          possibilities for the benchmarks. Most common:                    *
 *                                                                            *
 *              1.) Mixed-Binary Algorithm                                    *
 *              2.) Binary Algorithm                                          *
 *              3.) Euclidean Algorithm                                       *
 *              4.) Naive / By-Hand Algorithm                                 *
 *                                                                            *
 *          Not quite as common:                                              *
 *                                                                            *
 *              1.) Binary Algorithm                                          *
 *              2.) Euclidean Algorithm                                       *
 *              3.) Mixed-Binary Algorithm                                    *
 *              4.) Naive / By-Hand Algorithm                                 *
 *                                                                            *
 *          Run the benchmarks yourself and see which algorithm is fastest.   *
 *          Set the TMPL_GCD_ALGORITHM accordingly (see build instructions).  *
 *                                                                            *
 *      2.) By definition, GCD(0, 0) = 0, GCD(n, 0) = n, and GCD(0, n) = n.   *
 *          This function follows these requirements.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_ALWAYS_INLINE macro.                  *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header providing C23 attributes for optimization.                 *
 *  3.) tmpl_integer.h:                                                       *
 *          Function prototype / forward declaration found here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 4, 2026                                               *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  C23 attributes for optimization are found here.                           */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration provided here.                   */
#include <libtmpl/include/tmpl_integer.h>

/*  Function for computing the GCD of two unsigned integers.                  */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
unsigned int tmpl_UInt_GCD(const unsigned int m, const unsigned int n)
TMPL_UNSEQUENCED
{
#if TMPL_GCD_ALGORITHM == TMPL_GCD_ALGORITHM_MIXED_BINARY
    return tmpl_UInt_GCD_Mixed_Binary(m, n);
#elif TMPL_GCD_ALGORITHM == TMPL_GCD_ALGORITHM_BINARY
    return tmpl_UInt_GCD_Binary(m, n);
#elif TMPL_GCD_ALGORITHM == TMPL_GCD_ALGORITHM_EUCLIDEAN
    return tmpl_UInt_GCD_Euclidean(m, n);
#else
    return tmpl_UInt_GCD_Naive(m, n);
#endif
}
/*  End of tmpl_UInt_GCD.                                                     */
