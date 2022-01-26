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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 26, 2022                                              *
 ******************************************************************************/

/*  puts found here.                                                          */
#include <stdio.h>

/*  toupper found here.                                                       */
#include <ctype.h>

/*  CHAR_MIN and CHAR_MAX macros are here.                                    */
#include <limits.h>

/*  tmpl_ASCII_Upper_Case declared here.                                      */
#include <libtmpl/include/tmpl_string.h>

/*  Function for testing tmpl_ASCII_Upper_Case against toupper.               */
int main(void)
{
    /*  Variables for indexing and testing toupper vs tmpl_ASCII_Upper_Case.  */
    char n, c;
    int out;

    /*  Loop over all possible char values.                                   */
    for (n = CHAR_MIN; n < CHAR_MAX; ++n)
    {
        /*  Compute toupper and tmpl_ASCII_Upper_Case of n and compare.       */
        c = tmpl_ASCII_Upper_Case(n);
        out = toupper(n);

        /*  The answers should be identical.                                  */
        if (c != (char)out)
        {
            puts("FAIL");
            return -1;
        }
    }

    /*  If we get here, the function passes this test.                        */
    puts("PASS");

    return 0;
}
/*  End of main.                                                              */

