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

#ifdef _MSC_VER

#include <windows.h>
static unsigned long long int memsize()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return (unsigned long long int)status.ullTotalPhys;
}

#else

#include <unistd.h>
static unsigned long long memsize()
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return (unsigned long long int)(pages * page_size);
}
#endif

static inline long double rand_real(void)
{
    int n = rand();
    long double x = (long double)n / (long double)(RAND_MAX);
    return 2.0L*(x - 0.5L);
}

#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) MAX2((a), MAX2((b), (c)))
#define NSAMPS(a, b, c) (memsize()/(2ULL*MAX3(sizeof(a), sizeof(b), sizeof(c))))

#define TEST1(ftype, ttype, ctype, f0, f1)                                     \
int main(void)                                                                 \
{                                                                              \
    ttype *X;                                                                  \
    ctype *A;                                                                  \
    ftype *Y, *B;                                                              \
    const unsigned long long int N = NSAMPS(ftype, ttype, ctype) / 4UL;        \
    unsigned long long int n;                                                  \
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
    printf("samples: %llu\n", N);                                              \
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
        tmp = fabsl((long double)(Y[n] - B[n]));                               \
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
