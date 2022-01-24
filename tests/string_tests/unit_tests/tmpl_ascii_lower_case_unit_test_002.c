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
 ******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <libtmpl/include/tmpl_string.h>

int main(void)
{
    char n, c;
    int out;

    for (n = CHAR_MIN; n < CHAR_MAX; ++n)
    {
        c = tmpl_ASCII_Lower_Case(n);
        out = tolower(n);

        if (c != (char)out)
        {
            printf("FAIL");
            return -1;
        }
    }

    puts("PASS");
    return 0;
}

