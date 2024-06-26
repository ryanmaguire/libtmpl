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
 *                            tmpl_factorial_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the factorial of an integer.                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Factorial                                                  *
 *  Purpose:                                                                  *
 *      Computes n!, the factorial of an integer.                             *
 *  Arguments:                                                                *
 *      n (unsigned int):                                                     *
 *          A non-negative integer.                                           *
 *  Output:                                                                   *
 *      n_factorial (float):                                                  *
 *          The factorial of the input.                                       *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Use a lookup table for 0 <= n <= 33. Return infinity otherwise.   *
 *      Error:                                                                *
 *          Based on integer values 0 <= x <= 33.                             *
 *              max relative error: 3.7863716668571940E-08                    *
 *              rms relative error: 2.3007473207311396E-09                    *
 *              max absolute error: 2.5720946892867613E+29                    *
 *              rms absolute error: 7.3642156714739730E+27                    *
 *          Values were computed using arbitrary precision libraries.         *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          If the input is smaller than the size of the lookup table, return *
 *          the corresponding value. Otherwise set y to the largest element   *
 *          in the table and iteratively compute y = y * m for increasing m.  *
 *      Error:                                                                *
 *          Based on integer values 0 <= x <= 33.                             *
 *              max relative error: 3.7863716668571940E-08                    *
 *              rms relative error: 2.3007473207311396E-09                    *
 *              max absolute error: 2.5720946892867613E+29                    *
 *              rms absolute error: 7.3642156714739730E+27                    *
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
#define PEAK (sizeof(tmpl_float_factorial_table) / sizeof(float))

/*  With IEEE-754 we know exactly when n! will overflow and can compute using *
 *  a lookup table. Check for this.                                           */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Computes the factorial of a non-negative integer at single precision.     */
float tmpl_Float_Factorial(unsigned int n)
{
    /*  The factorial function grows very quickly. For large enough n this    *
     *  will overflow. For integers larger than the size of the array return  *
     *  infinity.                                                             */
    if (n >= PEAK)
        return TMPL_INFINITYF;

    /*  Otherwise, n! has been pre-computed in a lookup table. Use this.      */
    return tmpl_float_factorial_table[n];
}
/*  End of tmpl_Float_Factorial.                                             */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Computes the factorial of a non-negative integer at single precision.     */
float tmpl_Float_Factorial(unsigned int n)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float factorial;
    unsigned int k;

    /*  If the input does not exceed the size of the table, return the value  *
     *  of the corresponding entry in the lookup table.                       */
    if (n < PEAK)
        return tmpl_float_factorial_table[n];

    /*  Otherwise start the computation at the largest value in the table.    */
    factorial = tmpl_float_factorial_table[PEAK - 1U];

    /*  Compute n! via n! = 1*2*3*...*(n-1)*n, doing this iteratively.        */
    for (k = PEAK; k <= n; ++k)
        factorial *= (float)k;

    return factorial;
}
/*  End of tmpl_Float_Factorial.                                              */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

/*  Undefine this in case someone wants to #include this file.                */
#undef PEAK
