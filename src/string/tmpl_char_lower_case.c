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
 *                            tmpl_char_lower_case                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Convert upper case letters to lower case.                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Char_Lower_Case                                                  *
 *  Purpose:                                                                  *
 *      Given a char c, convert it to lower case (if applicable).             *
 *  Arguments:                                                                *
 *      c (char):                                                             *
 *          Any character.                                                    *
 *  Output:                                                                   *
 *      lower_c (char):                                                       *
 *          The lower case of c (if applicable).                              *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      ASCII Version:                                                        *
 *          Use the ISO 8859-1 standard to convert an upper case character to *
 *          a lower case one. See the code for an explanation.                *
 *      Portable Version:                                                     *
 *          Use a switch to check the argument, returning the lower case      *
 *          version, if applicable, and returning the input otherwise.        *
 *  Notes:                                                                    *
 *      The ASCII version is much faster, but the portable version works      *
 *      without the ISO 8859-1 assumption. ISO 8859-1 is standard, however.   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_HAS_ASCII is defined.                      *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 12, 2021                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/08/07: Ryan Maguire                                                  *
 *      Added check for ASCII support. Combined portable and ascii versions.  *
 ******************************************************************************/

/*  TMPL_HAS_ASCII macro found here.                                          */
#include <libtmpl/include/tmpl_config.h>

/*  Booleans (true and false) are provided here.                              */
#include <libtmpl/include/tmpl_bool.h>

/*  Forward declaration / function prototype, found in tmpl_string.h as well. */
extern char tmpl_Char_Lower_Case(char c);

/*  The ASCII version is much more efficient.                                 */
#if TMPL_HAS_ASCII == 1

/******************************************************************************
 *                               ASCII Version                                *
 ******************************************************************************/

/*  Function for converting an ASCII character to lower case.                 */
char tmpl_Char_Lower_Case(char c)
{
    /*  In the ISO 8859-1 standard, the ASCII table has the following         *
     *  property (written in binary):                                         *
     *      1000001 = A                                                       *
     *      1000010 = B                                                       *
     *      1000011 = C                                                       *
     *          ...                                                           *
     *      1100001 = a                                                       *
     *      1100010 = b                                                       *
     *      1100011 = c                                                       *
     *          ...                                                           *
     *  So if we flip the 6th bit, i.e. the 2^5 factor, from 0 to 1 we go     *
     *  from upper case to lower case. Do this with bit-wise OR using 0x20.   */
    if ((c >= 'A') && (c <= 'Z'))
        return c | 0x20;

    /*  Every other value is either already lower-case, or lower-case doesn't *
     *  make sense (i.e. ! or 5), so return the input.                        */
    return c;
}
/*  End of tmpl_Char_Lower_Case.                                              */

#else
/*  Else for #if TMPL_HAS_ASCII == 1.                                         */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for converting upper case character to lower case.               */
char tmpl_Char_Lower_Case(char c)
{
    /*  Use a switch to check the value of c and return the lower-case.       */
    switch(c)
    {
        case 'A':
            return 'a';
        case 'B':
            return 'b';
        case 'C':
            return 'c';
        case 'D':
            return 'd';
        case 'E':
            return 'e';
        case 'F':
            return 'f';
        case 'G':
            return 'g';
        case 'H':
            return 'h';
        case 'I':
            return 'i';
        case 'J':
            return 'j';
        case 'K':
            return 'k';
        case 'L':
            return 'l';
        case 'M':
            return 'm';
        case 'N':
            return 'n';
        case 'O':
            return 'o';
        case 'P':
            return 'p';
        case 'Q':
            return 'q';
        case 'R':
            return 'r';
        case 'S':
            return 's';
        case 'T':
            return 't';
        case 'U':
            return 'u';
        case 'V':
            return 'v';
        case 'W':
            return 'w';
        case 'X':
            return 'x';
        case 'Y':
            return 'y';
        case 'Z':
            return 'z';

        /*  If the input is not a capital letter, return the input.           */
        default:
            return c;
    }
}
/*  End of tmpl_Char_Lower_Case.                                              */

#endif
/*  End of #if TMPL_HAS_ASCII == 1.                                           */
