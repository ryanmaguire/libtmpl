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
 *      Use a switch to check the argument, returning the upper case version  *
 *      if applicable, and returning the input otherwise.                     *
 *  Notes:                                                                    *
 *      This is the more portable version of tmpl_ASCII_Upper_Case, but it    *
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
 *  Date:       January 26, 2022                                              *
 ******************************************************************************/

/*  Function prototype is here.                                               */
#include <libtmpl/include/tmpl_string.h>

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

