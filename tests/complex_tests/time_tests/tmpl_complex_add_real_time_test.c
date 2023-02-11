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

#ifdef _WIN32
#define ctype _Dcomplex
#define cconstruct _Cbuild
#else
#define ctype complex double
static inline complex double complex_double_construct(double real, double imag) { return u0 + (complex double)_Complex_I*u1; }
#define cconstruct complex_double_construct
#endif

static double abs_err(tmpl_ComplexDouble z, ctype w)
{
    double x = tmpl_CDouble_Real_Part(z) - creal(w);
    double y = tmpl_CDouble_Imag_Part(z) - cimag(w);
    return sqrt(x*x + y*y);
}

static double rel_err(tmpl_ComplexDouble z, ctype w)
{
    double x = tmpl_CDouble_Real_Part(z) - creal(w);
    double y = tmpl_CDouble_Imag_Part(z) - cimag(w);
    return sqrt(x*x + y*y) / cabs(w);
}

/*  Routine for testing tmpl_CDouble_Add_Real.                                */
int main(void)
{
    tmpl_ComplexDouble **z0, **z1;
    ctype **w0, **w1;

    const unsigned int N = 10000U;
    const double real = 1.0;

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
            w0[x][y] = cconstruct(z_x, z_y);
        }
    }

    puts("Functions: tmpl_CDouble_Add_Real vs complex addition");
    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            z1[x][y] = tmpl_CDouble_Add_Real(real, z0[x][y]);
    t2 = clock();
    printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            w1[x][y] = cconstruct(creal(w0[x][y]) + real, cimag(w0[x][y]));
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

