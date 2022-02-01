/******************************************************************************
 *                                 LICENSE                                    *
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
 *                                tmpl_bytes                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide tools for swapping bytes of char pointers and for determining *
 *      the endianness of your platform. This is useful for reading binary    *
 *      files, but also learning about how computers work and store numbers.  *
 *                                                                            *
 *  Notes:                                                                    *
 *      This file is a fork of the bytes library I wrote for rss_ringoccs.    *
 *      rss_ringoccs is also released under the GPL 3.                        *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  None.                                                                     *
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
 *                                EXAMPLES                                    *
 ******************************************************************************
 *  Examples of all of the functions can be found in:                         *
 *      libtmpl/examples/bytes_examples/                                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 1, 2021                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2021/01/14: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/01: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs and edited.                                  *
 *  2021/02/02: Ryan Maguire                                                  *
 *      Soft freeze for libtmpl alpha release.                                *
 *  2021/02/17: Ryan Maguire                                                  *
 *      Updated doc-strings for functions.                                    *
 *  2021/04/05: Ryan Maguire                                                  *
 *      Added source code and example code locations to comments.             *
 *  2021/04/30: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code/comments. No  *
 *      more changes to comments or code unless something breaks.             *
 *  2022/01/24: Ryan Maguire                                                  *
 *      Added extern "C" statement for C++ compatibility.                     *
 *  2022/02/01: Ryan Maguire                                                  *
 *      Getting rid of -Wreserved-identifier warnings with clang.             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_BYTES_H
#define TMPL_BYTES_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/*  Data type for determining the endianness of your platform.                */
typedef enum tmpl_Endian_Def {
    tmpl_UnknownEndian,
    tmpl_LittleEndian,
    tmpl_MixedEndian,
    tmpl_BigEndian
} tmpl_Endian;

/*  This part of libtmpl is used in the rss_ringoccs library for reading RSR  *
 *  binary files. To read those files requires your platform to be either     *
 *  little-endian or big-endian. That is, there's no attempts to mess with    *
 *  mixed-endian systems. All of the functions defined in this header file    *
 *  should work on mixed-endian, but have not been tested on such platforms.  */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Determine_Endianness                                             *
 *  Purpose:                                                                  *
 *      Determines the endianness of your platform.                           *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      endianness (tmpl_Endian):                                             *
 *          A tmpl_Endian data type whose value corresponds to the            *
 *          endianness of your system.                                        *
 *  Notes:                                                                    *
 *      This code needs sizeof(unsigned long int) > 1, unless the C99         *
 *      standard (or higher) is supported, in which case it is needed that    *
 *      sizeof(unsigned long long int) > 1. This is almost always true. On    *
 *      most unix-like platforms (GNU, Linux, FreeBSD, macOS)                 *
 *      sizeof(unsigned long int) = 8, and on Microsoft Windows we find       *
 *      sizeof(unsigned long int) = 4. If both long and long long have sizeof *
 *      equal to 1, this function returns tmpl_UnknownEndian.                 *
 *  Source Code:                                                              *
 *      libtmpl/src/bytes/tmpl_determine_endianness.c                         *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes_examples/tmpl_determine_endianness_example.c   *
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
 *  Source Code:                                                              *
 *      libtmpl/src/bytes/tmpl_swap_bytes.c                                   *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes_examples/tmpl_swap_bytes_example.c             *
 *  Tests:                                                                    *
 *      libtmpl/tests/bytes_tests/tmpl_swap_bytes_unit_test_001.c             *
 ******************************************************************************/
extern void tmpl_Swap_Bytes(char *ptr1, char *ptr2);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Swap_Most_Significant_Bit_2                                      *
 *  Purpose:                                                                  *
 *      Changes the endianness of a data type that is two chars long. This    *
 *      is usually a "short". Similar functions are provided for 4 and 8.     *
 *  Arguments:                                                                *
 *      ptr (char *):                                                         *
 *          A pointer to a char array.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/bytes/tmpl_swap_most_significant_bit_2.c                  *
 *      libtmpl/src/bytes/tmpl_swap_most_significant_bit_4.c                  *
 *      libtmpl/src/bytes/tmpl_swap_most_significant_bit_8.c                  *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes/tmpl_swap_most_significant_bit_2_example.c     *
 *      libtmpl/examples/bytes/tmpl_swap_most_significant_bit_2_alt_example.c *
 *      libtmpl/examples/bytes/tmpl_swap_most_significant_bit_4_example.c     *
 *      libtmpl/examples/bytes/tmpl_swap_most_significant_bit_8_example.c     *
 *  Tests:                                                                    *
 *      libtmpl/tests/bytes_tests/                                            *
 *          tmpl_swap_most_significant_bit_2_unit_test_001.c                  *
 *          tmpl_swap_most_significant_bit_4_unit_test_001.c                  *
 *          tmpl_swap_most_significant_bit_8_unit_test_001.c                  *
 ******************************************************************************/
extern void tmpl_Swap_Most_Significant_Bit_2(char *ptr);
extern void tmpl_Swap_Most_Significant_Bit_4(char *ptr);
extern void tmpl_Swap_Most_Significant_Bit_8(char *ptr);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */

