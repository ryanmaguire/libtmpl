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
#include <libtmpl/include/tmpl_integer.h>

int main(void)
{
    unsigned short int x = 3U;
    unsigned short int y = 4U;

    if (tmpl_UShort_Trailing_Zeros(x) != 0)
    {
        puts("FAIL");
        return -1;
    }

    if (tmpl_UShort_Trailing_Zeros(y) != 2)
    {
        puts("FAIL");
        return -1;
    }

    puts("PASS");
    return 0;
}
