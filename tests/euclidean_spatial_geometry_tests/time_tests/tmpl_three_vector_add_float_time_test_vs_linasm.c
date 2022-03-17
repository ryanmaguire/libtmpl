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

static float rand_real(void)
{
    int n = rand();
    return (float)n / (float)(RAND_MAX);
}

int main(void)
{
    tmpl_ThreeVectorFloat *X, *Y, *Z;
    struct v3D32_t *A, *B, *C;
    const unsigned int N = 10000000U;
    unsigned int n;
    clock_t t1, t2;
    float x_max = 0.0;
    float y_max = 0.0;
    float z_max = 0.0;
    float x_rms = 0.0;
    float y_rms = 0.0;
    float z_rms = 0.0;
    float tmp = 0.0;

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

    Z = malloc(sizeof(*Z) * N);

    if (!Z)
    {
        puts("malloc failed and returned NULL for Z. Aborting.");
        free(X);
        free(Y);
        return -1;
    }

    A = malloc(sizeof(*A) * N);

    if (!A)
    {
        puts("malloc failed and returned NULL for A. Aborting.");
        free(X);
        free(Y);
        free(Z);
        return -1;
    }

    B = malloc(sizeof(*B) * N);

    if (!B)
    {
        puts("malloc failed and returned NULL for B. Aborting.");
        free(X);
        free(Y);
        free(Z);
        free(A);
        return -1;
    }

    C = malloc(sizeof(*C) * N);

    if (!C)
    {
        puts("malloc failed and returned NULL for C. Aborting.");
        free(X);
        free(Y);
        free(Z);
        free(A);
        free(B);
        return -1;
    }

    for (n = 0U; n < N; ++n)
    {
        float u0 = rand_real();
        float u1 = rand_real();
        float u2 = rand_real();
        float v0 = rand_real();
        float v1 = rand_real();
        float v2 = rand_real();

        X[n] = tmpl_3DFloat_Rect(u0, u1, u2);
        Y[n] = tmpl_3DFloat_Rect(v0, v1, v2);

        A[n].x = u0;
        A[n].y = u1;
        A[n].z = u2;

        B[n].x = v0;
        B[n].y = v1;
        B[n].z = v2;
    }

    t1 = clock();
    for (n = 0U; n < N; ++n)
        Z[n] = tmpl_3DFloat_Add(X[n], Y[n]);
    t2 = clock();
    printf("libtmpl: %e\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0U; n < N; ++n)
    {
        C[n] = A[n];
        Vector3D_Add_flt32(&C[n], &B[n]);
    }
    t2 = clock();
    printf("linasm:  %e\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);

    for (n = 0U; n < N; ++n)
    {
        tmp = fabsf(Z[n].dat[0] - C[n].x);
        x_rms += tmp*tmp;

        if (x_max < tmp)
            x_max = tmp;

        tmp = fabsf(Z[n].dat[1] - C[n].y);
        y_rms += tmp*tmp;

        if (y_max < tmp)
            y_max = tmp;

        tmp = fabsf(Z[n].dat[2] - C[n].z);
        z_rms += tmp*tmp;

        if (z_max < tmp)
            z_max = tmp;
    }

    x_rms = sqrtf(x_rms / (float)N);
    y_rms = sqrtf(y_rms / (float)N);
    z_rms = sqrtf(z_rms / (float)N);

    printf("x max err: %e\n", (double)x_max);
    printf("y max err: %e\n", (double)y_max);
    printf("z max err: %e\n", (double)z_max);
    printf("x rms err: %e\n", (double)x_rms);
    printf("y rms err: %e\n", (double)y_rms);
    printf("z rms err: %e\n", (double)z_rms);

    free(A);
    free(B);
    free(C);
    free(X);
    free(Y);
    free(Z);
}
