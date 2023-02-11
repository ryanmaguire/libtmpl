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
#define ctype _Lcomplex
#define cconstruct _LCbuild
#else
#define ctype complex long double
static inline complex long double complex_long_double_construct(long double real, long double imag) { return u0 + (complex long double)_Complex_I*u1; }
#define cconstruct complex_long_double_construct
#endif

static long double abs_err(tmpl_ComplexLongDouble z, ctype w)
{
    long double x = tmpl_CLDouble_Real_Part(z) - creall(w);
    long double y = tmpl_CLDouble_Imag_Part(z) - cimagl(w);
    return sqrtl(x*x + y*y);
}

static long double rel_err(tmpl_ComplexLongDouble z, ctype w)
{
    long double x = tmpl_CLDouble_Real_Part(z) - creall(w);
    long double y = tmpl_CLDouble_Imag_Part(z) - cimagl(w);
    return sqrtl(x*x + y*y) / cabsl(w);
}


/*  Routine for testing tmpl_CLDouble_Add.                                    */
int main(void)
{
    tmpl_ComplexLongDouble **z0, **z1;
    ctype **w0, **w1;

    const unsigned int N = 10000U;
    const tmpl_ComplexLongDouble z = tmpl_CLDouble_Rect(1.0L, 2.0L);
    const ctype w = cconstruct(1.0L, 2.0L);

    long double z_x, z_y, max_rel, max_abs, temp, r, theta;
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
            theta = tmpl_Two_Pi_L*rand() / (long double)RAND_MAX;
            r = rand();
            z_x = r*cosl(theta);
            z_y = r*sinl(theta);
            z0[x][y] = tmpl_CLDouble_Rect(z_x, z_y);
            w0[x][y] = cconstruct(z_x, z_y);
        }
    }

    puts("Functions: tmpl_CLDouble_Add vs complex addition");
    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            z1[x][y] = tmpl_CLDouble_Add(z0[x][y], z);
    t2 = clock();
    printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            w1[x][y] = cconstruct(creall(w0[x][y]) + creall(w), cimagl(w0[x][y]) + cimagl(w));
    t2 = clock();
    printf("c99:     %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    max_abs = 0.0L;
    max_rel = 0.0L;
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

    printf("Max Abs Error: %.24Lf\n", max_abs);
    printf("Max Rel Error: %.24Lf\n", max_rel);

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

