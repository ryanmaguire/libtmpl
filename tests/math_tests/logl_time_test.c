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
    long double start, end, dx, max_abs, max_rel, temp;
    long double *x, *y0, *y1;
    unsigned long int n, N;
    clock_t t1, t2;

    long double (*f0)(long double);
    long double (*f1)(long double);

    f0 = tmpl_LDouble_Log;
    f1 = logl;

    start = 0.0L;
    end   = 100.0L;
    N     = 1E8;
    dx    = (end - start) / (long double)N;

    x  = malloc(sizeof(*x)  * N);
    y0 = malloc(sizeof(*y0) * N);
    y1 = malloc(sizeof(*y1) * N);

    x[0] = start;
    for (n = 1UL; n < N; ++n)
        x[n] = x[n-1] + dx;

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y0[n] = f0(x[n]);
    t2 = clock();

    printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y1[n] = f1(x[n]);
    t2 = clock();

    printf("C:       %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    max_abs = 0.0;
    for (n = 0UL; n < N; ++n)
    {
        temp = fabsl(y0[n] - y1[n]);
        if (max_abs < temp)
            max_abs = temp;

        temp = fabsl((y0[n] - y1[n]) / y1[n]);
        if (max_rel < temp)
            max_rel = temp;
    }

    printf("Max Abs Error: %.32Lf\n", max_abs);
    printf("Max Rel Error: %.32Lf\n", max_rel);

    free(x);
    free(y0);
    free(y1);
    return 0;
}

