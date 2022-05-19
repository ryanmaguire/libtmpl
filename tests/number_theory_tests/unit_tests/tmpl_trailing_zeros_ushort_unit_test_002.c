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
#include <limits.h>
#include <libtmpl/include/tmpl_number_theory.h>

/*  Only run this test on 16-bit short. Larger short may take a very long     *
 *  time to run. 16-bit (65536 total numbers) takes a fraction of a second.   */

int main(void)
{
    unsigned int n;
    for (n = 1U; n < USHRT_MAX; ++n)
    {
        unsigned short int m = (unsigned short int)n;
        int x = tmpl_UShort_Trailing_Zeros(m);
        int y = __builtin_ctz(n);

        if (x != y)
        {
            printf("FAIL\n");
            return -1;
        }
    }

    puts("PASS");
    return 0;
}
