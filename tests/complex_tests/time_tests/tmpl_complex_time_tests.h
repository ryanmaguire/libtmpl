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
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <time.h>

#ifndef TMPL_NSAMPS
#ifdef _MSC_VER
#include <windows.h>
static size_t memsize()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return (size_t)status.ullTotalPhys;
}
#else
#include <unistd.h>
static size_t memsize()
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return (size_t)(pages * page_size);
}
#endif
#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) MAX2((a), MAX2((b), (c)))
#define NSAMPS(a, b, c) (memsize()/(2ULL*MAX3(sizeof(a), sizeof(b), sizeof(c))))
#else
#define NSAMPS(a, b, c) TMPL_NSAMPS
#endif

#ifdef IMPART
#undef IMPART
#endif
#define IMPART(x) _Generic((x),   \
    long double complex: cimagl,  \
    default: cimag,               \
    float complex: cimagf         \
)(x)

#ifdef REPART
#undef REPART
#endif
#define REPART(x) _Generic((x),   \
    complex long double: creall,  \
    default: creal,               \
    complex float: crealf         \
)(x)

static inline long double rand_real(void)
{
    int n = rand();
    long double x = (long double)n / (long double)(RAND_MAX);
    return 2.0L*(x - 0.5L);
}

#define TEST1(ftype, ttype, ctype, f0, f1)                                     \
int main(void)                                                                 \
{                                                                              \
    ttype *X;                                                                  \
    ctype *A;                                                                  \
    ftype *Y, *B;                                                              \
    const size_t N = NSAMPS(ftype, ttype, ctype) / 4UL;                        \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double max_err = 0.0L;                                                \
    long double rel_err = 0.0L;                                                \
    long double tmp = 0.0L;                                                    \
    const ftype zero = (ftype)0;                                               \
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
                                                                               \
        X[n].dat[0] = (ftype)u0;                                               \
        X[n].dat[1] = (ftype)u1;                                               \
                                                                               \
        A[n] = (ftype)u0 + (complex ftype)_Complex_I*(ftype)u1;                \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1"\n");                                               \
    printf("samples: %zu\n", N);                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        Y[n] = f0(X[n]);                                                       \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        B[n] = f1(A[n]);                                                       \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        if (B[n] != zero)                                                      \
        {                                                                      \
            tmp = fabsl((long double)((Y[n] - B[n])/B[n]));                    \
            rel_err += tmp*tmp;                                                \
                                                                               \
            if (max_err < tmp)                                                 \
                max_err = tmp;                                                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    rel_err = sqrtl(rel_err / (long double)N);                                 \
                                                                               \
    printf("max err: %Le\n", max_err);                                         \
    printf("rel err: %Le\n", rel_err);                                         \
    free(A);                                                                   \
    free(B);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    return 0;                                                                  \
}

#define TEST2(ftype, ttype, ctype, f, op)                                      \
int main(void)                                                                 \
{                                                                              \
    ttype *X, *Y, *Z;                                                          \
    ctype *A, *B, *C;                                                          \
    const size_t N = NSAMPS(ftype, ttype, ctype) / 6UL;                        \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double max_err = 0.0L;                                                \
    long double rel_err = 0.0L;                                                \
    long double tmp = 0.0L;                                                    \
    ftype dx, dy;                                                              \
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
        long double v0 = rand_real();                                          \
        long double v1 = rand_real();                                          \
                                                                               \
        X[n].dat[0] = (ftype)u0;                                               \
        X[n].dat[1] = (ftype)u1;                                               \
        Y[n].dat[0] = (ftype)v0;                                               \
        Y[n].dat[1] = (ftype)v1;                                               \
                                                                               \
        A[n] = (ftype)u0 + (complex ftype)_Complex_I*(ftype)u1;                \
        B[n] = (ftype)v0 + (complex ftype)_Complex_I*(ftype)v1;                \
    }                                                                          \
                                                                               \
    printf(#f " vs. " #op"\n");                                                \
    printf("samples: %zu\n", N);                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        Z[n] = f(&X[n], &Y[n]);                                                \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        C[n] = A[n] op B[n];                                                   \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        dx = Z[n].dat[0] - REPART(C[n]);                                       \
        dy = Z[n].dat[1] - IMPART(C[n]);                                       \
        tmp = sqrtl((long double)(dx*dx) + (long double)(dy*dy));              \
        rel_err += tmp*tmp;                                                    \
                                                                               \
        if (max_err < tmp)                                                     \
            max_err = tmp;                                                     \
    }                                                                          \
                                                                               \
    rel_err = sqrtl(rel_err / (long double)N);                                 \
                                                                               \
    printf("max err: %Le\n", max_err);                                         \
    printf("rel err: %Le\n", rel_err);                                         \
    free(A);                                                                   \
    free(B);                                                                   \
    free(C);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    free(Z);                                                                   \
    return 0;                                                                  \
}

#define TEST3(ftype, ttype, ctype, f, op)                                      \
int main(void)                                                                 \
{                                                                              \
    ttype *X, *Y, *Z;                                                          \
    ctype *A, *B, *C;                                                          \
    const size_t N = NSAMPS(ftype, ttype, ctype) / 6UL;                        \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double max_err = 0.0L;                                                \
    long double rel_err = 0.0L;                                                \
    long double tmp = 0.0L;                                                    \
    ftype dx, dy;                                                              \
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
        long double v0 = rand_real();                                          \
        long double v1 = rand_real();                                          \
                                                                               \
        X[n].dat[0] = (ftype)u0;                                               \
        X[n].dat[1] = (ftype)u1;                                               \
        Y[n].dat[0] = (ftype)v0;                                               \
        Y[n].dat[1] = (ftype)v1;                                               \
                                                                               \
        A[n] = (ftype)u0 + (complex ftype)_Complex_I*(ftype)u1;                \
        B[n] = (ftype)v0 + (complex ftype)_Complex_I*(ftype)v1;                \
    }                                                                          \
                                                                               \
    printf(#f " vs. " #op"\n");                                                \
    printf("samples: %zu\n", N);                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        Z[n] = f(X[n], Y[n]);                                                  \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        C[n] = A[n] op B[n];                                                   \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        dx = Z[n].dat[0] - REPART(C[n]);                                       \
        dy = Z[n].dat[1] - IMPART(C[n]);                                       \
        tmp = sqrtl((long double)(dx*dx) + (long double)(dy*dy));              \
        rel_err += tmp*tmp;                                                    \
                                                                               \
        if (max_err < tmp)                                                     \
            max_err = tmp;                                                     \
    }                                                                          \
                                                                               \
    rel_err = sqrtl(rel_err / (long double)N);                                 \
                                                                               \
    printf("max err: %Le\n", max_err);                                         \
    printf("rel err: %Le\n", rel_err);                                         \
    free(A);                                                                   \
    free(B);                                                                   \
    free(C);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    free(Z);                                                                   \
    return 0;                                                                  \
}

#define TEST4(ftype, ttype, ctype, f, op)                                      \
int main(void)                                                                 \
{                                                                              \
    ttype *X, *Y;                                                              \
    ctype *A, *B;                                                              \
    const size_t N = NSAMPS(ftype, ttype, ctype) / 4UL;                        \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double max_err = 0.0L;                                                \
    long double rel_err = 0.0L;                                                \
    long double tmp = 0.0L;                                                    \
    ftype dx, dy;                                                              \
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
                                                                               \
        X[n].dat[0] = (ftype)u0;                                               \
        X[n].dat[1] = (ftype)u1;                                               \
        A[n] = (ftype)u0 + (complex ftype)_Complex_I*(ftype)u1;                \
    }                                                                          \
                                                                               \
    printf(#f " vs. " #op"\n");                                                \
    printf("samples: %zu\n", N);                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        f(&X[n], &Y[n]);                                                       \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        A[n] op B[n];                                                          \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        dx = Y[n].dat[0] - REPART(B[n]);                                       \
        dy = Y[n].dat[1] - IMPART(B[n]);                                       \
        tmp = sqrtl((long double)(dx*dx) + (long double)(dy*dy));              \
        rel_err += tmp*tmp;                                                    \
                                                                               \
        if (max_err < tmp)                                                     \
            max_err = tmp;                                                     \
    }                                                                          \
                                                                               \
    rel_err = sqrtl(rel_err / (long double)N);                                 \
                                                                               \
    printf("max err: %Le\n", max_err);                                         \
    printf("rel err: %Le\n", rel_err);                                         \
    free(A);                                                                   \
    free(B);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    return 0;                                                                  \
}

#define TEST5(ftype, ttype, ctype, f0, f1)                                     \
int main(void)                                                                 \
{                                                                              \
    ttype *X, *Z;                                                              \
    ctype *A, *C;                                                              \
    ftype *Y, *B;                                                              \
    const size_t N = NSAMPS(ftype, ttype, ctype) / 6UL;                        \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double max_err = 0.0L;                                                \
    long double rel_err = 0.0L;                                                \
    long double tmp = 0.0L;                                                    \
    ftype dx, dy;                                                              \
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
        long double v = rand_real();                                           \
                                                                               \
        X[n].dat[0] = (ftype)u0;                                               \
        X[n].dat[1] = (ftype)u1;                                               \
        Y[n] = (ftype)v;                                                       \
                                                                               \
        A[n] = (ftype)u0 + (complex ftype)_Complex_I*(ftype)u1;                \
        B[n] = (ftype)v;                                                       \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1"\n");                                               \
    printf("samples: %zu\n", N);                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        Z[n] = f0(Y[n], X[n]);                                                 \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        C[n] = f1(B[n], A[n]);                                                 \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        dx = Z[n].dat[0] - REPART(C[n]);                                       \
        dy = Z[n].dat[1] - IMPART(C[n]);                                       \
        tmp = sqrtl((long double)(dx*dx) + (long double)(dy*dy));              \
        rel_err += tmp*tmp;                                                    \
                                                                               \
        if (max_err < tmp)                                                     \
            max_err = tmp;                                                     \
    }                                                                          \
                                                                               \
    rel_err = sqrtl(rel_err / (long double)N);                                 \
                                                                               \
    printf("max err: %Le\n", max_err);                                         \
    printf("rel err: %Le\n", rel_err);                                         \
    free(A);                                                                   \
    free(B);                                                                   \
    free(C);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    free(Z);                                                                   \
    return 0;                                                                  \
}

#define TEST6(ftype, ttype, ctype, f, op)                                      \
int main(void)                                                                 \
{                                                                              \
    ftype *X;                                                                  \
    ttype *Y;                                                                  \
    ctype *B;                                                                  \
    const size_t N = NSAMPS(ftype, ttype, ctype) / 4UL;                        \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double max_err = 0.0L;                                                \
    long double rel_err = 0.0L;                                                \
    long double tmp = 0.0L;                                                    \
    ftype dx, dy;                                                              \
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
    B = malloc(sizeof(*B) * N);                                                \
                                                                               \
    if (!B)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for B. Aborting.");              \
        free(X);                                                               \
        free(Y);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        long double u0 = rand_real();                                          \
        long double u1 = rand_real();                                          \
        long double v = rand_real();                                           \
                                                                               \
        Y[n].dat[0] = (ftype)u0;                                               \
        Y[n].dat[1] = (ftype)u1;                                               \
        B[n] = (ftype)u0 + (complex ftype)_Complex_I*(ftype)u1;                \
                                                                               \
        X[n] = (ftype)v;                                                       \
    }                                                                          \
                                                                               \
    printf(#f " vs. " #op"\n");                                                \
    printf("samples: %zu\n", N);                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        f(&Y[n], X[n]);                                                        \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        B[n] op X[n];                                                          \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        dx = Y[n].dat[0] - REPART(B[n]);                                       \
        dy = Y[n].dat[1] - IMPART(B[n]);                                       \
        tmp = sqrtl((long double)(dx*dx) + (long double)(dy*dy));              \
        rel_err += tmp*tmp;                                                    \
                                                                               \
        if (max_err < tmp)                                                     \
            max_err = tmp;                                                     \
    }                                                                          \
                                                                               \
    rel_err = sqrtl(rel_err / (long double)N);                                 \
                                                                               \
    printf("max err: %Le\n", max_err);                                         \
    printf("rel err: %Le\n", rel_err);                                         \
    free(B);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    return 0;                                                                  \
}

#define TEST7(ftype, ttype, ctype, f0, f1)                                     \
int main(void)                                                                 \
{                                                                              \
    ttype *X, *Y;                                                              \
    ctype *A, *B;                                                              \
    const size_t N = NSAMPS(ftype, ttype, ctype) / 4UL;                        \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double max_err = 0.0L;                                                \
    long double rel_err = 0.0L;                                                \
    long double tmp = 0.0L;                                                    \
    const ftype zero = (ftype)0;                                               \
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
                                                                               \
        X[n].dat[0] = (ftype)u0;                                               \
        X[n].dat[1] = (ftype)u1;                                               \
                                                                               \
        A[n] = (ftype)u0 + (complex ftype)_Complex_I*(ftype)u1;                \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1"\n");                                               \
    printf("samples: %zu\n", N);                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        Y[n] = f0(X[n]);                                                       \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        B[n] = f1(A[n]);                                                       \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        if (B[n] != zero)                                                      \
        {                                                                      \
            long double dx = (long double)(Y[n].dat[0] - REPART(B[n]));        \
            long double dy = (long double)(Y[n].dat[1] - IMPART(B[n]));        \
            tmp = sqrtl(dx*dx + dy*dy);                                        \
            rel_err += tmp*tmp;                                                \
                                                                               \
            if (max_err < tmp)                                                 \
                max_err = tmp;                                                 \
        }                                                                      \
    }                                                                          \
                                                                               \
    rel_err = sqrtl(rel_err / (long double)N);                                 \
                                                                               \
    printf("max err: %Le\n", max_err);                                         \
    printf("rel err: %Le\n", rel_err);                                         \
    free(A);                                                                   \
    free(B);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    return 0;                                                                  \
}

#define TEST8(ftype, ttype, ctype, f0, f1)                                     \
int main(void)                                                                 \
{                                                                              \
    ttype *X, *Y;                                                              \
    ctype *A, *B;                                                              \
    ftype *Z, *C;                                                              \
    const size_t N = NSAMPS(ftype, ttype, ctype) / 6UL;                        \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double max_err = 0.0L;                                                \
    long double rel_err = 0.0L;                                                \
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
        long double v0 = rand_real();                                          \
        long double v1 = rand_real();                                          \
                                                                               \
        X[n].dat[0] = (ftype)u0;                                               \
        X[n].dat[1] = (ftype)u1;                                               \
        Y[n].dat[0] = (ftype)v0;                                               \
        Y[n].dat[1] = (ftype)v1;                                               \
                                                                               \
        A[n] = (ftype)u0 + (complex ftype)_Complex_I*(ftype)u1;                \
        B[n] = (ftype)v0 + (complex ftype)_Complex_I*(ftype)v1;                \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1"\n");                                               \
    printf("samples: %zu\n", N);                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        Z[n] = f0(X[n], Y[n]);                                                 \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        C[n] = f1(A[n], B[n]);                                                 \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        tmp = fabsl((long double)((Z[n] - C[n])/C[n]));                        \
        rel_err += tmp*tmp;                                                    \
                                                                               \
        if (max_err < tmp)                                                     \
            max_err = tmp;                                                     \
    }                                                                          \
                                                                               \
    rel_err = sqrtl(rel_err / (long double)N);                                 \
                                                                               \
    printf("max err: %Le\n", max_err);                                         \
    printf("rel err: %Le\n", rel_err);                                         \
    free(A);                                                                   \
    free(B);                                                                   \
    free(C);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    free(Z);                                                                   \
    return 0;                                                                  \
}

#define TEST9(ftype, ttype, ctype, f0, f1)                                     \
int main(void)                                                                 \
{                                                                              \
    ttype *Z;                                                                  \
    ctype *A;                                                                  \
    ftype *X;                                                                  \
    const size_t N = NSAMPS(ftype, ttype, ctype) / 3UL;                        \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double max_err = 0.0L;                                                \
    long double rel_err = 0.0L;                                                \
    long double tmp = 0.0L;                                                    \
    ftype dx, dy;                                                              \
                                                                               \
    X = malloc(sizeof(*X) * N);                                                \
                                                                               \
    if (!X)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for X. Aborting.");              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    Z = malloc(sizeof(*Z) * N);                                                \
                                                                               \
    if (!Z)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for Z. Aborting.");              \
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
        free(Z);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        long double u = rand_real();                                           \
        X[n] = (ftype) u;                                                      \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1"\n");                                               \
    printf("samples: %zu\n", N);                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        Z[n] = f0(X[n]);                                                       \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        A[n] = f1(X[n]);                                                       \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC); \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        dx = Z[n].dat[0] - REPART(A[n]);                                       \
        dy = Z[n].dat[1] - IMPART(A[n]);                                       \
        tmp = sqrtl((long double)(dx*dx) + (long double)(dy*dy));              \
        rel_err += tmp*tmp;                                                    \
                                                                               \
        if (max_err < tmp)                                                     \
            max_err = tmp;                                                     \
    }                                                                          \
                                                                               \
    rel_err = sqrtl(rel_err / (long double)N);                                 \
                                                                               \
    printf("max err: %Le\n", max_err);                                         \
    printf("rel err: %Le\n", rel_err);                                         \
    free(A);                                                                   \
    free(X);                                                                   \
    free(Z);                                                                   \
    return 0;                                                                  \
}
