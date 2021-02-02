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
 *      is neither of these, libtmpl will fail to build.                      *
 *                                                                            *
 *      This file is a fork of the bytes library I wrote for rss_ringoccs.    *
 *      rss_ringoccs is also released under the GPL 3.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 1, 2021                                              *
 ******************************************************************************
 *                          Revision History                                  *
 ******************************************************************************
 *  2021/02/01: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs and edited.                                  *
 *  2021/02/02: Ryan Maguire:                                                 *
 *      Soft freeze for libtmpl alpha release.                                *
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
 *  binary files. For most functions if a platform is neither little-endian   *
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
 *      1.) This function assumes CHAR_BITS (defined in limits.h) is either   *
 *          8 or 16. If this is not true, libtmpl will fail to build.         *
 ******************************************************************************/
extern tmpl_Endian tmpl_Determine_Endianness(void);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Swap_Bytes                                                       *
 *  Purpose:                                                                  *
 *      Swaps the values of two char pointers.                                *
 *  Arguments:                                                                *
 *      ptr1 (char *):                                                        *
 *          The first pointer to a char.                                      *
 *      ptr2 (char *):                                                        *
 *          The second pointer to a char.                                     *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Swap_Bytes(char *ptr1, char *ptr2);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Swap_Most_Significant_Bit_2                                      *
 *  Purpose:                                                                  *
 *      Changes the endianness of a data type that is two chars long. This    *
 *      is usually a "short". Similarly functions are provided for 4 and 8.   *
 *  Arguments:                                                                *
 *      ptr (char *):                                                         *
 *          A pointer to a char array.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Swap_Most_Significant_Bit_2(char *ptr);
extern void tmpl_Swap_Most_Significant_Bit_4(char *ptr);
extern void tmpl_Swap_Most_Significant_Bit_8(char *ptr);

#endif
/*  End of include guard.                                                     */

