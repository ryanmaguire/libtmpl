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
#include <libtmpl/include/tmpl_special_functions_real.h>
#include <libtmpl/include/tmpl_math.h>

#ifdef __cplusplus
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
using namespace std;
#define TMPL_CAST(x, type) static_cast<type>((x))
#define TMPL_MALLOC(x, type, N) static_cast<type *>(malloc(sizeof(*x)*N))
#else
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define TMPL_CAST(x, type) (type)((x))
#define TMPL_MALLOC(x, type, N) malloc(sizeof(*x) * N)
#endif

#ifndef TMPL_NSAMPS
#ifdef _MSC_VER
#include <windows.h>
static size_t memsize(void)
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return TMPL_CAST(status.ullTotalPhys, size_t);
}
#else
#include <unistd.h>
static size_t memsize(void)
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return TMPL_CAST(pages * page_size, size_t);
}
#endif
#define NSAMPS(a) (4*memsize()/(5*sizeof(a)))
#else
#define NSAMPS(a) TMPL_CAST(TMPL_NSAMPS, size_t)
#endif

#define RAND_REAL(type, val)                                                   \
do {                                                                           \
    int my_temp_variable = rand();                                             \
    val = (type)my_temp_variable / (type)RAND_MAX;                             \
} while(0);

#define TEST1(type, begin, finish, f0, f1)                                     \
int main(void)                                                                 \
{                                                                              \
    long double max_abs = 0.0L;                                                \
    long double max_rel = 0.0L;                                                \
    long double rms_rel = 0.0L;                                                \
    long double rms_abs = 0.0L;                                                \
    long double temp;                                                          \
    type *x, *y0, *y1;                                                         \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
                                                                               \
    const type start = TMPL_CAST(begin, type);                                 \
    const type end = TMPL_CAST(finish, type);                                  \
    const size_t N = NSAMPS(type) / 3;                                         \
    const type dx = (end - start) / TMPL_CAST(N, type);                        \
                                                                               \
    x = TMPL_MALLOC(x, type, N);                                               \
                                                                               \
    if (!x)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for x. Aborting.");              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y0 = TMPL_MALLOC(y0, type, N);                                             \
                                                                               \
    if (!y0)                                                                   \
    {                                                                          \
        puts("malloc failed and returned NULL for y0. Aborting.");             \
        free(x);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y1 = TMPL_MALLOC(y1, type, N);                                             \
                                                                               \
    if (!y1)                                                                   \
    {                                                                          \
        puts("malloc failed and returned NULL for y1. Aborting.");             \
        free(x);                                                               \
        free(y0);                                                              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1 "\n");                                              \
    printf("start:   %.16Le\n", TMPL_CAST(start, long double));                \
    printf("end:     %.16Le\n", TMPL_CAST(end, long double));                  \
    printf("samples: %zu\n", N);                                               \
    printf("dx:      %.16Le\n", TMPL_CAST(dx, long double));                   \
                                                                               \
    x[0] = start;                                                              \
    for (n = TMPL_CAST(1, size_t); n < N; ++n)                                 \
        x[n] = x[n-1] + dx;                                                    \
                                                                               \
    t1 = clock();                                                              \
    for (n = TMPL_CAST(0, size_t); n < N; ++n)                                 \
        y0[n] = f0(x[n]);                                                      \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", TMPL_CAST(t2-t1, double)/CLOCKS_PER_SEC);  \
                                                                               \
    t1 = clock();                                                              \
    for (n = TMPL_CAST(0, size_t); n < N; ++n)                                 \
        y1[n] = f1(x[n]);                                                      \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", TMPL_CAST(t2-t1, double)/CLOCKS_PER_SEC);  \
                                                                               \
    for (n = TMPL_CAST(0, size_t); n < N; ++n)                                 \
    {                                                                          \
        temp = fabsl(TMPL_CAST(y0[n] - y1[n], long double));                   \
        rms_abs += temp*temp;                                                  \
        if (max_abs < temp)                                                    \
            max_abs = temp;                                                    \
                                                                               \
        temp = fabsl(TMPL_CAST((y0[n] - y1[n])/y1[n], long double));           \
                                                                               \
        if (y1[n] != 0)                                                        \
        {                                                                      \
            rms_rel += temp*temp;                                              \
                                                                               \
            if (max_rel < temp)                                                \
                max_rel = temp;                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    rms_rel = sqrtl(rms_rel / TMPL_CAST(N, long double));                      \
    rms_abs = sqrtl(rms_abs / TMPL_CAST(N, long double));                      \
    printf("max abs error: %.16Le\n", max_abs);                                \
    printf("max rel error: %.16Le\n", max_rel);                                \
    printf("rms abs error: %.16Le\n", rms_abs);                                \
    printf("rms rel error: %.16Le\n", rms_rel);                                \
    free(x);                                                                   \
    free(y0);                                                                  \
    free(y1);                                                                  \
    return 0;                                                                  \
}
