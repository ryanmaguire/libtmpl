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
 *                                tmpl_string                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide functions for dealing with strings. Some of these functions   *
 *      are included in the POSIX standard of the C programming language, but *
 *      are not required by the actual standard. They are provided here for   *
 *      the sake of portability.                                              *
 *  NOTES:                                                                    *
 *      This code is identical to the code I wrote for rss_ringoccs, only the *
 *      rssringoccs titles have been replaced with tmpl. rss_ringoccs is also *
 *      released under GPL3.                                                  *
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
 *  Author: Ryan Maguire                                                      *
 *  Date:   April 8, 2021                                                     *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/01/21: Ryan Maguire                                                  *
 *      Added docstring style comments for function declarations.             *
 *      Added and updated tests for functions in test/ directory.             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_STRING_H
#define TMPL_STRING_H

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_ASCII_Lower_Case                                                 *
 *  Purpose:                                                                  *
 *      Takes in a char which represents an ASCII character and returns the   *
 *      lower-case of the character if it is a capital letter, and returns    *
 *      the input otherwise.                                                  *
 *  Arguments:                                                                *
 *      upper (char):                                                         *
 *          The input character.                                              *
 *  Output:                                                                   *
 *      lower (char):                                                         *
 *          The lower case version of the input character.                    *
 *  Note:                                                                     *
 *      The function assumes the ASCII ISO 8859-1 standard is implemented.    *
 *      This has been the case on all devices I've tested. If you're unsure,  *
 *      use tmpl_Lower_Case. That function is slower, but the computational   *
 *      time is essentially negligible for both functions.                    *
 *  Source Code:                                                              *
 *      libtmpl/src/string/tmpl_ascii_lower_case.c                            *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes/tmpl_determine_endianness_example.c            *
 ******************************************************************************/
extern char tmpl_ASCII_Lower_Case(char c);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_ASCII_Upper_Case                                                 *
 *  Purpose:                                                                  *
 *      Takes in a char which represents an ASCII character and returns the   *
 *      upper-case of the character if it is a lower-case letter, and returns *
 *      the input otherwise.                                                  *
 *  Arguments:                                                                *
 *      lower (char):                                                         *
 *          The input character.                                              *
 *  Output:                                                                   *
 *      upper (char):                                                         *
 *          The upper case version of the input character.                    *
 *  Note:                                                                     *
 *      The function assumes the ASCII ISO 8859-1 standard is implemented.    *
 *      This has been the case on all devices I've tested. If you're unsure,  *
 *      use tmpl_Lower_Case. That function is slower, but the computational   *
 *      time is essentially negligible for both functions.                    *
 *  Source Code:                                                              *
 *      libtmpl/src/string/tmpl_strdup.c                                      *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes/tmpl_determine_endianness_example.c            *
 ******************************************************************************/
extern char tmpl_ASCII_Lower_Case(char c);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_strdup                                                           *
 *  Purpose:                                                                  *
 *      Copies a string, verbatim, into a pointer to a char array. This is    *
 *      equivalent to the strdup function, defined in the POSIX standard, but *
 *      not defined in the general standard of the C programming language.    *
 *  Arguments:                                                                *
 *      str (const char *):                                                   *
 *          The string that is to be duplicated.                              *
 *  Output:                                                                   *
 *      dup (char *):                                                         *
 *          A pointer to a char array whose entries correspond to the input   *
 *          string str.                                                       *
 *  NOTE:                                                                     *
 *      A call to malloc is made to allocate memory for the string. You must  *
 *      free the pointer after you are done with it to avoid memory leaks.    *
 *      There is also the (unlikely) chance that malloc failed to allocate    *
 *      memory for the pointer, and returns NULL. You should also check that  *
 *      the output pointer is not NULL before using it.                       *
 *  Source Code:                                                              *
 *      libtmpl/src/string/tmpl_strdup.c                                      *
 *  Examples:                                                                 *
 *      libtmpl/examples/string/tmpl_strdup_example.c                         *
 ******************************************************************************/
extern char *tmpl_strdup(const char *str);

extern char tmpl_Lower_Case(char c);

extern void tmpl_Make_Lower(char *str);
extern void tmpl_Remove_Spaces(char * str);

#endif
/*  End of include guard.                                                     */

