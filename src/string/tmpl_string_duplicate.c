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
 *                            tmpl_string_duplicate                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the string duplicating function. This is *
 *      identical to the function strdup defined in the POSIX standard.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_String_Duplicate                                                 *
 *  Purpose:                                                                  *
 *      Duplicates a string:                                                  *
 *                                                                            *
 *          char *string = tmpl_String_Duplicate("my string");                *
 *                                                                            *
 *  Arguments:                                                                *
 *      str (const char *):                                                   *
 *          The string that is to be duplicated.                              *
 *  Output:                                                                   *
 *      out (char *):                                                         *
 *          A pointer to a null-terminated char array containing the string.  *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          malloc:                                                           *
 *              Allocates memory for a pointer.                               *
 *      src/string/                                                           *
 *          tmpl_String_Length:                                               *
 *              Computes the length of a string.                              *
 *  Method:                                                                   *
 *      Compute the size of the string, allocate memory for the new char      *
 *      pointer, and copy the string byte-by-byte into the allocated space.   *
 *  Notes:                                                                    *
 *      If the input string is NULL, a NULL pointer is returned. If malloc    *
 *      fails, a NULL pointer is returned. You should free the pointer when   *
 *      you are done with it to avoid memory leaks.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_cast.h:                                                          *
 *          Provides a macro for casting with C vs. C++ compatibility.        *
 *  2.) tmpl_malloc.h:                                                        *
 *          Provides a malloc macro with C vs. C++ compatibility.             *
 *  3.) stddef.h:                                                             *
 *          Standard library header providing the size_t typedef and NULL.    *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   April 8, 2021                                                     *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/01/21: Ryan Maguire                                                  *
 *      Added docstring style comments.                                       *
 *  2023/08/08: Ryan Maguire                                                  *
 *      Changed function name, adding call to tmpl_String_Length.             *
 *  2025/10/08: Ryan Maguire                                                  *
 *      Added use of TMPL_CAST and TMPL_MALLOC.                               *
 ******************************************************************************/

/*  TMPL_CAST given here, provides casting with C vs. C++ compatibility.      */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  TMPL_MALLOC found here. Provides C vs. C++ compatibility.                 */
#include <libtmpl/include/compat/tmpl_malloc.h>

/*  size_t typedef and the NULL macro are found here.                         */
#include <stddef.h>

/*  Function used for computing the length of the input string.               */
extern size_t tmpl_String_Length(const char * const str);

/*  Forward declaration / function prototype, found in tmpl_string.h as well. */
extern char *tmpl_String_Duplicate(const char * const str);

/*  Function for duplicating a string into a char pointer.                    */
char *tmpl_String_Duplicate(const char *str)
{
    /*  Declare necessary variables.                                          */
    char *out;
    size_t n, string_length;

    /*  Useful constants, cast to type "size_t".                              */
    const size_t zero = TMPL_CAST(0, size_t);
    const size_t one = TMPL_CAST(1, size_t);

    /*  Check if the input string is a NULL pointer. A segfault may occur if  *
     *  we try to dereference a NULL pointer.                                 */
    if (!str)
        return NULL;

    /*  Otherwise, compute the length of the input string.                    */
    string_length = tmpl_String_Length(str);

    /*  Allocate memory for the output string. The +1 is for the NULL         *
     *  terminator at the end of the string.                                  */
    out = TMPL_MALLOC(char, string_length + one);

    /*  Check if malloc failed.                                               */
    if (!out)
        return NULL;

    /*  If not, copy the input string into out.                               */
    for (n = zero; n < string_length; ++n)
        out[n] = str[n];

    /*  Lastly, set the NULL terminator and return.                           */
    out[string_length] = '\0';
    return out;
}
/*  End of tmpl_String_Duplicate.                                             */
