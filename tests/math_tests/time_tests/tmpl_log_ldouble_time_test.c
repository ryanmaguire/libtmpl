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
#include <float.h>

int main(void)
{
    long double rms_abs = 0.0L;
    long double rms_rel = 0.0L;
    long double max_abs = 0.0L;
    long double max_rel = 0.0L;
    long double temp;
    long double *x, *y0, *y1;
    unsigned long int n;
    clock_t t1, t2;
    const long double start = 0.00001L;
    const long double end = 100.0L;
    const unsigned long int N = 1E6;
    const long double dx = (end - start) / (long double)N;

    x = malloc(sizeof(*x) * N);
    y0 = malloc(sizeof(*y0) * N);
    y1 = malloc(sizeof(*y1) * N);

    x[0] = start;
    for (n = 1UL; n < N; ++n)
        x[n] = x[n-1] + dx;

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y0[n] = tmpl_LDouble_Log(x[n]);
    t2 = clock();

    printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y1[n] = logl(x[n]);
    t2 = clock();

    printf("C:       %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

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

    printf("max abs error: %.32Le\n", max_abs);
    printf("max rel error: %.32Le\n", max_rel);
    printf("rms abs error: %.32Le\n", rms_abs);
    printf("rms rel error: %.32Le\n", rms_rel);

    free(x);
    free(y0);
    free(y1);
    return 0;
}
