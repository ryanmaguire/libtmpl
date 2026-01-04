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
 *                               tmpl_gcd_ulong                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the GCD of two unsigned integers.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULong_GCD                                                        *
 *  Purpose:                                                                  *
 *      Computes GCD(m, n), the greatest common divisor of m and n.           *
 *  Arguments:                                                                *
 *      m (unsigned long int):                                                *
 *          An integer.                                                       *
 *      n (unsigned long int):                                                *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      gcd (unsigned long int):                                              *
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
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 4, 2026                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_GCD_ULONG_H
#define TMPL_GCD_ULONG_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Get the requested algorithm, examine the TMPL_GCD_ALGORITHM macro.        *
 *  Default, mixed-binary which combines the Euclidean and Stein algorithms.  */
#if TMPL_GCD_ALGORITHM == TMPL_GCD_ALGORITHM_MIXED_BINARY

/******************************************************************************
 *                           Mixed Binary Algorithm                           *
 ******************************************************************************/

/*  Forward declaration / function prototype for the mixed-binary function.   */
extern unsigned long int
tmpl_ULong_GCD_Mixed_Binary(const unsigned long int m,
                            const unsigned long int n);

/*  Macro for selecting the mixed-binary method.                              */
#define TMPL_GCD_METHOD tmpl_ULong_GCD_Mixed_Binary

/*  With some architectures / compilers the binary algorithm is faster.       */
#elif TMPL_GCD_ALGORITHM == TMPL_GCD_ALGORITHM_BINARY

/******************************************************************************
 *                          Binary / Stein Algorithm                          *
 ******************************************************************************/

/*  Forward declaration / function prototype for the binary function.         */
extern unsigned long int
tmpl_ULong_GCD_Binary(const unsigned long int m, const unsigned long int n);

/*  Macro for selecting the binary method.                                    */
#define TMPL_GCD_METHOD tmpl_ULong_GCD_Binary

/*  The Euclidean algorithm is often a bit slower than the binary algorithm.  *
 *  It can still be quite fast, and there may be benefits to using it.        */
#elif TMPL_GCD_ALGORITHM == TMPL_GCD_ALGORITHM_EUCLIDEAN

/******************************************************************************
 *                            Euclidean Algorithm                             *
 ******************************************************************************/

/*  Forward declaration / function prototype for the Euclidean function.      */
extern unsigned long int
tmpl_ULong_GCD_Euclidean(const unsigned long int m, const unsigned long int n);

/*  Macro for selecting the Euclidean method.                                 */
#define TMPL_GCD_METHOD tmpl_ULong_GCD_Euclidean

/*  The Naive algorithm is always the slowest. Only use this for experiment.  */
#else

/******************************************************************************
 *                         Naive / By-Hand Algorithm                          *
 ******************************************************************************/

/*  Forward declaration / function prototype for the Naive function.          */
extern unsigned long int
tmpl_ULong_GCD_Naive(const unsigned long int m, const unsigned long int n);

/*  Macro for selecting the Naive method.                                     */
#define TMPL_GCD_METHOD tmpl_ULong_GCD_Naive

#endif
/*  End of #if TMPL_GCD_ALGORITHM == TMPL_GCD_ALGORITHM_MIXED_BINARY.         */

/*  Function for computing the GCD of two unsigned integers.                  */
TMPL_INLINE_DECL
unsigned long int
tmpl_ULong_GCD(const unsigned long int m, const unsigned long int n)
{
    return TMPL_GCD_METHOD(m, n);
}
/*  End of tmpl_ULong_GCD.                                                    */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_GCD_METHOD

#endif
/*  End of include guard.                                                     */
