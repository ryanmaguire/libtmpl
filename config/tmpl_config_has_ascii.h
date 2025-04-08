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
 *                            tmpl_config_has_ascii                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines if the ASCII character set is used.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_has_ascii                                                        *
 *  Purpose:                                                                  *
 *      Determines if the numeric values for char correspond to ASCII.        *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      has_ascii (int):                                                      *
 *          Boolean, 0 if ASCII is not available, 1 if it is.                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Pre-compute the standard ASCII table and loop through, checking if    *
 *      the numeric value for a given char corresponds to the ASCII character *
 *      in the table.                                                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/08: Ryan Maguire                                                  *
 *      Moved function to its own file.                                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_HAS_ASCII_H
#define TMPL_CONFIG_HAS_ASCII_H

/*  Users may optionally request to not use ASCII-specific code.              */
#ifdef TMPL_NO_ASCII

/*  Determines if the compiler uses the ASCII character set.                  */
static int tmpl_has_ascii(void)
{
    /*  ASCII-specific code not requested. Return false.                      */
    return 0;
}
/*  End of tmpl_has_ascii.                                                    */

#else
/*  Else for #ifdef TMPL_NO_ASCII.                                            */

/*  Used for testing if the compiler uses ASCII for characters.               */
static const char tmpl_ascii_character_array[94] = {
    '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.',
    '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<',
    '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'
};

/*  Determines if the compiler uses the ASCII character set.                  */
static int tmpl_has_ascii(void)
{
    /*  Dummy variable used for indexing.                                     */
    int n;

    /*  Numbers 0 to 32 represent special ASCII characters. The count starts  *
     *  starts at 33, which is 0x21 in hexidecimal.                           */
    const int start = 0x21;

    /*  There are 94 characters total in the table, the final numeric value   *
     *  is 126, which is 0x7E in hexidecimal.                                 */
    const int end = 0x7E;

    /*  Loop through and check if n, as a numerical value, corresponds to the *
     *  nth element of the ASCII table.                                       */
    for (n = start; n <= end; ++n)
    {
        /*  Treat the current index as a character. Cast to char.             */
        const char c = (char)n;

        /*  Indexing starts at zero, whereas n starts at "start". Subtract to *
         *  get the correct table index. If we do not have equality, ASCII is *
         *  not implemented. Return false.                                    */
        if (tmpl_ascii_character_array[n - start] != c)
            return 0;
    }

    /*  If we get here, there was an exact match. ASCII is being used.        */
    return 1;
}
/*  End of tmpl_has_ascii.                                                    */

#endif
/*  End of #ifdef TMPL_NO_ASCII.                                              */

#endif
/*  End of include guard.                                                     */
