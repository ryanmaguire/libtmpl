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
    double max_abs, max_rel, temp;
    double *x, *y0, *y1;
    unsigned long int n;
    clock_t t1, t2;

    const double start = -1000.0;
    const double end = 1000.00;
    const unsigned long int N = 1E8;
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

    printf("Functions: tmpl_Double_Abs vs fabs\n\n");
    printf("Start:     %.16e\n", start);
    printf("End:       %.16e\n", end);
    printf("Number:    %lu\n", N);
    printf("Increment: %.16e\n\n", dx);

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

    max_abs = 0.0;
    max_rel = 0.0;
    for (n = 0UL; n < N; ++n)
    {
        temp = fabs(y0[n] - y1[n]);
        if (max_abs < temp)
            max_abs = temp;

        temp = fabs((y0[n] - y1[n]) / y1[n]);
        if (max_rel < temp)
            max_rel = temp;
    }

    printf("Max Abs Error: %.24e\n", max_abs);
    printf("Max Rel Error: %.24e\n", max_rel);

    free(x);
    free(y0);
    free(y1);
    return 0;
}
/*  End of main.                                                              */
