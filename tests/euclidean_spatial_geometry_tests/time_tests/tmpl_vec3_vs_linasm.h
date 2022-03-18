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

static inline long double rand_real(void)
{
    int n = rand();
    return (long double)n / (long double)(RAND_MAX);
}

#define TEST1(ctype, ttype, ltype, f0, f1, samples)                            \
int main(void)                                                                 \
{                                                                              \
    ttype *X, *Y, *Z;                                                          \
    struct ltype *A, *B, *C;                                                   \
    const unsigned long long int N = samples;                                  \
    unsigned long long int n;                                                  \
    clock_t t1, t2;                                                            \
    long double x_max = 0.0L;                                                  \
    long double y_max = 0.0L;                                                  \
    long double z_max = 0.0L;                                                  \
    long double x_rms = 0.0L;                                                  \
    long double y_rms = 0.0L;                                                  \
    long double z_rms = 0.0L;                                                  \
    long double tmp = 0.0L;                                                    \
                                                                               \
    X = malloc(sizeof(*X) * N);                                                \
                                                                               \
    if (!X)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for X. Aborting.");              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    Y = malloc(sizeof(*Y) * N);                                                \
                                                                               \
    if (!Y)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for Y. Aborting.");              \
        free(X);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    Z = malloc(sizeof(*Z) * N);                                                \
                                                                               \
    if (!Z)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for Z. Aborting.");              \
        free(X);                                                               \
        free(Y);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    A = malloc(sizeof(*A) * N);                                                \
                                                                               \
    if (!A)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for A. Aborting.");              \
        free(X);                                                               \
        free(Y);                                                               \
        free(Z);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    B = malloc(sizeof(*B) * N);                                                \
                                                                               \
    if (!B)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for B. Aborting.");              \
        free(X);                                                               \
        free(Y);                                                               \
        free(Z);                                                               \
        free(A);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    C = malloc(sizeof(*C) * N);                                                \
                                                                               \
    if (!C)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for C. Aborting.");              \
        free(X);                                                               \
        free(Y);                                                               \
        free(Z);                                                               \
        free(A);                                                               \
        free(B);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        long double u0 = rand_real();                                          \
        long double u1 = rand_real();                                          \
        long double u2 = rand_real();                                          \
        long double v0 = rand_real();                                          \
        long double v1 = rand_real();                                          \
        long double v2 = rand_real();                                          \
                                                                               \
        X[n].dat[0] = (ctype)u0;                                               \
        X[n].dat[1] = (ctype)u1;                                               \
        X[n].dat[2] = (ctype)u2;                                               \
                                                                               \
        Y[n].dat[0] = (ctype)v0;                                               \
        Y[n].dat[1] = (ctype)v1;                                               \
        Y[n].dat[2] = (ctype)v2;                                               \
                                                                               \
        A[n].x = (ctype)u0;                                                    \
        A[n].y = (ctype)u1;                                                    \
        A[n].z = (ctype)u2;                                                    \
                                                                               \
        B[n].x = (ctype)v0;                                                    \
        B[n].y = (ctype)v1;                                                    \
        B[n].z = (ctype)v2;                                                    \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1"\n");                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        Z[n] = f0(&X[n], &Y[n]);                                               \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        C[n] = A[n];                                                           \
        f1(&C[n], &B[n]);                                                      \
    }                                                                          \
    t2 = clock();                                                              \
    printf("linasm:  %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        tmp = fabsl((long double)(Z[n].dat[0] - C[n].x));                      \
        x_rms += tmp*tmp;                                                      \
                                                                               \
        if (x_max < tmp)                                                       \
            x_max = tmp;                                                       \
                                                                               \
        tmp = fabsl((long double)(Z[n].dat[1] - C[n].y));                      \
        y_rms += tmp*tmp;                                                      \
                                                                               \
        if (y_max < tmp)                                                       \
            y_max = tmp;                                                       \
                                                                               \
        tmp = fabsl((long double)(Z[n].dat[2] - C[n].z));                      \
        z_rms += tmp*tmp;                                                      \
                                                                               \
        if (z_max < tmp)                                                       \
            z_max = tmp;                                                       \
    }                                                                          \
                                                                               \
    x_rms = sqrtl(x_rms / (long double)N);                                     \
    y_rms = sqrtl(y_rms / (long double)N);                                     \
    z_rms = sqrtl(z_rms / (long double)N);                                     \
                                                                               \
    printf("x max err: %Le\n", x_max);                                         \
    printf("y max err: %Le\n", y_max);                                         \
    printf("z max err: %Le\n", z_max);                                         \
    printf("x rms err: %Le\n", x_rms);                                         \
    printf("y rms err: %Le\n", y_rms);                                         \
    printf("z rms err: %Le\n", z_rms);                                         \
                                                                               \
    free(A);                                                                   \
    free(B);                                                                   \
    free(C);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    free(Z);                                                                   \
    return 0;                                                                  \
}

#define TEST2(ctype, ttype, ltype, f0, f1, samples)                            \
int main(void)                                                                 \
{                                                                              \
    ttype *X, *Y;                                                              \
    struct ltype *A, *B;                                                       \
    const unsigned long long int N = samples;                                  \
    unsigned long long int n;                                                  \
    clock_t t1, t2;                                                            \
    long double x_max = 0.0L;                                                  \
    long double y_max = 0.0L;                                                  \
    long double z_max = 0.0L;                                                  \
    long double x_rms = 0.0L;                                                  \
    long double y_rms = 0.0L;                                                  \
    long double z_rms = 0.0L;                                                  \
    long double tmp = 0.0L;                                                    \
                                                                               \
    X = malloc(sizeof(*X) * N);                                                \
                                                                               \
    if (!X)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for X. Aborting.");              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    Y = malloc(sizeof(*Y) * N);                                                \
                                                                               \
    if (!Y)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for Y. Aborting.");              \
        free(X);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    A = malloc(sizeof(*A) * N);                                                \
                                                                               \
    if (!A)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for A. Aborting.");              \
        free(X);                                                               \
        free(Y);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    B = malloc(sizeof(*B) * N);                                                \
                                                                               \
    if (!B)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for B. Aborting.");              \
        free(X);                                                               \
        free(Y);                                                               \
        free(A);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        long double u0 = rand_real();                                          \
        long double u1 = rand_real();                                          \
        long double u2 = rand_real();                                          \
        long double v0 = rand_real();                                          \
        long double v1 = rand_real();                                          \
        long double v2 = rand_real();                                          \
                                                                               \
        X[n].dat[0] = (ctype)u0;                                               \
        X[n].dat[1] = (ctype)u1;                                               \
        X[n].dat[2] = (ctype)u2;                                               \
                                                                               \
        Y[n].dat[0] = (ctype)v0;                                               \
        Y[n].dat[1] = (ctype)v1;                                               \
        Y[n].dat[2] = (ctype)v2;                                               \
                                                                               \
        A[n].x = (ctype)u0;                                                    \
        A[n].y = (ctype)u1;                                                    \
        A[n].z = (ctype)u2;                                                    \
                                                                               \
        B[n].x = (ctype)v0;                                                    \
        B[n].y = (ctype)v1;                                                    \
        B[n].z = (ctype)v2;                                                    \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1"\n");                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        f0(&Y[n], &X[n]);                                                      \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        f1(&B[n], &A[n]);                                                      \
    t2 = clock();                                                              \
    printf("linasm:  %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        tmp = fabsl((long double)(Y[n].dat[0] - B[n].x));                      \
        x_rms += tmp*tmp;                                                      \
                                                                               \
        if (x_max < tmp)                                                       \
            x_max = tmp;                                                       \
                                                                               \
        tmp = fabsl((long double)(Y[n].dat[1] - B[n].y));                      \
        y_rms += tmp*tmp;                                                      \
                                                                               \
        if (y_max < tmp)                                                       \
            y_max = tmp;                                                       \
                                                                               \
        tmp = fabsl((long double)(Y[n].dat[2] - B[n].z));                      \
        z_rms += tmp*tmp;                                                      \
                                                                               \
        if (z_max < tmp)                                                       \
            z_max = tmp;                                                       \
    }                                                                          \
                                                                               \
    x_rms = sqrtl(x_rms / (long double)N);                                     \
    y_rms = sqrtl(y_rms / (long double)N);                                     \
    z_rms = sqrtl(z_rms / (long double)N);                                     \
                                                                               \
    printf("x max err: %Le\n", x_max);                                         \
    printf("y max err: %Le\n", y_max);                                         \
    printf("z max err: %Le\n", z_max);                                         \
    printf("x rms err: %Le\n", x_rms);                                         \
    printf("y rms err: %Le\n", y_rms);                                         \
    printf("z rms err: %Le\n", z_rms);                                         \
                                                                               \
    free(A);                                                                   \
    free(B);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    return 0;                                                                  \
}
