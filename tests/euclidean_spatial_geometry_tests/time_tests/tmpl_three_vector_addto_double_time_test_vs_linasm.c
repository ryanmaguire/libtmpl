/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>
#include <Vector3D.h>

static double rand_real(void)
{
    int n = rand();
    return (double)n / (double)(RAND_MAX);
}

int main(void)
{
    tmpl_ThreeVectorDouble *X, *Y;
    struct v3D64_t *A, *B;
    const unsigned int N = 10000000U;
    unsigned int n;
    clock_t t1, t2;
    double x_max = 0.0;
    double y_max = 0.0;
    double z_max = 0.0;
    double x_rms = 0.0;
    double y_rms = 0.0;
    double z_rms = 0.0;
    double tmp = 0.0;

    X = malloc(sizeof(*X) * N);

    if (!X)
    {
        puts("malloc failed and returned NULL for X. Aborting.");
        return -1;
    }

    Y = malloc(sizeof(*Y) * N);

    if (!Y)
    {
        puts("malloc failed and returned NULL for Y. Aborting.");
        free(X);
        return -1;
    }

    A = malloc(sizeof(*A) * N);

    if (!A)
    {
        puts("malloc failed and returned NULL for A. Aborting.");
        free(X);
        free(Y);
        return -1;
    }

    B = malloc(sizeof(*B) * N);

    if (!B)
    {
        puts("malloc failed and returned NULL for B. Aborting.");
        free(X);
        free(Y);
        free(A);
        return -1;
    }

    for (n = 0U; n < N; ++n)
    {
        double u0 = rand_real();
        double u1 = rand_real();
        double u2 = rand_real();
        double v0 = rand_real();
        double v1 = rand_real();
        double v2 = rand_real();

        X[n] = tmpl_3DDouble_Rect(u0, u1, u2);
        Y[n] = tmpl_3DDouble_Rect(v0, v1, v2);

        A[n].x = u0;
        A[n].y = u1;
        A[n].z = u2;

        B[n].x = v0;
        B[n].y = v1;
        B[n].z = v2;
    }

    t1 = clock();
    for (n = 0U; n < N; ++n)
        tmpl_3DDouble_AddTo(&X[n], &Y[n]);
    t2 = clock();
    printf("libtmpl: %e\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0U; n < N; ++n)
        Vector3D_Add_flt64(&A[n], &B[n]);
    t2 = clock();
    printf("linasm:  %e\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);

    for (n = 0U; n < N; ++n)
    {
        tmp = fabs(X[n].dat[0] - A[n].x);
        x_rms += tmp*tmp;

        if (x_max < tmp)
            x_max = tmp;

        tmp = fabs(X[n].dat[1] - A[n].y);
        y_rms += tmp*tmp;

        if (y_max < tmp)
            y_max = tmp;

        tmp = fabs(X[n].dat[2] - A[n].z);
        z_rms += tmp*tmp;

        if (z_max < tmp)
            z_max = tmp;
    }

    x_rms = sqrt(x_rms / (double)N);
    y_rms = sqrt(y_rms / (double)N);
    z_rms = sqrt(z_rms / (double)N);

    printf("x max err: %e\n", x_max);
    printf("y max err: %e\n", y_max);
    printf("z max err: %e\n", z_max);
    printf("x rms err: %e\n", x_rms);
    printf("y rms err: %e\n", y_rms);
    printf("z rms err: %e\n", z_rms);

    free(A);
    free(B);
    free(X);
    free(Y);
}
