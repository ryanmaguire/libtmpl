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
 *                                tmpl_string                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide functions for dealing with strings. Some of these functions   *
 *      are included in the POSIX standard of the C programming language, but *
 *      are not required by the actual standard. They are provided here for   *
 *      the sake of portability.                                              *
 *  Notes:                                                                    *
 *      This code is identical to the code I wrote for rss_ringoccs, only the *
 *      rssringoccs titles have been replaced with tmpl. rss_ringoccs is also *
 *      released under GPL3.                                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard library header file where size_t is defined.             *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 8, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/01/21: Ryan Maguire                                                  *
 *      Added docstring style comments for function declarations.             *
 *      Added and updated tests for functions in tests/ directory.            *
 *  2022/01/25: Ryan Maguire                                                  *
 *      Added C++ compatibility.                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_STRING_H
#define TMPL_STRING_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/*  size_t data type found here.                                              */
#include <stddef.h>

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Lower_Case                                                       *
 *  Purpose:                                                                  *
 *      Converts a character to lower case, if applicable.                    *
 *  Arguments:                                                                *
 *      upper (char):                                                         *
 *          The input character.                                              *
 *  Output:                                                                   *
 *      lower (char):                                                         *
 *          The lower case version of the input character.                    *
 *  Source Code:                                                              *
 *      libtmpl/src/string/tmpl_lower_case.c                                  *
 ******************************************************************************/
extern char tmpl_Lower_Case(char c);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Upper_Case                                                       *
 *  Purpose:                                                                  *
 *      Converts a character to upper case, if applicable.                    *
 *  Arguments:                                                                *
 *      lower (char):                                                         *
 *          The input character.                                              *
 *  Output:                                                                   *
 *      upper (char):                                                         *
 *          The upper case version of the input character.                    *
 *  Source Code:                                                              *
 *      libtmpl/src/string/tmpl_upper_case.c                                  *
 ******************************************************************************/
extern char tmpl_Upper_Case(char c);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Duplicate_String                                                 *
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
 *  Notes:                                                                    *
 *      A call to malloc is made to allocate memory for the string. You must  *
 *      free the pointer after you are done with it to avoid memory leaks.    *
 *      There is also the (unlikely) chance that malloc failed to allocate    *
 *      memory for the pointer, and returns NULL. You should also check that  *
 *      the output pointer is not NULL before using it.                       *
 *  Source Code:                                                              *
 *      libtmpl/src/string/tmpl_duplicate_string.c                            *
 ******************************************************************************/
extern char *tmpl_Duplicate_String(const char *str);

size_t tmpl_String_Length(const char *str);

extern void tmpl_Make_Lower(char *str);
extern void tmpl_Remove_Spaces(char * str);

#define tmpl_strdup tmpl_Duplicate_String

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
