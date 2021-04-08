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

/*  Needed for strcpy.                                                        */
#include <string.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_string.h>

/*  Function for duplicating a string into a char pointer.                    */
char *tmpl_strdup(const char *str)
{
    /*  Create space for the output. The +1 is for the NULL terminator.       */
    char *dst = malloc(strlen(str) + 1);

    /*  Check if malloc failed.                                               */
    if (dst == NULL)
        return NULL;

    /*  Copy the input string into dst.                                       */
    strcpy(dst, str);
    return dst;
}
/*  End of tmpl_strdup.                                                       */

