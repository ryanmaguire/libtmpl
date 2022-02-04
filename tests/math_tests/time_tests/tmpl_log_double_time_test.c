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
    double start, end, dx, max_abs, max_rel, temp, rms_rel, rms_abs;
    double *x, *y0, *y1;
    unsigned long int n, N;
    clock_t t1, t2;

    double (*f0)(double);
    double (*f1)(double);

    f0 = tmpl_Double_Log;
    f1 = log;

    start = 0.00001;
    end   = 100.0;
    N     = 1E8;
    dx    = (end - start) / (double)N;

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
    max_rel = 0.0;
    rms_abs = 0.0;
    rms_rel = 0.0;
    for (n = 0UL; n < N; ++n)
    {
        temp = fabs(y0[n] - y1[n]);
        rms_abs += temp*temp;
        if (max_abs < temp)
            max_abs = temp;

        temp = fabs((y0[n] - y1[n]) / y1[n]);
        rms_rel += temp*temp;
        if (max_rel < temp)
            max_rel = temp;
    }

    rms_rel = sqrt(rms_rel / (double)N);
    rms_abs = sqrt(rms_abs / (double)N);
    printf("max Abs Error: %.24e\n", max_abs);
    printf("max Rel Error: %.24e\n", max_rel);
    printf("rms Abs Error: %.24e\n", rms_abs);
    printf("rms Rel Error: %.24e\n", rms_rel);

    free(x);
    free(y0);
    free(y1);
    return 0;
}

