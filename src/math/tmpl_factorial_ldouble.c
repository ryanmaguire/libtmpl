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
 *                           tmpl_factorial_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the factorial of an integer.                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Factorial                                                *
 *  Purpose:                                                                  *
 *      Computes n!, the factorial of an integer.                             *
 *  Arguments:                                                                *
 *      n (unsigned int):                                                     *
 *          A non-negative integer.                                           *
 *  Output:                                                                   *
 *      n_factorial (long double):                                            *
 *          The factorial of the input.                                       *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Use a lookup table for 0 <= n <= max. Return infinity otherwise.  *
 *          max depends on how long double is implemented. For 64-bit double  *
 *          and 128-bit double-double, max = 170. For 80-bit extended and     *
 *          128-bit quadruple, max = 1754.                                    *
 *      Error:                                                                *
 *          Based on integer values 0 <= x <= 1754.                           *
 *              max relative error: 1.0461307088864179E-16                    *
 *              rms relative error: 5.5641544376682720E-18                    *
 *              max absolute error: 6.7603681341259850E+289                   *
 *              rms absolute error: 3.8562089886859030E+287                   *
 *          Values were computed using arbitrary precision libraries.         *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          If the input is smaller than the size of the lookup table, return *
 *          the corresponding value. Otherwise set y to the largest element   *
 *          in the table and iteratively compute y = y * m for increasing m.  *
 *      Error:                                                                *
 *          Based on integer values 0 <= x <= 1754.                           *
 *              max relative error: 1.0461307088864179E-16                    *
 *              rms relative error: 5.5641544376682720E-18                    *
 *              max absolute error: 6.7603681341259850E+289                   *
 *              rms absolute error: 3.8562089886859030E+287                   *
 *          Values were computed using arbitrary precision libraries.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype and lookup table.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 18, 2022                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/05/13: Ryan Maguire                                                  *
 *      Added license and function description.                               *
 ******************************************************************************/

/*  Function prototype and lookup table provided here.                        */
#include <libtmpl/include/tmpl_math.h>

/*  Size of the lookup table. For the IEEE-754 version this is the largest    *
 *  integer n such that (n-1)! will not overflow.                             */
#define PEAK (sizeof(tmpl_ldouble_factorial_table) / sizeof(long double))

/*  With IEEE-754 we know exactly when n! will overflow and can compute using *
 *  a lookup table. Check for this.                                           */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Computes the factorial of a non-negative integer at long double precision.*/
long double tmpl_LDouble_Factorial(unsigned int n)
{
    /*  The factorial function grows very quickly. For large enough n this    *
     *  will overflow. For integers larger than the size of the array return  *
     *  infinity.                                                             */
    if (n >= PEAK)
        return TMPL_INFINITYL;

    /*  Otherwise, n! has been pre-computed in a lookup table. Use this.      */
    return tmpl_ldouble_factorial_table[n];
}
/*  End of tmpl_LDouble_Factorial.                                            */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Computes the factorial of a non-negative integer at long double precision.*/
long double tmpl_LDouble_Factorial(unsigned int n)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double factorial;
    unsigned int k;

    /*  If the input does not exceed the size of the table, return the value  *
     *  of the corresponding entry in the lookup table.                       */
    if (n < PEAK)
        return tmpl_ldouble_factorial_table[n];

    /*  Otherwise start the computation at the largest value in the table.    */
    factorial = tmpl_ldouble_factorial_table[PEAK - 1U];

    /*  Compute n! via n! = 1*2*3*...*(n-1)*n, doing this iteratively.        */
    for (k = PEAK; k <= n; ++k)
        factorial *= (long double)k;

    return factorial;
}
/*  End of tmpl_LDouble_Factorial.                                            */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

/*  Undefine this in case someone wants to #include this file.                */
#undef PEAK
