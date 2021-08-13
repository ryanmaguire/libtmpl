/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       August 12, 2021                                               *
 ******************************************************************************/

/*  puts function is here.                                                    */
#include <stdio.h>

/*  free is here.                                                             */
#include <stdlib.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_string.h>

int main(void)
{
    /*  Copy a string into a char pointer.                                    */
    char *str = tmpl_strdup("Hi! This is my string!");

    /*  Check if the internal call to malloc failed.                          */
    if (!str)
        puts("tmpl_strdup failed and returned NULL.");
    else
    {
        puts(str);

        /*  Since tmpl_strdup was successful, now that we're done with it we  *
         *  need to free the memory that was allocated to it.                 */
        free(str);
    }

    return 0;
}
/*  End of main.                                                              */

