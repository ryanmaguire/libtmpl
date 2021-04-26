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
 *                        tmpl_determine_endianness                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for determining the endianness of a platform.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Determine_Endianness:                                            *
 *  Purpose:                                                                  *
 *      Determines the endianness of a platform. That is, whether the system  *
 *      is little-endian, big-endian, or mixed-endian.                        *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      endianness (tmpl_Endian):                                             *
 *          An enum data-type whose value corresponds to the endianness.      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a union data type between a char array with 4 elements and an     *
 *      unsigned integer data type that is 4 chars wide. This is usually a    *
 *      32-bit unsigned int, but may vary depending on your platform. We'll   *
 *      check the size of char with the CHAR_BIT macro from limits.h. If      *
 *      this is 8 (which it probably is), we'll use a tmpl_uint32 which is a  *
 *      32-bit unsigned integer data type from tmpl_integer.h. If CHAR_BIT is *
 *      16, we'll use a tmpl_uint64 data type. If CHAR_BIT is neither 8 nor   *
 *      16 (which is incredibly rare), we give up and return                  *
 *      tmpl_UnknownEndian.                                                   *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bytes.h:                                                         *
 *          Header where tmpl_Endian enum data type is defined, and           *
 *          where the function's prototype is given.                          *
 *  2.) limits.h:                                                             *
 *          Standard C library header file containing the CHAR_BIT macro      *
 *          which tells us how many bits are in one char.                     *
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
 *  Date:       February 11, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/01/14: Ryan Maguire                                                  *
 *      Created file (rss_ringoccs for Wellesley College).                    *
 *  2021/02/11: Ryan Maguire                                                  *
 *      Ported to libtmpl.                                                    *
 *  2021/02/11: Ryan Maguire                                                  *
 *      Added comments and license.                                           *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2021/04/10: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code/comments. No  *
 *      more changes to comments or code unless something breaks.             *
 *  2021/04/26:                                                               *
 *      Removed tmpl_integer.h from dependencies to improve portability.      *
 ******************************************************************************/

/*  Standard library file containing the CHAR_BIT macro and more.             */
#include <limits.h>

/*  Where the function's prototype and tmpl_Endian are defined.               */
#include <libtmpl/include/tmpl_bytes.h>
#include <stdio.h>

/******************************************************************************
 *                             The Basic Idea                                 *
 ******************************************************************************
 *  We'll use union to have an unsigned integer and a char array share the    *
 *  same memory. We'll then set the integer part to the hexidecimal number    *
 *  0x01020304 (for platforms with CHAR_BIT = 8). The char array will         *
 *  see this as follows for little-endian systems:                            *
 *                                                                            *
 *          -----------------------------                                     *
 *          |  04  |  03  |  02  |  01  |                                     *
 *          -----------------------------                                     *
 *                                                                            *
 *  Whereas on big-endian the char array will see:                            *
 *                                                                            *
 *          -----------------------------                                     *
 *          |  01  |  02  |  03  |  04  |                                     *
 *          -----------------------------                                     *
 *                                                                            *
 *  By checking the zeroth element of the array, we can determine endianness. *
 ******************************************************************************/

/*  Function for determining the endianness of the system.                    */
tmpl_Endian tmpl_Determine_Endianness(void)
{
    /*  Use the union C-keyword to create a data-type that has an unsigned    *
     *  integer and a char array consisting of four elements which share the  *
     *  same address in memory. By setting the integer portion to 0x01020304  *
     *  we can use the fact that the char array c is occupying the            *
     *  same address as the unsigned integer and interpret the value as a char*
     *  array. With this we can see if the zeroth value of the array is 01,   *
     *  02, 03, or 04. This will tell us if we have little-endian or          *
     *  big-endian, or the rarer mixed-endian.                                */
    union {
        unsigned long int n;
        unsigned char arr[sizeof(unsigned long int)];
    } e;

    unsigned long int n, pow;

    if (sizeof(unsigned long int) == 1)
        return tmpl_UnknownEndian;

    e.n = 0UL;
    pow = 1UL << CHAR_BIT;
    
    for (n = 1; n < sizeof(unsigned long int); ++n)
    {
        e.n += n * pow;
        pow  = pow << CHAR_BIT;
    }

    if (e.arr[0] == 0)
        return tmpl_LittleEndian;
    else if (e.arr[0] == sizeof(unsigned long int) - 1)
        return tmpl_BigEndian;
    else if ((0 < e.arr[0]) && (e.arr[0] < sizeof(unsigned long int) - 1))
        return tmpl_MixedEndian;
    else
        return tmpl_UnknownEndian;
}
/*  End of tmpl_Determine_Endianness.                                         */

