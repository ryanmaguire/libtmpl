/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 ******************************************************************************/

/*  Needed for malloc.                                                        */
#include <stdlib.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_string.h>

/*  Function for duplicating a string into a char pointer.                    */
char *tmpl_strdup(const char *str)
{
    /*  Declare necessary variables.                                          */
    char *out;
    unsigned long int n, string_length;

    /*  Check if the input string is a NULL pointer. A segfault may occur if  *
     *  we try to dereference a NULL pointer.                                 */
    if (str == NULL)
        return NULL;

    /*  Otherwise, compute the length of the input string.                    */
    string_length = 0UL;

    /*  Increment until we hit the NULL terminator of the string.             */
    while(str[string_length])
    {
        ++string_length;
    }

    /*  Allocate memory for the output string. The +1 is for the NULL         *
     *  terminator at the end of the string.                                  */
    out = malloc(sizeof(*out) * (string_length + 1UL));

    /*  Check if malloc failed.                                               */
    if (out == NULL)
        return NULL;

    /*  If not, copy the input string into out.                               */
    for (n = 0UL; n < string_length; ++n)
        out[n] = str[n];

    /*  Lastly, set the NULL terminator and return.                           */
    out[string_length] = str[string_length];
    return out;
}
/*  End of tmpl_strdup.                                                       */

