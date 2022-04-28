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

#include <libtmpl/include/tmpl_complex.h>

/*  2 pi is defined here.                                                     */
#include <libtmpl/include/tmpl_math.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static double abs_err(tmpl_ComplexDouble z, complex double w)
{
    double x = tmpl_CDouble_Real_Part(z) - creal(w);
    double y = tmpl_CDouble_Imag_Part(z) - cimag(w);
    return sqrt(x*x + y*y);
}

static double rel_err(tmpl_ComplexDouble z, complex double w)
{
    double x = tmpl_CDouble_Real_Part(z) - creal(w);
    double y = tmpl_CDouble_Imag_Part(z) - cimag(w);
    return sqrt(x*x + y*y) / cabs(w);
}

/*  Routine for testing tmpl_CDouble_Add_Imag.                                */
int main(void)
{
    tmpl_ComplexDouble **z0, **z1;
    complex double **w0, **w1;

    const unsigned int N = 10000U;
    const double imag = 1.0;

    double z_x, z_y, max_rel, max_abs, temp, r, theta;
    unsigned int x, y;
    clock_t t1, t2;

    z0 = malloc(sizeof(*z0) * N);
    z1 = malloc(sizeof(*z1) * N);
    w0 = malloc(sizeof(*w0) * N);
    w1 = malloc(sizeof(*w1) * N);

    for (x = 0U; x < N; ++x)
    {
        z0[x] = malloc(sizeof(*z0[x]) * N);
        z1[x] = malloc(sizeof(*z1[x]) * N);
        w0[x] = malloc(sizeof(*w0[x]) * N);
        w1[x] = malloc(sizeof(*w1[x]) * N);
    }

    for (x = 0U; x < N; ++x)
    {
        for (y = 0U; y < N; ++y)
        {
            theta = tmpl_Two_Pi*rand() / (double)RAND_MAX;
            r = rand();
            z_x = r*cos(theta);
            z_y = r*sin(theta);
            z0[x][y] = tmpl_CDouble_Rect(z_x, z_y);
            w0[x][y] = z_x + (complex double)_Complex_I*z_y;
        }
    }

    puts("Functions: tmpl_CDouble_Add_Imag vs complex addition");
    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            z1[x][y] = tmpl_CDouble_Add_Imag(imag, z0[x][y]);
    t2 = clock();
    printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            w1[x][y] = w0[x][y] + (complex double)_Complex_I*imag;
    t2 = clock();
    printf("c99:     %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    max_abs = 0.0;
    max_rel = 0.0;
    for (x = 0U; x < N; ++x)
    {
        for (y = 0U; y < N; ++y)
        {
            temp = abs_err(z1[x][y], w1[x][y]);

            if (max_abs < temp)
                max_abs = temp;

            temp = rel_err(z1[x][y], w1[x][y]);

            if (max_rel < temp)
                max_rel = temp;
        }
    }

    printf("Max Abs Error: %.16f\n", max_abs);
    printf("Max Rel Error: %.16f\n", max_rel);

    for (x = 0U; x < N; ++x)
    {
        free(z0[x]);
        free(z1[x]);
        free(w0[x]);
        free(w1[x]);
    }

    free(z0);
    free(z1);
    free(w0);
    free(w1);
    return 0;
}
/*  End of main.                                                              */

