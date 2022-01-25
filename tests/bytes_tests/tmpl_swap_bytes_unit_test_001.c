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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 25, 2022                                              *
 ******************************************************************************/

/*  Needed for the puts function.                                             */
#include <stdio.h>

/*  tmpl_Swap_Bytes found here.                                               */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for testing tmpl_Swap_Bytes.                                     */
int main(void)
{
    /*  Create random char variables that will be swapped later.              */
    const char c0 = 0x1F;
    const char c1 = 0x63;

    /*  char variables that will be swapped.                                  */
    char x0 = c0;
    char x1 = c1;

    /*  Swap the variables.                                                   */
    tmpl_Swap_Bytes(&x0, &x1);

    /*  Check if it worked.                                                   */
    if ((x1 != c0) || (x0 != c1))
        puts("FAIL");
    else
        puts("PASS");

    return 0;
}
/*  End of main.                                                              */

