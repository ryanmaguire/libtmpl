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
 *                                tmpl_random                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for generating pseudo-random numbers.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_limits.h:                                                        *
 *          Header file containing sizes of int and long.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 1, 2024                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_RANDOM_H
#define TMPL_RANDOM_H

/*  Macros for probing the size of integer data types.                        */
#include <libtmpl/include/tmpl_limits.h>

/*  For the sake of portability, probe the size of unsigned int.              */
#if TMPL_UINT_BIT >= 64

/*  64-bit Mersenne twister with period 2^19937 - 1. The parameters are:      *
 *      width = 64                                                            *
 *      degree of recurrence = 312                                            *
 *      middle word size = 156                                                *
 *      separation point = 31                                                 */
typedef struct tmpl_UintMersenneTwisterStateType {
    unsigned int array[312];
    unsigned int index;
    unsigned int seed;
} tmpl_UIntMersenneTwisterState;

/*  unsigned int is commonly 32-bits on modern systems.                       */
#elif TMPL_UINT_BIT >= 32

/*  32-bit Mersenne twister with period 2^19937 - 1. The parameters are:      *
 *      width = 32                                                            *
 *      degree of recurrence = 624                                            *
 *      middle word size = 397                                                *
 *      separation point = 31                                                 */
typedef struct tmpl_UintMersenneTwisterStateType {
    unsigned int array[624];
    unsigned int index;
    unsigned int seed;
} tmpl_UIntMersenneTwisterState;

/*  The C standard requires int to be at least 16-bits.                       */
#else

/*  16-bit Mersenne twister with period 2^19937 - 1. The parameters are:      *
 *      width = 16                                                            *
 *      degree of recurrence = 1247                                           *
 *      middle word size = 623                                                *
 *      separation point = 15                                                 */
typedef struct tmpl_UintMersenneTwisterStateType {
    unsigned int array[1247];
    unsigned int index;
    unsigned int seed;
} tmpl_UIntMersenneTwisterState;

#endif
/*  End of 64-bit vs. 32-bit vs. 16-bit integers.                             */

/*  For the sake of portability, probe the size of unsigned long.             */
#if TMPL_ULONG_BIT >= 64

/*  64-bit Mersenne twister with period 2^19937 - 1. The parameters are:      *
 *      width = 64                                                            *
 *      degree of recurrence = 312                                            *
 *      middle word size = 156                                                *
 *      separation point = 31                                                 */
typedef struct tmpl_ULongMersenneTwisterStateType {
    unsigned long int array[312];
    unsigned long int index;
    unsigned long int seed;
} tmpl_ULongMersenneTwisterState;

/*  Unsigned long is required to be at least 32 bits.                         */
#else

/*  32-bit Mersenne twister with period 2^19937 - 1. The parameters are:      *
 *      width = 32                                                            *
 *      degree of recurrence = 624                                            *
 *      middle word size = 397                                                *
 *      separation point = 31                                                 */
typedef struct tmpl_ULongMersenneTwisterStateType {
    unsigned long int array[624];
    unsigned long int index;
    unsigned long int seed;
} tmpl_ULongMersenneTwisterState;

#endif
/*  End of 32-bit vs 64-bit unsigned long.                                    */

extern void
tmpl_UIntMersenneTwisterState_Init(tmpl_UIntMersenneTwisterState * const state,
                                   const unsigned int seed);

extern unsigned int
tmpl_UInt_MersenneTwister(tmpl_UIntMersenneTwisterState * const state);

#endif
/*  End of include guard.                                                     */
