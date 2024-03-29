/******************************************************************************
 *                                  LICENSE                                   *
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libtmpl/include/tmpl_integer.h>

static double time_as_double(clock_t a, clock_t b)
{
    double t = (double)(b - a);
    return t / (double)(CLOCKS_PER_SEC);
}

#ifndef TMPL_NSAMPS
#ifdef _MSC_VER
#include <windows.h>
static size_t memsize(void)
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return (size_t)(status.ullTotalPhys);
}
#else
#include <unistd.h>
static size_t memsize(void)
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return (size_t)(pages * page_size);
}
#endif
#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define NSAMPS(a, b) (memsize()/(2ULL*MAX2(sizeof(a), sizeof(b))))
#else
#define NSAMPS(a, b) (size_t)TMPL_NSAMPS
#endif

#define TEST1(intype, outtype, f0, f1)                                         \
                                                                               \
static intype random_int(void)                                                 \
{                                                                              \
    int a = rand();                                                            \
    intype b = (intype)(a);                                                    \
    return b;                                                                  \
}                                                                              \
                                                                               \
int main(void)                                                                 \
{                                                                              \
    intype *A, *X;                                                             \
    outtype *B, *Y;                                                            \
    size_t n;                                                                  \
    const size_t N = NSAMPS(intype, outtype) / 4ULL;                           \
    clock_t t1, t2;                                                            \
    double tmp;                                                                \
    double max = 0.0;                                                          \
    double rms = 0.0;                                                          \
    A = malloc(sizeof(*A)*N);                                                  \
    B = malloc(sizeof(*B)*N);                                                  \
    X = malloc(sizeof(*X)*N);                                                  \
    Y = malloc(sizeof(*Y)*N);                                                  \
                                                                               \
    printf(#f0 " vs. " #f1 "\n");                                              \
    printf("samples: %zu\n", N);                                               \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
        A[n] = X[n] = random_int();                                            \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0; n < N; ++n)                                                    \
        B[n] = f0(A[n]);                                                       \
    t2 = clock();                                                              \
    printf("libtmpl: %f\n", time_as_double(t1, t2));                           \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0; n < N; ++n)                                                    \
        Y[n] = f1(X[n]);                                                       \
    t2 = clock();                                                              \
    printf("glibc:   %f\n", time_as_double(t1, t2));                           \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        double x = (double)(Y[n]);                                             \
        double y = (double)(B[n]);                                             \
        tmp = fabs((x - y));                                                   \
        rms += tmp*tmp;                                                        \
        if (max < tmp)                                                         \
            max = tmp;                                                         \
    }                                                                          \
                                                                               \
    rms = sqrt(rms / (double)N);                                               \
    printf("rms error: %e\n", rms);                                            \
    printf("max error: %e\n", max);                                            \
                                                                               \
    free(A);                                                                   \
    free(B);                                                                   \
    free(X);                                                                   \
    free(Y);                                                                   \
    return 0;                                                                  \
}
