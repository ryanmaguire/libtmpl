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
 *                       tmpl_config_det_int_endianness                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Detects the endianness of integer data types.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_det_int_endianness                                               *
 *  Purpose:                                                                  *
 *      Determines the endianness of unsigned integers.                       *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      endianness (enum tmpl_integer_endianness):                            *
 *          enum representing integer endianness.                             *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_uchar_width.h:                                    *
 *              tmpl_det_uchar_width:                                         *
 *                  Computes the number of bits in unsigned char.             *
 *  Method:                                                                   *
 *      Create the number 76543210 (or n-1 ... 0 where n is the number of     *
 *      bytes in either unsigned long or unsigned long long) and type-pun     *
 *      this with a char array. Reading the zeroth element will tell us the   *
 *      endianness of the system.                                             *
 *  Notes:                                                                    *
 *      1.) The C99 standard (and higher) explicitly allow type punning via   *
 *          unions. See section 6.5.2.3 of the C99, C11, and C18 drafts, and  *
 *          section 6.5.2.4 of the C23 draft.                                 *
 *      2.) The C89 standard states that type punning is implementation       *
 *          defined. It is not undefined behavior. See section 6.2.3.2 of the *
 *          C89 draft.                                                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config_globals.h:                                                *
 *          Header file with all of the globals used by config.c.             *
 *  2.) tmpl_config_det_uchar_width.h:                                        *
 *          Provides the tmpl_det_uchar_width function.                       *
 *  3.) tmpl_cast.h:                                                          *
 *          Provides the TMPL_CAST macro.                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/08: Ryan Maguire                                                  *
 *      Moved function to its own file.                                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_DET_INT_ENDIANNESS_H
#define TMPL_CONFIG_DET_INT_ENDIANNESS_H

/*  TMPL_CAST macro found here, used for casting with C vs. C++ compatibility.*/
#include "../include/compat/tmpl_cast.h"

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  Function for computing the number of bits in unsigned char found here.    */
#include "tmpl_config_det_uchar_width.h"

/*  There are 4 possibilities for endianness. Little endian is the most       *
 *  common, big endian is a bit rarer, mixed endian is almost non-existent,   *
 *  and unknown means the function could not determine anything.              */
enum tmpl_integer_endianness {
    tmpl_integer_little_endian,
    tmpl_integer_big_endian,
    tmpl_integer_mixed_endian,
    tmpl_integer_unknown_endian
};

/*  We want to use the largest integer data type available. If long long      *
 *  support is available, use this. Otherwise create a typedef for long.      */
#ifdef TMPL_LONG_LONG_IS_AVAILABLE
typedef unsigned long long int tmpl_uint;
#else
typedef unsigned long int tmpl_uint;
#endif

/*  Function for determining the endianness of integer data types.            */
static enum tmpl_integer_endianness tmpl_det_int_endianness(void)
{
    /*  We'll use a union between a tmpl_uint integer and an unsigned char    *
     *  array with as many elements as there are bytes in an tmpl_uint.       *
     *  tmpl_uint is either unsigned long int or unsigned long long int, so   *
     *  this is usually either 8 (unix-based, i.e. GNU, Linux, FreeBSD,       *
     *  macOS), or 4 (Microsoft Windows), but the value is not specified in   *
     *  the C standard.                                                       */
    union {
        tmpl_uint n;
        unsigned char arr[sizeof(tmpl_uint)];
    } e;

    /*  n is for indexing and power keeps track of the power of an integer.   */
    tmpl_uint n, power;

    /*  Avoid implicit conversion. Create constants for 0 and 1 of the same   *
     *  type as n and power, which is tmpl_uint.                              */
    const tmpl_uint zero = TMPL_CAST(0, tmpl_uint);
    const tmpl_uint one = TMPL_CAST(1, tmpl_uint);

    /*  There is one, extremely rare (essentially unheard of), exceptional    *
     *  case that needs to be handled separately. If sizeof(tmpl_uint) = 1,   *
     *  then the char array will have one element, which is the same number   *
     *  as the tmpl_uint value. Because of this we would be unable to         *
     *  determine the endianness. If this is true, return unknown endian. I   *
     *  know of no systems where sizeof(unsigned long int) = 1, but the ISO   *
     *  C90 standard does not specify that this is impossible, so we do this  *
     *  for the sake of portability.                                          */
    if (sizeof(tmpl_uint) == 1)
        return tmpl_integer_unknown_endian;

    /*  We need to use the global value tmpl_uchar_width. Check that it has   *
     *  been computed already. If not, compute it.                            */
    if (!tmpl_uchar_width_is_known)
        tmpl_det_uchar_width();

    /*  The idea is as follows. Create the integer 76543210, store this in    *
     *  the tmpl_uint part of our union, and then check the array part to see *
     *  which element is 0. This would work if computers are base 10, but     *
     *  they usually use base 2, base 8, or base 16. Letting N be the base,   *
     *  we'll store the number 7*N^7 + 6*N^6 + ... + 2*N^2 + 1*N + 0. The     *
     *  array will then be:                                                   *
     *                                                                        *
     *      ---------------------------------                                 *
     *      | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |                                 *
     *      ---------------------------------                                 *
     *                                                                        *
     *  This is assuming sizeof(tmpl_uint) = 8. If it is some other value,    *
     *  the array will be 0 up to that number. We'll start by initializing    *
     *  the tmpl_uint part of the union to 0.                                 */
    e.n = zero;

    /*  We need to set power to 2^(number of bits in a byte). This number is  *
     *  found in tmpl_uchar_width. We're going to write out the number as     *
     *  7 * power^7 + 6 * power^6 + ... + 2 * power^2 + power + 0. If we      *
     *  somehow had a base-10 computer, this would be                         *
     *  7*10^7 + 6*10^6 + ... + 2*10^2 + 1*10 + 0 = 76543210. We want this in *
     *  base 2^tmpl_uchar_width. We compute 2^tmpl_uchar_width quickly using  *
     *  bitwise operators. 1 << N is the number 1000...000 in binary with N   *
     *  0's. This would be the number 2^N in decimal, which is what we want.  *
     *  We compute 2^tmpl_uchar_width via 1 << tmpl_uchar_width.              */
    power = one << tmpl_uchar_width;

    /*  Write out 76543210 in base 2^tmpl_uchar_width by adding.              */
    for (n = one; n < sizeof(tmpl_uint); ++n)
    {
        e.n += n * power;

        /*  From power^k we can get power^(k+1) by shifting the "decimal"     *
         *  tmpl_uchar_width to the right. If we have 100 and want 1000, we'd *
         *  write 100.00, shift the decimal to the right, and get 1000.0.     *
         *  Writing pow = pow << tmpl_uchar_width is the base                 *
         *  2^tmpl_uchar_width equivalent.                                    */
        power = power << tmpl_uchar_width;
    }

    /*  We now have 76543210 in the array part of the union (or n-1...210 if  *
     *  sizeof(tmpl_uint) = n). If the zeroth entry of the array is 0, we     *
     *  have little endian. If it is n-1, we have big endian. Anything        *
     *  between 0 and n-1 is mixed endian, and any other result is unknown.   */
    if (e.arr[0] == 0)
        return tmpl_integer_little_endian;

    if (e.arr[0] == (sizeof(tmpl_uint) - 1))
        return tmpl_integer_big_endian;

    if (e.arr[0] < (sizeof(tmpl_uint) - 1))
        return tmpl_integer_mixed_endian;

    return tmpl_integer_unknown_endian;
}
/*  End of tmpl_det_int_endianness.                                           */

#endif
/*  End of include guard.                                                     */
