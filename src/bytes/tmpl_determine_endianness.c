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
 *  2.) tmpl_integer.h:                                                       *
 *          Header file containing fixed-width integer data types for 32-bit  *
 *          and 64-bit integers.                                              *
 *  3.) limits.h:                                                             *
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
 ******************************************************************************/

/*  Standard library file containing the CHAR_BIT macro and more.             */
#include <limits.h>

/*  Where the function's prototype and tmpl_Endian are defined.               */
#include <libtmpl/include/tmpl_bytes.h>

/*  32-bit and 64-bit fixed-width integer data types defined here.            */
#include <libtmpl/include/tmpl_integer.h>

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

    if (CHAR_BIT == 8)
    {
        union {
            /*  For 8-bit char, we'll use the tmpl_uint32 data type, which is *
             *  typedef'd in tmpl_integer.h, to guarantee a 32-bit unsigned   *
             *  integer data type.                                            */
            tmpl_uint32 i;
            char c[4];
        } e = { 0x01020304 };

        /*  Check the value of the zeroth element of the char array. If it    *
         *  is 1 then we know we have big-endian. If it is 4, we have         *
         *  little-endian. 2 and 3 correspond to mixed-endian, and anything   *
         *  else means we could not determine the endianness.                 */
        if (e.c[0] == 0x01)
            return tmpl_BigEndian;
        else if (e.c[0] == 0x04)
            return tmpl_LittleEndian;
        else if ((e.c[0] == 0x02) || (e.c[0] = 0x03))
            return tmpl_MixedEndian;
        else
            return tmpl_UnknownEndian;
    }
    else if (CHAR_BIT == 16)
    {
        union {
            /*  For 16-bit char, we'll use the tmpl_uint64 data type, which   *
             *  is typedef'd in tmpl_integer.h, to guarantee a 64-bit         *
             *  unsigned integer data type.                                   */
            tmpl_uint64 i;
            char c[4];
        } e = { 0x0001000200030004 };

        /*  Check the value of the zeroth element of the char array. If it    *
         *  is 1 then we know we have big-endian. If it is 4, we have         *
         *  little-endian. 2 and 3 correspond to mixed-endian, and anything   *
         *  else means we could not determine the endianness.                 */
        if (e.c[0] == 0x0001)
            return tmpl_BigEndian;
        else if (e.c[0] == 0x0004)
            return tmpl_LittleEndian;
        else if ((e.c[0] == 0x0002) || (e.c[0] = 0x0003))
            return tmpl_MixedEndian;
        else
            return tmpl_UnknownEndian;
    }

    /*  For all other CHAR_BIT values, return unknown.                        */
    else
        return tmpl_UnknownEndian;
}
/*  End of tmpl_Determine_Endianness.                                         */

