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

#include <stdio.h>
#include <stdlib.h>
#include <libtmpl/include/tmpl_math.h>

int main(void)
{
    FILE *fp = fopen("data.txt", "w");

    float start = -4.0F;
    float end   =  4.0F;

    unsigned int N = 1E5;
    unsigned int n;
    float x, y, diff, dx;

    dx = (end - start) / (float)N;
    x = start;

    for (n = 0UL; n < N; ++n)
    {
        y = tmpl_Float_Mod_2(x);
        fprintf(fp, "%f %f\n", x, y);
        x += dx;
    }

    fclose(fp);
    system("graph -T ps data.txt > tmpl_floor_gnuplotutils.ps");
    system("rm -f data.txt");
    return 0;
}
