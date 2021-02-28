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
 *                               tmpl_ieee754                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains tools for manipulating floating point variables for          *
 *      platforms using the IEEE754 format (most do in 2021). All of this is  *
 *      experimental and mostly for the sake of learning, and is not directly *
 *      required for libtmpl. Uses of this header file include accurate       *
 *      and fast logarithmic functions, square roots, and more.               *
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

/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_IEEE754_H__
#define __TMPL_IEEE754_H__

#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_endianness.h>

/******************************************************************************
 *  For a non-negative integer that is less than 2^64, we can store the       *
 *  number in a computer using binary. That is, 64 bits of zeroes and ones    *
 *  which represent our ordinal base-10 integer. With this we can store every *
 *  integer between 0 and 2^64-1.                                             *
 *                                                                            *
 *    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx        *
 *    ----------------------------------------------------------------        *
 *                              Integer Part                                  *
 *                                                                            *
 *  If we want to represent a "signed" integer, one that can be negative or   *
 *  positive, or zero, we require more information. The solution is to        *
 *  sacrifice one of the 64 bits and reserve it as the "sign." In doing so we *
 *  we can now store every integer between -(2^63-1) and +(2^63-1). Oddly     *
 *  enough, the difference between these two numbers is 2^64-2, not 2^64-1.   *
 *  In reserving a bit for the sign, we now have two zeroes. A "positive"     *
 *  zero and a "negative" zero, These are called "signed zeroes." When using  *
 *  these, compilers treat them nearly the same, and testing -0 == +0 return  *
 *  True.                                                                     *
 *                                                                            *
 *    x xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx       *
 *    - ---------------------------------------------------------------       *
 *  Sign                        Integer Part                                  *
 *                                                                            *
 *  Note, the left-most bit does not need to be the signed bit. This will be  *
 *  determined by the "endianness" or your system. To store a real number, or *
 *  to at least approximate, one might guess that we simply insert a point    *
 *  half-way and treat this as a decimal:                                     *
 *                                                                            *
 *    x xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx      *
 *    - -------------------------------- -------------------------------      *
 *  Sign         Integer Part                      Fractional Part            *
 *                                                                            *
 *  This turns out to be a very bad idea since we cannot represent very many  *
 *  numbers with this. The largest number is now 2^32-1, or roughly 4 billion.*
 *  Any larger number would be treated as infinity. And the other hand, we    *
 *  only have about 9 significant digits past the decimal point (in decimal)  *
 *  whereas many applications need up to 16. The solution is the IEEE754      *
 *  Floating Point Format. It represents a real number as follows:            *
 *                                                                            *
 *    s eeeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx      *
 *    - ----------- ----------------------------------------------------      *
 *  Sign  Exponent                     Fraction                               *
 *                                                                            *
 *  The idea is to use scientific notation in binary, writing a number as     *
 *                                                                            *
 *        y = s * 1.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx_2    *
 *              * 2^(eeeeeeeeeee_2 - 1111111111_2)                            *
 *                                                                            *
 *  Where _2 indicates this is all base 2. This "magic number" being          *
 *  subtracted is 2^10-1 = 1023.                                              *
 *                                                                            *
 *  Since we know the first digit in scientific notation is always 1, we don't*
 *  need to waste a bit and can store 53 bits worth of the fractional part    *
 *  using just 52 bits. The eeeeeeeeeee - 1023 needs an explaination. We want *
 *  to store fractional numbers between 0 and 1 and so we need negative       *
 *  exponents. We could reserve a second bit for the sign of the exponent,    *
 *  but the standard is to just subtract 2^32-1 from the exponent. The last   *
 *  thing is to say that all zeroes, or all zeros plus the sign bit,          *
 *  represents zero and not +/- 10^-1023.                                     *
 *                                                                            *
 *  Now for some examples:                                                    *
 *    0 00000000001 0000000000000000000000000000000000000000000000000000      *
 *      = 2^(1-1023)                                                          *
 *      = 2^-1022                                                             *
 *      ~ 10^-308                                                             *
 *                                                                            *
 *    This is the smallest positive number.                                   *
 *                                                                            *
 *    0 11111111111 0000000000000000000000000000000000000000000000000000      *
 *      = 2^1023                                                              *
 *      ~ 10^308                                                              *
 *      = Infinity (according to the standard).                               *
 *                                                                            *
 *    Seting 2^1023 to infinity means we can reserve a number of Not-a-Number *
 *    (NaN) as follows:                                                       *
 *                                                                            *
 *    0 11111111111 1111111111111111111111111111111111111111111111111111      *
 *      = NaN                                                                 *
 *                                                                            *
 *    This is useful for log(-1) or sqrt(-1) or 0.0/0.0.                      *
 *                                                                            *
 *    0 01111111111 0000000000000000000000000000000000000000000000000000      *
 *      = 2^(1023 - 1023)                                                     *
 *      = 2^0                                                                 *
 *      = 1                                                                   *
 ******************************************************************************/


/*  To access binary representation of a floating point number, we use unions.*
 *  Unions allows us to have different data types share the same block of     *
 *  memory. If we have a union of a floating point and an integer, and then   *
 *  set the floating point part to some number, then when we try to access the*
 *  integer part it will already have its bits set (They'll be set by the     *
 *  floating point value). The resulting integer is the actual binary value   *
 *  corresponding to the IEEE754 format.                                      */

/*  Data type for a 32-bit floating point number. This is assumed to          *
 *  correspond to the float data type. Note that float is assumed to be 32    *
 *  bits. If your compiler supports the IEEE 754 format, it is.               */
typedef union _tmpl_IEE754_Word32 {
    float real;
    tmpl_uint32 integer;
} tmpl_IEEE754_Word32;

/*  Data type for a 64-bit floating point number. This is assumed to          *
 *  correspond to the double data type.                                       */
#if defined(__TMPL_ENDIAN__) && __TMPL_ENDIAN__ == __TMPL_BIG_ENDIAN__

typedef union _tmpl_IEE754_Word64 {
    double real;
    struct {
        tmpl_int32 most_significant_word;
        tmpl_int32 least_significant_word;
    } parts;
    struct {
        tmpl_uint32 most_significant_word;
        tmpl_uint32 least_significant_word;
    } uparts;
	  tmpl_uint64 integer;
} tmpl_IEEE754_Word64;

#elif defined(__TMPL_ENDIAN__) &&  __TMPL_ENDIAN__ == __TMPL_LITTLE_ENDIAN__

typedef union _tmpl_IEE754_Word64 {
    double real;
    struct {
        tmpl_int32 least_significant_word;
        tmpl_int32 most_significant_word;
    } parts;
    struct {
        tmpl_uint32 least_significant_word;
        tmpl_uint32 most_significant_word;
    } uparts;
	  tmpl_uint64 integer;
} tmpl_IEEE754_Word64;

#else

#error "Unsupported endianness."

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Get_High_Word32                                                  *
 *  Purpose:                                                                  *
 *      Gets the "high word" of a 32-bit IEEE754 floating point number. This  *
 *      is just the binary value of the exponent part of the number.          *
 *      A 64 bit version is also provided.                                    *
 *  Arguments:                                                                *
 *      tmpl_IEE754_Word32 w:                                                 *
 *          A union for 32-bit float and 32-bit unsigned int.                 *
 *  Output:                                                                   *
 *      tmpl_uint32 high:                                                     *
 *          The numerical value of the high word of x.                        *
 ******************************************************************************/
extern tmpl_uint32
tmpl_Get_High_Word32(tmpl_IEEE754_Word32 w);

extern tmpl_uint32
tmpl_Get_High_Word64(tmpl_IEEE754_Word64 w);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Get_Low_Word32                                                   *
 *  Purpose:                                                                  *
 *      Gets the "low word" of a 32-bit IEEE754 floating point number. This   *
 *      is just the binary value of the fractional part of the number.        *
 *      A 64 bit version is also provided.                                    *
 *  Arguments:                                                                *
 *      tmpl_IEE754_Word32 w:                                                 *
 *          A union for 32-bit float and 32-bit unsigned int.                 *
 *  Output:                                                                   *
 *      tmpl_uint32 low:                                                      *
 *          The numerical value of the low word of x.                         *
 ******************************************************************************/
extern tmpl_uint32
tmpl_Get_Low_Word32(tmpl_IEEE754_Word32 w);

extern tmpl_uint64
tmpl_Get_Low_Word64(tmpl_IEEE754_Word64 w);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Get_Base_2_Exp32                                                 *
 *  Purpose:                                                                  *
 *      Gets the exponent of a 32-bit word. This is the value b such that the *
 *      number x is represented by 1.m * 2^b, m being the mantissa.           *
 *      tmpl_IEE754_Word32 w:                                                 *
 *          A union for 32-bit float and 32-bit unsigned int.                 *
 *  Output:                                                                   *
 *      tmpl_uint32 exp:                                                      *
 *          The numerical value of the exponential part of x in base 2.       *
 *  Source Code:                                                              *
 *      libtmpl/src/ieee754/tmpl_get_base_2_exp32.c                           *
 *      libtmpl/src/ieee754/tmpl_get_base_2_exp64.c                           *
 ******************************************************************************/
extern tmpl_int32
tmpl_Get_Base_2_Exp32(tmpl_IEEE754_Word32 w);

extern tmpl_int32
tmpl_Get_Base_2_Exp64(tmpl_IEEE754_Word64 w);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Get_Mantissa32                                                   *
 *  Purpose:                                                                  *
 *      Gets the mantissa of a 32-bit word. This is the value 1.m such that   *
 *      the number x is represented by 1.m * 2^b, b being the exponent.       *
 *      tmpl_IEE754_Word32 w:                                                 *
 *          A union for 32-bit float and 32-bit unsigned int.                 *
 *  Output:                                                                   *
 *      float mantissa:                                                       *
 *          The numerical value of the mantissa of x.                         *
 ******************************************************************************/
extern float
tmpl_Get_Mantissa32(tmpl_IEEE754_Word32 w);

extern double
tmpl_Get_Mantissa64(tmpl_IEEE754_Word64 w);

#endif
/*  End of include guard.                                                     */

