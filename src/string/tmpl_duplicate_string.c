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
 *                                tmpl_strdup                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the string duplicating function. This is *
 *      identical to the function strdup defined in the POSIX standard.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_strdup:                                                          *
 *  Purpose:                                                                  *
 *      Duplicates a string:                                                  *
 *                                                                            *
 *          char *string = tmpl_strdup("my string");                          *
 *                                                                            *
 *  Arguments:                                                                *
 *      str (const char *):                                                   *
 *          The string that is to be duplicated.                              *
 *  Output:                                                                   *
 *      out (char *):                                                         *
 *          A pointer to a null-terminated char array containing the string.  *
 *  Called Functions:                                                         *
 *      malloc  (stdlib.h)                                                    *
 *          Allocates memory for a pointer.                                   *
 *  Method:                                                                   *
 *      Compute the size of the string, allocate memory for the new char      *
 *      pointer, and copy the string byte-by-byte into the allocated space.   *
 *  Notes:                                                                    *
 *      If the input string is NULL, a NULL pointer is returned. If malloc    *
 *      fails, a NULL pointer is returned. You should free the pointer when   *
 *      you are done with it to avoid memory leaks.                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library header file containing malloc.                   *
 *  2.) tmpl_string.h:                                                        *
 *          Header where tmpl_strdup is declared.                             *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   April 8, 2021                                                     *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/01/21: Ryan Maguire                                                  *
 *      Added docstring style comments.                                       *
 ******************************************************************************/

/*  Needed for malloc.                                                        */
#include <stdlib.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_string.h>

/*  Function for duplicating a string into a char pointer.                    */
char *tmpl_Duplicate_String(const char *str)
{
    /*  Declare necessary variables.                                          */
    char *out;
    size_t n, string_length;
    const size_t zero = (size_t)0;
    const size_t one = (size_t)1;

    /*  Check if the input string is a NULL pointer. A segfault may occur if  *
     *  we try to dereference a NULL pointer.                                 */
    if (!str)
        return NULL;

    /*  Otherwise, compute the length of the input string.                    */
    string_length = tmpl_String_Length(str);

    /*  Allocate memory for the output string. The +1 is for the NULL         *
     *  terminator at the end of the string.                                  */
    out = malloc(sizeof(*out) * (string_length + one));

    /*  Check if malloc failed.                                               */
    if (!out)
        return NULL;

    /*  If not, copy the input string into out.                               */
    for (n = zero; n < string_length; ++n)
        out[n] = str[n];

    /*  Lastly, set the NULL terminator and return.                           */
    out[string_length] = str[string_length];
    return out;
}
/*  End of tmpl_Duplicate_String.                                             */

