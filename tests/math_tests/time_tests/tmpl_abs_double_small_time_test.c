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

/*  tmpl_Double_Abs function is here.                                         */
#include <libtmpl/include/tmpl_math.h>

/*  malloc is here.                                                           */
#include <stdlib.h>

/*  printf here.                                                              */
#include <stdio.h>

/*  The C standard library function fabs is here. This is the function we're  *
 *  comparing libtmpl with.                                                   */
#include <math.h>

/*  Tools for timing computations found here.                                 */
#include <time.h>

/*  Function for testing the speed and accuracy of tmpl_Double_Abs.           */
int main(void)
{
    double max_abs = 0.0;
    double max_rel = 0.0;
    double rms_abs = 0.0;
    double rms_rel = 0.0;
    double temp;
    double *x, *y0, *y1;
    unsigned long int n;
    clock_t t1, t2;
    const double start = -1000.0;
    const double end = 1000.00;
    const unsigned long int N = 10000000UL;
    const double dx = (end - start) / (double)N;

    x = malloc(sizeof(*x)  * N);

    /*  Check if malloc failed.                                               */
    if (!x)
    {
        puts("Error: malloc returned NULL. Aborting.");
        return -1;
    }

    y0 = malloc(sizeof(*y0) * N);

    if (!y0)
    {
        puts("Error: malloc returned NULL. Aborting.");
        free(x);
        return -1;
    }

    y1 = malloc(sizeof(*y1) * N);

    if (!y1)
    {
        puts("Error: malloc returned NULL. Aborting.");
        free(x);
        free(y0);
        return -1;
    }

    printf("tmpl_Double_Abs vs fabs\n");
    printf("start:   %.16e\n", start);
    printf("end:     %.16e\n", end);
    printf("samples: %lu\n", N);
    printf("dx:      %.16e\n", dx);

    x[0] = start;
    for (n = 1UL; n < N; ++n)
        x[n] = x[n-1] + dx;

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y0[n] = tmpl_Double_Abs(x[n]);
    t2 = clock();
    printf("libtmpl time: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y1[n] = fabs(x[n]);
    t2 = clock();
    printf("C time:       %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

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

    rms_abs = sqrt(rms_abs / (double)N);
    rms_rel = sqrt(rms_rel / (double)N);

    printf("max abs error: %.16e\n", max_abs);
    printf("max rel error: %.16e\n", max_rel);
    printf("rms abs error: %.16e\n", rms_abs);
    printf("rms rel error: %.16e\n", rms_rel);
    free(x);
    free(y0);
    free(y1);
    return 0;
}
/*  End of main.                                                              */
