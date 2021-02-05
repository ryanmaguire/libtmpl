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
 *                           tmpl_get_low_word_64                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains source code for getting the "low word" of an IEEE754         *
 *      double precision 64-bit floating point number. This is the            *
 *      fractional part of the number.                                        *
 *  Method:                                                                   *
 *      Get the unsigned long int equivalent of the double-precision number   *
 *      and perform bitwise AND with the magic number                         *
 *      11111111111111111111111111111111111111111111111111_2                  *
 *          = 4503599627370495                                                *
 *  NOTES:                                                                    *
 *      While the code is written in ANSI C, this is NOT portable since it    *
 *      assumes various things. This part of the code makes the following     *
 *      assumptions (as stated, use of this code is only optional):           *
 *          1.) Your platform uses IEEE754 format for floating point          *
 *              arithmetic. Most modern computers do.                         *
 *          2.) You have 32-bit float and 64-bit double. This is NOT          *
 *              required by the C89/C90 standard, only minimum sizes are      *
 *              specified. 32-bit/64-bit single and double precision is the   *
 *              most common, but this can break portability.                  *
 *          3.) An unsigned long int has 64-bits, and an unsigned int has     *
 *              32-bits. This will most likely NOT be true on 32-bit systems, *
 *              especially 32-bit Microsoft Windows machines where unsigned   *
 *              long int is 32-bit. This assumption is true for 64-bit        *
 *              computers, including all of those libtmpl was tested on.      *
 *      Endianness shouldn't matter, however the code has only been tested on *
 *      Little Endian systems.                                                *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       January 22, 2021                                              *
 ******************************************************************************/
#include <libtmpl/include/tmpl_ieee754.h>

unsigned long tmpl_Get_Low_Word64(tmpl_IEE754_Word64 x)
{
    /*  x.real is a double. Use the union and look at x.integer. This will    *
     *  give us the actual binary value of x.real and we can pretend it is    *
     *  an unsigned long.                                                     */
	unsigned long out = x.integer;

    /*  Bit-wise AND can help us zero out the high-word. If we have:          *
     *  s eeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx     *
     *  - ---------- ----------------------------------------------------     *
     *                                                                        *
     *  And then perform bitwise AND with 4503599627370495, we get:           *
     *    s eeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   *
     *    0 0000000000 1111111111111111111111111111111111111111111111111111   *
     *  = 0 0000000000 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   *
     *                                                                        *
     *  In other words, we get the low-word.                                  */
	out = out & 4503599627370495UL;
	return out;
}
