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
 *                              tmpl_lower_case                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Convert upper case letters to lower case.                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Lower_Case                                                       *
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
 *      Use a switch to check the argument, returning the lower case version  *
 *      if applicable, and returning the input otherwise.                     *
 *  Notes:                                                                    *
 *      This is the more portable version of tmpl_ASCII_Lower_Case, but it    *
 *      is a bit slower. The computational time is negligible for most        *
 *      applications for both functions.                                      *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_string.h:                                                        *
 *          Header file containing the function prototype.                    *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 12, 2021                                               *
 ******************************************************************************/

/*  Function prototype is here.                                               */
#include <libtmpl/include/tmpl_string.h>

/*  Function for converting upper case character to lower case.               */
char tmpl_Lower_Case(char c)
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
/*  End of tmpl_Lower_Case.                                                   */

