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

/*  puts function found here.                                                 */
#include <stdio.h>

/*  tmpl_Lower_Case declared here.                                            */
#include <libtmpl/include/tmpl_string.h>

/*  Array of all upper case letters in order.                                 */
static char upper_arr[26] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

/*  Array of all lower case letters in order.                                 */
static char lower_arr[26] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

/*  Function for testing tmpl_Lower_Case.                                     */
int main(void)
{
    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Character to be used for testing tmpl_Lower_Case.                     */
    char c;

    /*  Loop over all letters and test tmpl_Lower_Case.                       */
    for (n = 0; n < 26; ++n)
    {
        /*  Convert the upper case letter to lower case.                      */
        c = tmpl_Lower_Case(upper_arr[n]);

        /*  Check if it worked.                                               */
        if (c != lower_arr[n])
        {
            puts("FAIL");
            return -1;
        }

        /*  Convert lower case to lower case. Nothing should happen.          */
        c = tmpl_Lower_Case(lower_arr[n]);

        /*  Check if it worked.                                               */
        if (c != lower_arr[n])
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

