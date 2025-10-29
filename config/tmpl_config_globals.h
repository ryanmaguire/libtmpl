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
 *                             tmpl_config_do_sqrt                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides globals and enum definitions for the config.c file.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 29, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_GLOBALS_H
#define TMPL_CONFIG_GLOBALS_H

/*  Number of bits in char. char is not allowed to have padding, so all bits  *
 *  are used. This fact can be used to determine this value.                  */
static unsigned int tmpl_number_of_bits_in_uchar = 0U;
static unsigned int tmpl_uchar_width = 0U;
static unsigned int tmpl_uchar_width_is_known = 0U;

/*  The other integer data types are allowed to have padding. These numbers   *
 *  represent the number of unpadded bits.                                    */
static unsigned int tmpl_number_of_bits_in_ushort = 0U;
static unsigned int tmpl_ushort_width = 0U;
static unsigned int tmpl_ushort_width_is_known = 0U;

static unsigned int tmpl_number_of_bits_in_uint = 0U;
static unsigned int tmpl_uint_width = 0U;
static unsigned int tmpl_uint_width_is_known = 0U;

static unsigned int tmpl_number_of_bits_in_ulong = 0U;
static unsigned int tmpl_ulong_width = 0U;
static unsigned int tmpl_ulong_width_is_known = 0U;

#ifdef TMPL_LONG_LONG_IS_AVAILABLE
static unsigned int tmpl_number_of_bits_in_ullong = 0U;
static unsigned int tmpl_ullong_width = 0U;
static unsigned int tmpl_ullong_width_is_known = 0U;
#endif

static unsigned int tmpl_all_widths_are_known = 0U;

static unsigned int tmpl_has_32_bit_uint = 0U;
static unsigned int tmpl_has_64_bit_uint = 0U;

/*  There are 4 possibilities for endianness. Little endian is the most       *
 *  common, big endian is a bit rarer, mixed endian is almost non-existent,   *
 *  and unknown means the function could not determine anything.              */
enum tmpl_integer_endianness {
    tmpl_integer_little_endian,
    tmpl_integer_big_endian,
    tmpl_integer_mixed_endian,
    tmpl_integer_unknown_endian
};

static enum tmpl_integer_endianness tmpl_endian = tmpl_integer_unknown_endian;
static unsigned int tmpl_int_endianness_has_been_checked = 0U;

/*  IEEE-754 does not specify the endianness of float. It is usually the      *
 *  same as the endianness of integers, but this is not required. Unknown     *
 *  is returned if the function could not determine how float is implemented. */
enum tmpl_float_type {
    tmpl_float_little_endian,
    tmpl_float_big_endian,
    tmpl_float_unknown_endian
};

/*  Similarly, IEEE-754 does not specify endianness for double precision.     */
enum tmpl_double_type {
    tmpl_double_little_endian,
    tmpl_double_big_endian,
    tmpl_double_unknown_endian
};

/*  Long double is less standardized. There are many possible implementations.*
 *  This includes 64-bit, 80-bit, 96-bit, and 128-bit. The long double        *
 *  function below will attempt to determine which of these, if any, is       *
 *  implemented. Unknown is returned if this can't be determined.             */
enum tmpl_ldouble_type {
    tmpl_ldouble_64_bit_little_endian,
    tmpl_ldouble_64_bit_big_endian,
    tmpl_ldouble_96_bit_extended_little_endian,
    tmpl_ldouble_96_bit_extended_big_endian,
    tmpl_ldouble_128_bit_extended_little_endian,
    tmpl_ldouble_128_bit_extended_big_endian,
    tmpl_ldouble_128_bit_quadruple_little_endian,
    tmpl_ldouble_128_bit_quadruple_big_endian,
    tmpl_ldouble_128_bit_doubledouble_little_endian,
    tmpl_ldouble_128_bit_doubledouble_big_endian,
    tmpl_ldouble_unknown
};

static enum tmpl_float_type tmpl_float_rep = tmpl_float_unknown_endian;
static enum tmpl_double_type tmpl_double_rep = tmpl_double_unknown_endian;
static enum tmpl_ldouble_type tmpl_ldouble_rep = tmpl_ldouble_unknown;

static unsigned int tmpl_float_type_has_been_checked = 0U;
static unsigned int tmpl_double_type_has_been_checked = 0U;
static unsigned int tmpl_ldouble_type_has_been_checked = 0U;

#endif
/*  End of include guard.                                                     */
