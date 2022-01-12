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

#include <libtmpl/include/tmpl_math.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void)
{
    float start, end, dx, max_abs, max_rel, temp, worst_abs, worst_rel;
    float *x, *y0, *y1;
    float mant;
    signed int expo;
    unsigned long int n, N, bad;
    clock_t t1, t2;

    start = 0.0F;
    end   = 100.0F;
    N     = 1E8;
    dx    = (end - start) / (float)N;

    x  = malloc(sizeof(*x)  * N);
    y0 = malloc(sizeof(*y0) * N);
    y1 = malloc(sizeof(*y1) * N);

    x[0] = start;
    for (n = 1UL; n < N; ++n)
        x[n] = x[n-1] + dx;

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y0[n] = tmpl_Float_Log(x[n]);
    t2 = clock();

    printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y1[n] = logf(x[n]);
    t2 = clock();

    printf("C:       %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    max_abs = 0.0F;
    max_rel = 0.0F;
    worst_abs = start;
    worst_rel = start;
    bad = 0U;
    for (n = 0UL; n < N; ++n)
    {
        temp = fabsf(y0[n] - y1[n]);
        if (max_abs < temp)
        {
            max_abs = temp;
            worst_abs = x[n];
        }

        temp = fabsf((y0[n] - y1[n]) / y1[n]);
        if (max_rel < temp)
        {
            max_rel = temp;
            worst_rel = x[n];
            bad = n;
        }
    }

    printf("Max Abs Error: %.16e\n", (double)max_abs);
    printf("Max Rel Error: %.16e\n", (double)max_rel);
    printf("Worst Abs: %.16e\n", (double)worst_abs);
    printf("Worst Rel: %.16e\n", (double)worst_rel);

    free(x);
    free(y0);
    free(y1);
    return 0;
}

