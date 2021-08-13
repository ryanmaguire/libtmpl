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

/*  printf function is here.                                                  */
#include <stdio.h>

/*  Maximum of char is here.                                                  */
#include <limits.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_string.h>

/*  Function for testing tmpl_ASCII_Lower_Case.                               */
int main(void)
{
    /*  Variables for looping over all characters.                            */
    int n;
    char in[2] = " ";
    char out[2] = " ";


    /*  Loop over and print the results.                                      */
    for (n = 0x00; n != 0xFF; ++n)
    {
        in[0] = (char)n;
        out[0] = tmpl_ASCII_Lower_Case(in[0]);
        printf("Input: %s Output: %s\n", in, out);
    }

    return 0;
}
/*  End of main.                                                              */

