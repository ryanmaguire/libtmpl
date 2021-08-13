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
 *                          tmpl_ascii_lower_case                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Convert upper case letters to lower case.                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ASCII_Lower_Case                                                 *
 *  Purpose:                                                                  *
 *      Given a char c that represents an ascii character, convert it to      *
 *      lower case (if applicable).                                           *
 *  Arguments:                                                                *
 *      c (char):                                                             *
 *          An ASCII character.                                               *
 *  Output:                                                                   *
 *      lower_c (char):                                                       *
 *          The lower case of c (if applicable).                              *
 *  Method:                                                                   *
 *      Use the ISO 8859-1 standard to convert an upper case character to a   *
 *      lower case one. See the code for an explanation.                      *
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
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       August 12, 2021                                               *
 ******************************************************************************/

/*  Function prototype is here.                                               */
#include <libtmpl/include/tmpl_string.h>

/*  Function for converting an ASCII character to lower case.                 */
char tmpl_ASCII_Lower_Case(char c)
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
    else
        return c;
}
/*  End of tmpl_ASCII_Lower_Case.                                             */

