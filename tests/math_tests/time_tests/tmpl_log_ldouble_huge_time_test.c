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
    long double max_abs = 0.0L;
    long double max_rel = 0.0L;
    long double rms_rel = 0.0L;
    long double rms_abs = 0.0L;
    long double temp;
    long double *x, *y0, *y1;
    unsigned long int n;
    clock_t t1, t2;
    const long double start = 0.00001L;
    const long double end = 1000.0L;
    const unsigned long int N = 2615628245UL;
    const long double dx = (end - start) / (long double)N;

    x = malloc(sizeof(*x)  * N);

    if (!x)
    {
        puts("malloc failed and returned NULL for x. Aborting.");
        return -1;
    }

    y0 = malloc(sizeof(*y0) * N);

    if (!y0)
    {
        puts("malloc failed and returned NULL for y0. Aborting.");
        free(x);
        return -1;
    }

    y1 = malloc(sizeof(*y1) * N);

    if (!y1)
    {
        puts("malloc failed and returned NULL for y1. Aborting.");
        free(x);
        free(y0);
        return -1;
    }

    printf("start:   %Lf\n", start);
    printf("end:     %Lf\n", end);
    printf("samples: %lu\n", N);

    x[0] = start;
    for (n = 1UL; n < N; ++n)
        x[n] = x[n-1] + dx;

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y0[n] = tmpl_LDouble_Log(x[n]);
    t2 = clock();
    printf("libtmpl: %f seconds\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y1[n] = logl(x[n]);
    t2 = clock();
    printf("C:       %f seconds\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    for (n = 0UL; n < N; ++n)
    {
        temp = fabsl(y0[n] - y1[n]);
        rms_abs += temp*temp;
        if (max_abs < temp)
            max_abs = temp;

        temp = fabsl((y0[n] - y1[n]) / y1[n]);
        rms_rel += temp*temp;
        if (max_rel < temp)
            max_rel = temp;
    }

    rms_rel = sqrtl(rms_rel / (long double)N);
    rms_abs = sqrtl(rms_abs / (long double)N);
    printf("max abs error: %.16Le\n", max_abs);
    printf("max rel error: %.16Le\n", max_rel);
    printf("rms abs error: %.16Le\n", rms_abs);
    printf("rms rel error: %.16Le\n", rms_rel);
    free(x);
    free(y0);
    free(y1);
    return 0;
}

