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

static inline long double rand_real(void)
{
    int n = rand();
    return (long double)n / (long double)(RAND_MAX);
}

#define TEST1(fname, samples)                                                  \
int main(void)                                                                 \
{                                                                              \
    tmpl_ThreeVectorDouble *X, *Y, *Z;                                         \
    tmpl_ThreeVectorLongDouble *A, *B, *C;                                     \
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
        X[n].dat[0] = (double)u0;                                              \
        X[n].dat[1] = (double)u1;                                              \
        X[n].dat[2] = (double)u2;                                              \
                                                                               \
        Y[n].dat[0] = (double)v0;                                              \
        Y[n].dat[1] = (double)v1;                                              \
        Y[n].dat[2] = (double)v2;                                              \
                                                                               \
        A[n].dat[0] = u0;                                                      \
        A[n].dat[1] = u1;                                                      \
        A[n].dat[2] = u2;                                                      \
                                                                               \
        B[n].dat[0] = v0;                                                      \
        B[n].dat[1] = v1;                                                      \
        B[n].dat[2] = v2;                                                      \
    }                                                                          \
                                                                               \
    printf("tmpl_3DDouble_" #fname " vs. tmpl_3DLDouble_" #fname"\n");         \
    printf("samples: %llu\n", N);                                              \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        Z[n] = tmpl_3DDouble_##fname(&X[n], &Y[n]);                            \
    t2 = clock();                                                              \
    printf("double:      %f seconds\n",(double)(t2-t1)/(double)CLOCKS_PER_SEC);\
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        C[n] = tmpl_3DLDouble_##fname(&A[n], &B[n]);                           \
    t2 = clock();                                                              \
    printf("long double: %f seconds\n",(double)(t2-t1)/(double)CLOCKS_PER_SEC);\
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        tmp = fabsl((long double)Z[n].dat[0] - C[n].dat[0]);                   \
        x_rms += tmp*tmp;                                                      \
                                                                               \
        if (x_max < tmp)                                                       \
            x_max = tmp;                                                       \
                                                                               \
        tmp = fabsl((long double)Z[n].dat[1] - C[n].dat[1]);                   \
        y_rms += tmp*tmp;                                                      \
                                                                               \
        if (y_max < tmp)                                                       \
            y_max = tmp;                                                       \
                                                                               \
        tmp = fabsl((long double)Z[n].dat[2] - C[n].dat[2]);                   \
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

#define TEST2(fname, samples)                                                  \
int main(void)                                                                 \
{                                                                              \
    tmpl_ThreeVectorDouble *X, *Y;                                             \
    tmpl_ThreeVectorLongDouble *A, *B;                                         \
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
        X[n].dat[0] = (double)u0;                                              \
        X[n].dat[1] = (double)u1;                                              \
        X[n].dat[2] = (double)u2;                                              \
                                                                               \
        Y[n].dat[0] = (double)v0;                                              \
        Y[n].dat[1] = (double)v1;                                              \
        Y[n].dat[2] = (double)v2;                                              \
                                                                               \
        A[n].dat[0] = u0;                                                      \
        A[n].dat[1] = u1;                                                      \
        A[n].dat[2] = u2;                                                      \
                                                                               \
        B[n].dat[0] = v0;                                                      \
        B[n].dat[1] = v1;                                                      \
        B[n].dat[2] = v2;                                                      \
    }                                                                          \
                                                                               \
    printf("tmpl_3DDouble_" #fname " vs. tmpl_3DLDouble_" #fname"\n");         \
    printf("samples: %llu\n", N);                                              \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        tmpl_3DDouble_##fname(&X[n], &Y[n]);                                   \
    t2 = clock();                                                              \
    printf("double:      %f seconds\n",(double)(t2-t1)/(double)CLOCKS_PER_SEC);\
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        tmpl_3DLDouble_##fname(&A[n], &B[n]);                                  \
    t2 = clock();                                                              \
    printf("long double: %f seconds\n",(double)(t2-t1)/(double)CLOCKS_PER_SEC);\
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        tmp = fabsl((long double)X[n].dat[0] - A[n].dat[0]);                   \
        x_rms += tmp*tmp;                                                      \
                                                                               \
        if (x_max < tmp)                                                       \
            x_max = tmp;                                                       \
                                                                               \
        tmp = fabsl((long double)X[n].dat[1] - A[n].dat[1]);                   \
        y_rms += tmp*tmp;                                                      \
                                                                               \
        if (y_max < tmp)                                                       \
            y_max = tmp;                                                       \
                                                                               \
        tmp = fabsl((long double)X[n].dat[2] - A[n].dat[2]);                   \
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

#define TEST3(fname, samples)                                                  \
int main(void)                                                                 \
{                                                                              \
    tmpl_ThreeVectorDouble *X, *Y;                                             \
    tmpl_ThreeVectorLongDouble *A, *B;                                         \
    double *Z;                                                                 \
    long double *C;                                                            \
    const unsigned long long int N = samples;                                  \
    unsigned long long int n;                                                  \
    clock_t t1, t2;                                                            \
    long double max_err = 0.0L;                                                \
    long double rms_err = 0.0L;                                                \
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
        X[n].dat[0] = (double)u0;                                              \
        X[n].dat[1] = (double)u1;                                              \
        X[n].dat[2] = (double)u2;                                              \
                                                                               \
        Y[n].dat[0] = (double)v0;                                              \
        Y[n].dat[1] = (double)v1;                                              \
        Y[n].dat[2] = (double)v2;                                              \
                                                                               \
        A[n].dat[0] = u0;                                                      \
        A[n].dat[1] = u1;                                                      \
        A[n].dat[2] = u2;                                                      \
                                                                               \
        B[n].dat[0] = v0;                                                      \
        B[n].dat[1] = v1;                                                      \
        B[n].dat[2] = v2;                                                      \
    }                                                                          \
                                                                               \
    printf("tmpl_3DDouble_" #fname " vs. tmpl_3DLDouble_" #fname"\n");         \
    printf("samples: %llu\n", N);                                              \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        Z[n] = tmpl_3DDouble_##fname(&X[n], &Y[n]);                                   \
    t2 = clock();                                                              \
    printf("double:      %f seconds\n",(double)(t2-t1)/(double)CLOCKS_PER_SEC);\
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        C[n] = tmpl_3DLDouble_##fname(&A[n], &B[n]);                                  \
    t2 = clock();                                                              \
    printf("long double: %f seconds\n",(double)(t2-t1)/(double)CLOCKS_PER_SEC);\
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        tmp = fabsl((long double)Z[n] - C[n]);                                 \
        rms_err += tmp*tmp;                                                    \
                                                                               \
        if (max_err < tmp)                                                     \
            max_err = tmp;                                                     \
    }                                                                          \
                                                                               \
    rms_err = sqrtl(rms_err / (long double)N);                                 \
                                                                               \
    printf("max err: %Le\n", max_err);                                         \
    printf("rms err: %Le\n", rms_err);                                         \
                                                                               \
    free(A);                                                                   \
    free(B);                                                                   \
    free(C);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    free(Z);                                                                   \
    return 0;                                                                  \
}
