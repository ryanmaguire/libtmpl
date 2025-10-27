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

#endif
