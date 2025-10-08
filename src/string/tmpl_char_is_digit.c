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
 *                             tmpl_char_is_digit                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks if a character represents a number.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Char_Is_Digit                                                    *
 *  Purpose:                                                                  *
 *      Given a char c, checks if c is a number (like '0' or '6').            *
 *  Arguments:                                                                *
 *      c (char):                                                             *
 *          Any character.                                                    *
 *  Output:                                                                   *
 *      is_digit (tmpl_Bool):                                                 *
 *          Boolean indicating if c is a digit.                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      ASCII Version:                                                        *
 *          All numeric values fall between '0' and '9' when these            *
 *          characters are treated as the numbers the bits for them represent.*
 *          Simply check if '0' <= c and c <= '9'.                            *
 *      Portable Version:                                                     *
 *          Use a switch to check the argument. If c is a number, return true.*
 *  Notes:                                                                    *
 *      The ASCII version is much faster on older compilers, modern compilers *
 *      with strong enough optimizations produce identical code for both      *
 *      methods. ASCII, ISO 8859-1, is quite standard, however. It is likely  *
 *      the ASCII version is supported with your compiler.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_HAS_ASCII is defined.                      *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 29, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/10/08: Ryan Maguire                                                  *
 *      Added docstring, simplified switch, general clean up.                 *
 ******************************************************************************/

/*  TMPL_HAS_ASCII macro found here.                                          */
#include <libtmpl/include/tmpl_config.h>

/*  Booleans (true and false) are provided here.                              */
#include <libtmpl/include/tmpl_bool.h>

/*  Forward declaration / function prototype, found in tmpl_string.h as well. */
extern tmpl_Bool tmpl_Char_Is_Digit(char c);

/*  The ASCII version is much more efficient with older compilers.            */
#if TMPL_HAS_ASCII == 1

/******************************************************************************
 *                               ASCII Version                                *
 ******************************************************************************/

/*  Function for determining if a character represents a number.              */
tmpl_Bool tmpl_Char_Is_Digit(char c)
{
    /*  All numeric characters fall between '0' = 0x30 = 48 and               *
     *  '9' = 0x39 = 57. All character outside of this range are not numbers. */
    if (c > '9' || c < '0')
        return tmpl_False;

    /*  If 0x30 <= c <= 0x39 we have a digit. Return true.                    */
    return tmpl_True;
}
/*  End of tmpl_Char_Is_Digit.                                                */

#else
/*  Else for #if TMPL_HAS_ASCII == 1.                                         */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for determining if a character represents a number.              */
tmpl_Bool tmpl_Char_Is_Digit(char c)
{
    /*  Lacking ASCII support, we simply use a switch to check the character. *
     *  Interestingly enough, on a modern compiler with strong enough         *
     *  optimizations, this switch will produce the same assembly code as the *
     *  ASCII version above (GCC 15.2 with -O3 enabled, for example). With    *
     *  other compilers there is a noticeable difference in the performance.  */
    switch (c)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return tmpl_True;
        default:
            return tmpl_False;
    }
}
/*  End of tmpl_Char_Is_Digit.                                                */

#endif
/*  End of #if TMPL_HAS_ASCII == 1.                                           */
