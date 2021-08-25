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

/*  tmpl complex functions found here.                                        */
#include <libtmpl/include/tmpl_complex.h>

/*  C99 complex functions here.                                               */
#include <complex.h>

/*  malloc and free are here.                                                 */
#include <stdlib.h>

/*  printf here.                                                              */
#include <stdio.h>

/*  Time data types and functions here.                                       */
#include <time.h>

/*  Routine for testing tmpl_CLDouble_Abs.                                    */
int main(void)
{
    long double *y0, *y1;
    tmpl_ComplexLongDouble *z0;
    complex long double *z1;

    const unsigned int N = 10000U;
    const long double start = -100.0L;
    const long double end = 100.0L;
    const long double ds = (end - start) / (long double)(N - 1U);

    unsigned int x, y;
    clock_t t1, t2;
    long double z_x, z_y, max_rel, max_abs, temp;

    /*  Allocate memory and check that malloc did not fail.                   */
    y0 = malloc(sizeof(*y0) * N * N);

    if (y0 == NULL)
    {
        puts("malloc failed and returned NULL. Aborting.");
        return -1;
    }

    y1 = malloc(sizeof(*y1) * N * N);

    if (y1 == NULL)
    {
        puts("malloc failed and returned NULL. Aborting.");
        free(y0);
        return -1;
    }

    z0 = malloc(sizeof(*z0) * N * N);

    if (z0 == NULL)
    {
        puts("malloc failed and returned NULL. Aborting.");
        free(y0);
        free(y1);
        return -1;
    }

    z1 = malloc(sizeof(*z1) * N * N);

    if (z1 == NULL)
    {
        puts("malloc failed and returned NULL. Aborting.");
        free(y0);
        free(y1);
        free(z0);
        return -1;
    }

    for (x = 0U; x < N; ++x)
    {
        for (y = 0U; y < N; ++y)
        {
            z_x = (long double)x*ds + start;
            z_y = (long double)y*ds + start;
            z0[x + y*N] = tmpl_CLDouble_Rect(z_x, z_y);
            z1[x + y*N] = z_x + (complex long double)_Complex_I*z_y;
        }
    }

    puts("Functions: tmpl_CLDouble_Abs vs cabsl");
    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            y0[x + y*N] = tmpl_CLDouble_Abs(z0[x + y*N]);
    t2 = clock();
    printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            y1[x + y*N] = cabsl(z1[x + y*N]);
    t2 = clock();
    printf("c99:     %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    max_abs = 0.0L;
    max_rel = 0.0L;
    for (x = 0U; x < N; ++x)
    {
        for (y = 0U; y < N; ++y)
        {
            temp = y0[x + y*N] - y1[x + y*N];
            if (temp < 0.0L)
                temp = -temp;

            if (max_abs < temp)
                max_abs = temp;

            temp = (y0[x + y*N] - y1[x + y*N])/y1[x + y*N];
            if (temp < 0.0L)
                temp = -temp;

            if (max_rel < temp)
                max_rel = temp;
        }
    }

    printf("Max Abs Error: %.24Le\n", max_abs);
    printf("Max Rel Error: %.24Le\n", max_rel);

    /*  Free all of the memory allocated.                                     */
    free(y0);
    free(y1);
    free(z0);
    free(z1);
    return 0;
}
/*  End of main.                                                              */

