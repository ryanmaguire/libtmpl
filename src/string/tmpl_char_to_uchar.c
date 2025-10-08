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
 *                             tmpl_char_to_uchar                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Converts a character, like '6', to the number it represents, like 6.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Char_To_UChar                                                    *
 *  Purpose:                                                                  *
 *      Given a char c, convert it to a number, if applicable.                *
 *  Arguments:                                                                *
 *      c (char):                                                             *
 *          Any character.                                                    *
 *  Output:                                                                   *
 *      num (unsigned char):                                                  *
 *          The number that c represents.                                     *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      ASCII Version:                                                        *
 *          If the input represents a number, then the lowest four bits of it *
 *          are the numerical value it represents. Perform bitwise and with   *
 *          15 = 0b1111 = 0x0F to extract this value. Otherwise, return zero. *
 *      Portable Version:                                                     *
 *          Use a switch to check the argument, returning the numerical value *
 *          if it is a number, and zero otherwise.                            *
 *  Notes:                                                                    *
 *      If the input is not a number (like 'a'), the output is zero.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_HAS_ASCII is defined.                      *
 *  2.) tmpl_cast.h:                                                          *
 *          Provides a macro for casting with C vs. C++ compatibility.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 29, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/10/08: Ryan Maguire                                                  *
 *      Changed function and file name to be consistent with other routines.  *
 ******************************************************************************/

/*  TMPL_HAS_ASCII macro found here.                                          */
#include <libtmpl/include/tmpl_config.h>

/*  Forward declaration / function prototype, found in tmpl_string.h as well. */
extern unsigned char tmpl_Char_To_UChar(char c);

/*  The ASCII version is much more efficient.                                 */
#if TMPL_HAS_ASCII == 1

/******************************************************************************
 *                               ASCII Version                                *
 ******************************************************************************/

/*  TMPL_CAST macro found here, providing C vs. C++ compatibility.            */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Function for converting a character to a number.                          */
unsigned char tmpl_Char_To_UChar(char c)
{
    /*  If the input is not a number, simply return zero.                     */
    if (c > '9' || c < '0')
        return 0x00U;

    /*  In the ISO 8859-1 standard, the ASCII table has the following         *
     *  property (written in binary):                                         *
     *      0110000 = '0'                                                     *
     *      0110001 = '1'                                                     *
     *      0110011 = '2'                                                     *
     *          ...                                                           *
     *      0110111 = '7'                                                     *
     *      0111000 = '8'                                                     *
     *      0111001 = '9'                                                     *
     *          ...                                                           *
     *  If the input is a number, then the lower four bits are the binary     *
     *  representation of the number. Perform bitwise and with 15 = 0x0F to   *
     *  extract these bits and return the numerical value.                    */
    return TMPL_CAST(c & 0x0F, unsigned char);
}
/*  End of tmpl_Char_To_UChar.                                                */

#else
/*  Else for #if TMPL_HAS_ASCII == 1.                                         */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for converting a character to a number.                          */
unsigned char tmpl_Char_To_UChar(char c)
{
    /*  Lacking ASCII support, a switch works and is portable. GCC 15.2 with  *
     *  -O3 enabled optimizes this to the same number of instructions as the  *
     *  previous version (albeit, slightly different instructions).           */
    switch (c)
    {
        case '1':
            return 0x01U;
        case '2':
            return 0x02U;
        case '3':
            return 0x03U;
        case '4':
            return 0x04U;
        case '5':
            return 0x05U;
        case '6':
            return 0x06U;
        case '7':
            return 0x07U;
        case '8':
            return 0x08U;
        case '9':
            return 0x09U;
        default:
            return 0x00U;
    }
}
/*  End of tmpl_Char_To_UChar.                                                */

#endif
/*  End of #if TMPL_HAS_ASCII == 1.                                           */
