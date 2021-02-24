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
#include <math.h>
#include <libtmpl/include/tmpl_math.h>

static void write_val(FILE *fp, long double x, long double y)
{
    double xd = (double)x;
    double yd = (double)y;
    fwrite(&xd, sizeof(xd), 1, fp);
    fwrite(&yd, sizeof(yd), 1, fp);
}

int main(void)
{
    FILE *tmpl_fp, *glibc_fp, *diff_fp;

    long double start = 0.5L;
    long double end   = 1.5L;

    unsigned long N = 1e6;
    unsigned long n;
    long double x, y0, y1, diff;

    long double dx = (end - start) / (long double)N;

    tmpl_fp  = fopen("tmpl_logl_binary", "w");
    glibc_fp = fopen("glibc_logl_binary", "w");
    diff_fp  = fopen("diff_binary", "w");

    x = start;
    for (n = 0UL; n < N; ++n)
    {
        y0 = tmpl_LDouble_Log(x);
        write_val(tmpl_fp, x, y0);

        y1 = logl(x);
        write_val(glibc_fp, x, y1);

        diff = y1 - y0;
        write_val(diff_fp, x, diff);
        x += dx;
    }
    fclose(tmpl_fp);
    fclose(glibc_fp);
    fclose(diff_fp);

    system("graph -T ps -I d < tmpl_logl_binary glibc_logl_binary "
           "-L \"logl\" --reposition 0.0 -0.8 1 diff_binary "
           "-L \"Difference (tmpl vs glibc)\" > tmpl_logl_gnuplotutils.ps");
    system("rm -f tmpl_logl_binary glibc_logl_binary diff_binary");
    return 0;
}

