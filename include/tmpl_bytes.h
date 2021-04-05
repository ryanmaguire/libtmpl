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
 *                                tmpl_bytes                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide tools for swapping bytes of char pointers and for determining *
 *      the endianness of your platform. This is useful for reading binary    *
 *      files, but also learning about how computers work and store numbers.  *
 *  NOTES:                                                                    *
 *      It is assumed a char is either 8 bits or 16 bits. This is probably    *
 *      the case for your computer. The only devices I know of where this may *
 *      not be true are hand-held calculators. So don't try to use            *
 *      libtmpl on those, I suppose. If CHAR_BITS (defined in limits.h)       *
 *      is neither of these, the tmpl_Determine_Endianness function will      *
 *      return tmpl_UnknownEndian. This part of the library is needed for use *
 *      of the ieee754 part of libtmpl. The ieee754 functions can be ignored  *
 *      by compiling without the ieee754 option set to false. If your device  *
 *      does have mixed-endian, or has CHAR_BITS not equal to 8 or 16, but    *
 *      you would still like to use libtmpl, raise an issue at:               *
 *        https://github.com/ryanmaguire/libtmpl/issues                       *
 *      I don't have such things, and will not meddle in emulation unless     *
 *      there's an actual need.                                               *
 *                                                                            *
 *      This file is a fork of the bytes library I wrote for rss_ringoccs.    *
 *      rss_ringoccs is also released under the GPL 3.                        *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 1, 2021                                              *
 ******************************************************************************
 *                          Revision History                                  *
 ******************************************************************************
 *  2021/01/14: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs.                   *
 *  2021/02/01: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs and edited.                                  *
 *  2021/02/02: Ryan Maguire                                                  *
 *      Soft freeze for libtmpl alpha release.                                *
 *  2021/02/17: Ryan Maguire                                                  *
 *      Updated doc-strings for functions.                                    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_BYTES_H__
#define __TMPL_BYTES_H__

/*  Data type for determining the endianness of your platform.                */
typedef enum {
    tmpl_UnknownEndian,
    tmpl_LittleEndian,
    tmpl_MixedEndian,
    tmpl_BigEndian
} tmpl_Endian;

/*  This part of libtmpl is used in the rss_ringoccs library for reading RSR  *
 *  binary files. For most functions, if a platform is neither little-endian  *
 *  nor big-endian, nothing can be done. That is, there's no attempts to mess *
 *  with mixed-endian systems. Personally, I've never come across such things.*/

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Determine_Endianness                                             *
 *  Purpose:                                                                  *
 *      Determines the endianness of your platform.                           *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      tmpl_Endian endianness:                                               *
 *          A tmpl_Endian data type whose value corresponds to the            *
 *          endianness of your system.                                        *
 *  NOTES:                                                                    *
 *      This function assumes CHAR_BITS (defined in limits.h) is either       *
 *      8 or 16. If this is not true, this function automatically             *
 *      returns tmpl_UnknownEndian.                                           *
 *  Source Code:                                                              *
 *      libtmpl/src/bytes/tmpl_determine_endianness.c                         *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes/tmpl_determine_endianness_example.c            *
 ******************************************************************************/
extern tmpl_Endian tmpl_Determine_Endianness(void);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Swap_Bytes                                                       *
 *  Purpose:                                                                  *
 *      Swaps the values of two char pointers.                                *
 *  Arguments:                                                                *
 *      char *ptr1:                                                           *
 *          The first pointer to a char.                                      *
 *      char *ptr2:                                                           *
 *          The second pointer to a char.                                     *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/bytes/tmpl_swap_bytes.c                                   *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes/tmpl_swap_bytes_example.c                      *
 ******************************************************************************/
extern void tmpl_Swap_Bytes(char *ptr1, char *ptr2);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Swap_Most_Significant_Bit_2                                      *
 *  Purpose:                                                                  *
 *      Changes the endianness of a data type that is two chars long. This    *
 *      is usually a "short". Similar functions are provided for 4 and 8.     *
 *  Arguments:                                                                *
 *      char *ptr:                                                            *
 *          A pointer to a char array.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/bytes/tmpl_swap_most_significant_bit_2.c                  *
 *      libtmpl/src/bytes/tmpl_swap_most_significant_bit_4.c                  *
 *      libtmpl/src/bytes/tmpl_swap_most_significant_bit_8.c                  *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes/tmpl_swap_most_significant_bit_2_example.c     *
 *      libtmpl/examples/bytes/tmpl_swap_most_significant_bit_4_example.c     *
 *      libtmpl/examples/bytes/tmpl_swap_most_significant_bit_8_example.c     *
 ******************************************************************************/
extern void tmpl_Swap_Most_Significant_Bit_2(char *ptr);
extern void tmpl_Swap_Most_Significant_Bit_4(char *ptr);
extern void tmpl_Swap_Most_Significant_Bit_8(char *ptr);

#endif
/*  End of include guard.                                                     */

