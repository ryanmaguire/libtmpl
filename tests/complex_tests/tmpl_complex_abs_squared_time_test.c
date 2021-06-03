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

#include <libtmpl/include/tmpl_complex.h>
#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static double complex_abs_squared(complex double z)
{
    double x = creal(z);
    double y = cimag(z);
    return x*x + y*y;
}

/*  Routine for testing tmpl_CDouble_Abs_Squared.                             */
int main(void)
{
    double **y0, **y1;
    tmpl_ComplexDouble **z0;
    complex double **z1;

    const unsigned int N = 10000U;
    const double start = -100.0;
    const double end =  100.0;
    const double ds = (end - start) / (double)(N - 1U);

    unsigned int x, y;
    clock_t t1, t2;
    double z_x, z_y, max_rel, max_abs, temp;

    y0 = malloc(sizeof(*y0) * N);
    y1 = malloc(sizeof(*y1) * N);
    z0 = malloc(sizeof(*z0) * N);
    z1 = malloc(sizeof(*z1) * N);

    for (x = 0U; x < N; ++x)
    {
        y0[x] = malloc(sizeof(*y0[x]) * N);
        y1[x] = malloc(sizeof(*y1[x]) * N);
        z0[x] = malloc(sizeof(*z0[x]) * N);
        z1[x] = malloc(sizeof(*z1[x]) * N);
    }

    for (x = 0U; x < N; ++x)
    {
        for (y = 0U; y < N; ++y)
        {
            z_x = (double)x*ds + start;
            z_y = (double)y*ds + start;
            z0[x][y] = tmpl_CDouble_Rect(z_x, z_y);
            z1[x][y] = z_x + (complex double)_Complex_I*z_y;
        }
    }

    puts("Functions: tmpl_CDouble_Abs_Squared vs complex_abs_squared");
    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            y0[x][y] = tmpl_CDouble_Abs_Squared(z0[x][y]);
    t2 = clock();
    printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            y1[x][y] = complex_abs_squared(z1[x][y]);
    t2 = clock();
    printf("c99:     %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    max_abs = 0.0;
    max_rel = 0.0;
    for (x = 0U; x < N; ++x)
    {
        for (y = 0U; y < N; ++y)
        {
            temp = y0[x][y] - y1[x][y];
            if (temp < 0.0)
                temp = -temp;

            if (max_abs < temp)
                max_abs = temp;

            temp = (y0[x][y] - y1[x][y])/y1[x][y];
            if (temp < 0.0)
                temp = -temp;

            if (max_rel < temp)
                max_rel = temp;
        }
    }

    printf("Max Abs Error: %.16f\n", max_abs);
    printf("Max Rel Error: %.16f\n", max_rel);

    for (x = 0U; x < N; ++x)
    {
        free(y0[x]);
        free(y1[x]);
        free(z0[x]);
        free(z1[x]);
    }

    free(y0);
    free(y1);
    free(z0);
    free(z1);

    return 0;
}
/*  End of main.                                                              */

