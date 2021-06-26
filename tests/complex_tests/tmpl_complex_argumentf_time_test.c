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
#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*  Routine for testing tmpl_CFloat_Argument.                                 */
int main(void)
{
    float **y0, **y1;
    tmpl_ComplexFloat **z0;
    complex float **z1;

    const unsigned int N = 10000U;
    const float start = -100.0F;
    const float end = 100.0F;
    const float ds = (end - start) / (float)(N - 1U);

    unsigned int x, y;
    clock_t t1, t2;
    float z_x, z_y, max_rel, max_abs, temp;

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
            z_x = (float)x*ds + start;
            z_y = (float)y*ds + start;
            z0[x][y] = tmpl_CFloat_Rect(z_x, z_y);
            z1[x][y] = z_x + _Complex_I*z_y;
        }
    }

    puts("Functions: tmpl_CFloat_Argument vs cargf");
    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            y0[x][y] = tmpl_CFloat_Argument(z0[x][y]);
    t2 = clock();
    printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)
            y1[x][y] = cargf(z1[x][y]);
    t2 = clock();
    printf("c99:     %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    max_abs = 0.0F;
    max_rel = 0.0F;
    for (x = 0U; x < N; ++x)
    {
        for (y = 0U; y < N; ++y)
        {
            temp = y0[x][y] - y1[x][y];
            if (temp < 0.0F)
                temp = -temp;

            if (max_abs < temp)
                max_abs = temp;

            temp = (y0[x][y] - y1[x][y])/y1[x][y];
            if (temp < 0.0F)
                temp = -temp;

            if (max_rel < temp)
                max_rel = temp;
        }
    }

    printf("Max Abs Error: %.8f\n", (double)max_abs);
    printf("Max Rel Error: %.8f\n", (double)max_rel);

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

