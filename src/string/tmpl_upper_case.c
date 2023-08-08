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
 *                              tmpl_upper_case                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Convert lower case letters to upper case.                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Upper_Case                                                       *
 *  Purpose:                                                                  *
 *      Given a char c, convert it to upper case (if applicable).             *
 *  Arguments:                                                                *
 *      c (char):                                                             *
 *          Any character.                                                    *
 *  Output:                                                                   *
 *      upper_c (char):                                                       *
 *          The upper case of c (if applicable).                              *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      ASCII Version:                                                        *
 *          Use the ISO 8859-1 standard to convert a lower case character to  *
 *          an upper case one. See the code for an explanation.               *
 *      Portable Version:                                                     *
 *          Use a switch to check the argument, returning the upper case      *
 *          version, if applicable, and returning the input otherwise.        *
 *  Notes:                                                                    *
 *      The ASCII version is much faster, but the portable version works      *
 *      without the ISO 8859-1 assumption. ISO 8859-1 is standard, however.   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_HAS_ASCII is defined.                      *
 *  2.) tmpl_string.h:                                                        *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 26, 2022                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/08/07: Ryan Maguire                                                  *
 *      Added check for ASCII support. Combined portable and ascii versions.  *
 ******************************************************************************/

/*  TMPL_HAS_ASCII macro found here.                                          */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype is here.                                               */
#include <libtmpl/include/tmpl_string.h>

/*  The ASCII version is much more efficient.                                 */
#if TMPL_HAS_ASCII == 1

/*  Function for converting an ASCII character to upper case.                 */
char tmpl_Upper_Case(char c)
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
     *  So if we flip the 6th bit, i.e. the 2^5 factor, from 1 to 0 we go     *
     *  from lower case to upper case. Do this with bit-wise AND using 0x5F.  */
    if ((c >= 'a') && (c <= 'z'))
        return c & 0x5F;

    /*  Every other value is either already upper-case, or upper-case doesn't *
     *  make sense (i.e. ! or 5), so return the input.                        */
    return c;
}
/*  End of tmpl_Upper_Case.                                                   */

#else
/*  Else for #if TMPL_HAS_ASCII == 1.                                         */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for converting lower case character to upper case.               */
char tmpl_Upper_Case(char c)
{
    /*  Use a switch to check the value of c and return the lower-case.       */
    switch(c)
    {
        case 'a':
            return 'A';
        case 'b':
            return 'B';
        case 'c':
            return 'C';
        case 'd':
            return 'D';
        case 'e':
            return 'E';
        case 'f':
            return 'F';
        case 'g':
            return 'G';
        case 'h':
            return 'H';
        case 'i':
            return 'I';
        case 'j':
            return 'J';
        case 'k':
            return 'K';
        case 'l':
            return 'L';
        case 'm':
            return 'M';
        case 'n':
            return 'N';
        case 'o':
            return 'O';
        case 'p':
            return 'P';
        case 'q':
            return 'Q';
        case 'r':
            return 'R';
        case 's':
            return 'S';
        case 't':
            return 'T';
        case 'u':
            return 'U';
        case 'v':
            return 'V';
        case 'w':
            return 'W';
        case 'x':
            return 'X';
        case 'y':
            return 'Y';
        case 'z':
            return 'Z';

        /*  If the input is not a lower-case letter, return the input.        */
        default:
            return c;
    }
}
/*  End of tmpl_Upper_Case.                                                   */

#endif
/*  End of #if TMPL_HAS_ASCII == 1.                                           */
