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
#include <libtmpl/include/tmpl_math.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef USEOPENLIBM
#include <openlibm/include/openlibm_math.h>
#else
#include <math.h>
#endif

#include <time.h>
#include <float.h>

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
#define NSAMPS(a) (4*memsize()/(5*sizeof(a)))
#else
#define NSAMPS(a) (size_t)TMPL_NSAMPS
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
    unsigned long int n;                                                       \
    clock_t t1, t2;                                                            \
                                                                               \
    const type start = (type)begin;                                            \
    const type end = (type)finish;                                             \
    const size_t N = NSAMPS(type) / 3;                                         \
    const type dx = (end - start) / (type)N;                                   \
                                                                               \
    x = malloc(sizeof(*x) * N);                                                \
                                                                               \
    if (!x)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for x. Aborting.");              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y0 = malloc(sizeof(*y0) * N);                                              \
                                                                               \
    if (!y0)                                                                   \
    {                                                                          \
        puts("malloc failed and returned NULL for y0. Aborting.");             \
        free(x);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y1 = malloc(sizeof(*y1) * N);                                              \
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
    printf("start:   %.16Le\n", (long double)start);                           \
    printf("end:     %.16Le\n", (long double)end);                             \
    printf("samples: %zu\n", N);                                               \
    printf("dx:      %.16Le\n", (long double)dx);                              \
                                                                               \
    x[0] = start;                                                              \
    for (n = 1UL; n < N; ++n)                                                  \
        x[n] = x[n-1] + dx;                                                    \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0UL; n < N; ++n)                                                  \
        y0[n] = f0(x[n]);                                                      \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2-t1)/CLOCKS_PER_SEC);           \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0UL; n < N; ++n)                                                  \
        y1[n] = f1(x[n]);                                                      \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2-t1)/CLOCKS_PER_SEC);           \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        temp = fabsl((long double)(y0[n] - y1[n]));                            \
        rms_abs += temp*temp;                                                  \
        if (max_abs < temp)                                                    \
            max_abs = temp;                                                    \
                                                                               \
        temp = fabsl((long double)((y0[n] - y1[n]) / y1[n]));                  \
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
    rms_rel = sqrtl(rms_rel / (long double)N);                                 \
    rms_abs = sqrtl(rms_abs / (long double)N);                                 \
    printf("max abs error: %.16Le\n", max_abs);                                \
    printf("max rel error: %.16Le\n", max_rel);                                \
    printf("rms abs error: %.16Le\n", rms_abs);                                \
    printf("rms rel error: %.16Le\n", rms_rel);                                \
    free(x);                                                                   \
    free(y0);                                                                  \
    free(y1);                                                                  \
    return 0;                                                                  \
}

#define TEST2(type, f0, f1)                                                    \
int main(void)                                                                 \
{                                                                              \
    type *x, *y0, *y1;                                                         \
    int *n0, *n1;                                                              \
    const size_t N = NSAMPS(double) / 5;                                       \
    size_t n;                                                                  \
    clock_t t1, t2;                                                            \
    long double mant_rms_rel = 0.0L;                                           \
    long double mant_rms_abs = 0.0L;                                           \
    long double mant_max_rel = 0.0L;                                           \
    long double mant_max_abs = 0.0L;                                           \
    long double expo_rms_rel = 0.0L;                                           \
    long double expo_rms_abs = 0.0L;                                           \
    long double expo_max_rel = 0.0L;                                           \
    long double expo_max_abs = 0.0L;                                           \
    long double tmp;                                                           \
    int n_tmp;                                                                 \
    const type zero = (type)0;                                                 \
                                                                               \
    x = malloc(sizeof(*x) * N);                                                \
                                                                               \
    if (!x)                                                                    \
    {                                                                          \
        puts("Malloc returned NULL for x. Aborting.");                         \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y0 = malloc(sizeof(*y0) * N);                                              \
                                                                               \
    if (!y0)                                                                   \
    {                                                                          \
        puts("Malloc returned NULL for y0. Aborting.");                        \
        free(x);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y1 = malloc(sizeof(*y1) * N);                                              \
                                                                               \
    if (!y1)                                                                   \
    {                                                                          \
        puts("Malloc returned NULL for y1. Aborting.");                        \
        free(x);                                                               \
        free(y0);                                                              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    n0 = malloc(sizeof(*n0) * N);                                              \
                                                                               \
    if (!n0)                                                                   \
    {                                                                          \
        puts("Malloc returned NULL for n0. Aborting.");                        \
        free(x);                                                               \
        free(y0);                                                              \
        free(y1);                                                              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    n1 = malloc(sizeof(*n1) * N);                                              \
                                                                               \
    if (!n1)                                                                   \
    {                                                                          \
        puts("Malloc returned NULL for n1. Aborting.");                        \
        free(x);                                                               \
        free(y0);                                                              \
        free(y1);                                                              \
        free(n0);                                                              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1 "\n");                                              \
    printf("samples:  %zu\n", N);                                              \
    for (n = 0U; n < N; ++n)                                                   \
        RAND_REAL(type, x[n])                                                  \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
        f0(x[n], &y0[n], &n0[n]);                                              \
    t2 = clock();                                                              \
    printf("libtmpl: %f\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);         \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        y1[n] = ((type)2.0)*f1(x[n], &n1[n]);                                  \
        n1[n] -= 1;                                                            \
    }                                                                          \
    t2 = clock();                                                              \
    printf("C:       %f\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);         \
                                                                               \
    for (n = 0U; n < N; ++n)                                                   \
    {                                                                          \
        tmp = (long double)(y0[n] > y1[n] ? y0[n] - y1[n] : y1[n] - y0[n]);    \
        mant_rms_abs += tmp*tmp;                                               \
                                                                               \
        if (mant_max_abs < tmp)                                                \
            mant_max_abs = tmp;                                                \
                                                                               \
        if (y1[n] != zero)                                                     \
        {                                                                      \
            tmp /= (long double)y1[n];                                         \
            mant_rms_rel += tmp*tmp;                                           \
                                                                               \
            if (mant_max_rel < tmp)                                            \
                mant_max_rel = tmp;                                            \
        }                                                                      \
                                                                               \
                                                                               \
        n_tmp = abs(n0[n] - n1[n]);                                            \
        tmp = (long double)n_tmp;                                              \
        expo_rms_abs += tmp*tmp;                                               \
                                                                               \
        if (expo_max_abs < tmp)                                                \
            expo_max_abs = tmp;                                                \
                                                                               \
        n_tmp = abs(n1[n]);                                                    \
        if (n_tmp != 0)                                                        \
        {                                                                      \
            tmp = tmp / (long double)n_tmp;                                    \
            expo_rms_rel += tmp*tmp;                                           \
                                                                               \
            if (expo_max_rel < tmp)                                            \
                expo_max_rel = tmp;                                            \
        }                                                                      \
    }                                                                          \
                                                                               \
    mant_rms_abs = sqrtl(mant_rms_abs / (long double)N);                       \
    mant_rms_rel = sqrtl(mant_rms_rel / (long double)N);                       \
    expo_rms_abs = sqrtl(expo_rms_abs / (long double)N);                       \
    expo_rms_rel = sqrtl(expo_rms_rel / (long double)N);                       \
                                                                               \
    printf("mant max abs err: %Le\n", mant_max_abs);                           \
    printf("mant max rel err: %Le\n", mant_max_rel);                           \
    printf("mant rms abs err: %Le\n", mant_rms_abs);                           \
    printf("mant rms rel err: %Le\n", mant_rms_rel);                           \
    printf("expo max abs err: %Le\n", expo_max_abs);                           \
    printf("expo max rel err: %Le\n", expo_max_rel);                           \
    printf("expo rms abs err: %Le\n", expo_rms_abs);                           \
    printf("expo rms rel err: %Le\n", expo_rms_rel);                           \
                                                                               \
    free(x);                                                                   \
    free(y0);                                                                  \
    free(y1);                                                                  \
    free(n0);                                                                  \
    free(n1);                                                                  \
    return 0;                                                                  \
}

#define TEST3(type, begin, finish, f0, f1)                                     \
int main(void)                                                                 \
{                                                                              \
    long double max_abs = 0.0L;                                                \
    long double max_rel = 0.0L;                                                \
    long double rms_rel = 0.0L;                                                \
    long double rms_abs = 0.0L;                                                \
    long double temp;                                                          \
    type *x, *y, *z0, *z1;                                                     \
    unsigned long int n;                                                       \
    clock_t t1, t2;                                                            \
    type u, v;                                                                 \
                                                                               \
    const type start = (type)begin;                                            \
    const type end = (type)finish;                                             \
    const type diff = end - start;                                             \
    const size_t N = NSAMPS(type) / 4;                                         \
                                                                               \
    x = malloc(sizeof(*x) * N);                                                \
                                                                               \
    if (!x)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for x. Aborting.");              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y = malloc(sizeof(*y) * N);                                                \
                                                                               \
    if (!y)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for y. Aborting.");              \
        free(x);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    z0 = malloc(sizeof(*z0) * N);                                              \
                                                                               \
    if (!z0)                                                                   \
    {                                                                          \
        puts("malloc failed and returned NULL for z0. Aborting.");             \
        free(x);                                                               \
        free(y);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    z1 = malloc(sizeof(*z1) * N);                                              \
                                                                               \
    if (!z1)                                                                   \
    {                                                                          \
        puts("malloc failed and returned NULL for z1. Aborting.");             \
        free(x);                                                               \
        free(y);                                                               \
        free(z0);                                                              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1 "\n");                                              \
    printf("start:   %.16Le\n", (long double)start);                           \
    printf("end:     %.16Le\n", (long double)end);                             \
    printf("samples: %zu\n", N);                                               \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        RAND_REAL(type, u)                                                     \
        RAND_REAL(type, v)                                                     \
                                                                               \
        u = diff*u + start;                                                    \
        v = diff*v + start;                                                    \
                                                                               \
        x[n] = u;                                                              \
        y[n] = v;                                                              \
    }                                                                          \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0UL; n < N; ++n)                                                  \
        z0[n] = f0(x[n], y[n]);                                                \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2-t1)/CLOCKS_PER_SEC);           \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0UL; n < N; ++n)                                                  \
        z1[n] = f1(x[n], y[n]);                                                \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2-t1)/CLOCKS_PER_SEC);           \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        temp = fabsl((long double)(z0[n] - z1[n]));                            \
        rms_abs += temp*temp;                                                  \
        if (max_abs < temp)                                                    \
            max_abs = temp;                                                    \
                                                                               \
        temp = fabsl((long double)((z0[n] - z1[n]) / z1[n]));                  \
                                                                               \
        if (z1[n] != 0)                                                        \
        {                                                                      \
            rms_rel += temp*temp;                                              \
                                                                               \
            if (max_rel < temp)                                                \
                max_rel = temp;                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    rms_rel = sqrtl(rms_rel / (long double)N);                                 \
    rms_abs = sqrtl(rms_abs / (long double)N);                                 \
    printf("max abs error: %.16Le\n", max_abs);                                \
    printf("max rel error: %.16Le\n", max_rel);                                \
    printf("rms abs error: %.16Le\n", rms_abs);                                \
    printf("rms rel error: %.16Le\n", rms_rel);                                \
    free(x);                                                                   \
    free(y);                                                                   \
    free(z0);                                                                  \
    free(z1);                                                                  \
    return 0;                                                                  \
}

#define TEST4(type, begin, finish, f0, f1)                                     \
int main(void)                                                                 \
{                                                                              \
    long double max_abs_y = 0.0L;                                              \
    long double max_rel_y = 0.0L;                                              \
    long double rms_rel_y = 0.0L;                                              \
    long double rms_abs_y = 0.0L;                                              \
    long double max_abs_z = 0.0L;                                              \
    long double max_rel_z = 0.0L;                                              \
    long double rms_rel_z = 0.0L;                                              \
    long double rms_abs_z = 0.0L;                                              \
    long double tempy, tempz;                                                  \
    type *x, *y0, *y1, *z0, *z1;                                               \
    unsigned long int n;                                                       \
    clock_t t1, t2;                                                            \
                                                                               \
    const type start = (type)begin;                                            \
    const type end = (type)finish;                                             \
    const size_t N = NSAMPS(type) / 5;                                         \
    const type dx = (end - start) / (type)N;                                   \
                                                                               \
    x = malloc(sizeof(*x) * N);                                                \
                                                                               \
    if (!x)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for x. Aborting.");              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y0 = malloc(sizeof(*y0) * N);                                              \
                                                                               \
    if (!y0)                                                                   \
    {                                                                          \
        puts("malloc failed and returned NULL for y0. Aborting.");             \
        free(x);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y1 = malloc(sizeof(*y1) * N);                                              \
                                                                               \
    if (!y1)                                                                   \
    {                                                                          \
        puts("malloc failed and returned NULL for y1. Aborting.");             \
        free(x);                                                               \
        free(y0);                                                              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    z0 = malloc(sizeof(*z0) * N);                                              \
                                                                               \
    if (!z0)                                                                   \
    {                                                                          \
        puts("malloc failed and returned NULL for z0. Aborting.");             \
        free(x);                                                               \
        free(y0);                                                              \
        free(y1);                                                              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    z1 = malloc(sizeof(*z1) * N);                                              \
                                                                               \
    if (!z1)                                                                   \
    {                                                                          \
        puts("malloc failed and returned NULL for z1. Aborting.");             \
        free(x);                                                               \
        free(y0);                                                              \
        free(y1);                                                              \
        free(z0);                                                              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    printf(#f0 " vs. " #f1 "\n");                                              \
    printf("start:   %.16Le\n", (long double)start);                           \
    printf("end:     %.16Le\n", (long double)end);                             \
    printf("samples: %zu\n", N);                                               \
    printf("dx:      %.16Le\n", (long double)dx);                              \
                                                                               \
    x[0] = start;                                                              \
    for (n = 1UL; n < N; ++n)                                                  \
        x[n] = x[n-1] + dx;                                                    \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0UL; n < N; ++n)                                                  \
        f0(x[n], &y0[n], &z0[n]);                                              \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2-t1)/CLOCKS_PER_SEC);           \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0UL; n < N; ++n)                                                  \
        f1(x[n], &y1[n], &z1[n]);                                              \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2-t1)/CLOCKS_PER_SEC);           \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        tempy = fabsl((long double)(y0[n] - y1[n]));                           \
        tempz = fabsl((long double)(z0[n] - z1[n]));                           \
        rms_abs_y += tempy*tempy;                                              \
        if (max_abs_y < tempy)                                                 \
            max_abs_y = tempy;                                                 \
                                                                               \
        if (y1[n] != 0)                                                        \
        {                                                                      \
            tempy = fabsl((long double)((y0[n] - y1[n]) / y1[n]));             \
            rms_rel_y += tempy*tempy;                                          \
                                                                               \
            if (max_rel_y < tempy)                                             \
                max_rel_y = tempy;                                             \
        }                                                                      \
                                                                               \
        if (z1[n] != 0)                                                        \
        {                                                                      \
            tempz = fabsl((long double)((z0[n] - z1[n]) / z1[n]));             \
            rms_rel_z += tempz*tempz;                                          \
                                                                               \
            if (max_rel_z < tempz)                                             \
                max_rel_z = tempz;                                             \
        }                                                                      \
    }                                                                          \
                                                                               \
    rms_rel_y = sqrtl(rms_rel_y / (long double)N);                             \
    rms_abs_y = sqrtl(rms_abs_y / (long double)N);                             \
    rms_rel_z = sqrtl(rms_rel_z / (long double)N);                             \
    rms_abs_z = sqrtl(rms_abs_z / (long double)N);                             \
    printf("max y abs error: %.16Le\n", max_abs_y);                            \
    printf("max y rel error: %.16Le\n", max_rel_y);                            \
    printf("rms y abs error: %.16Le\n", rms_abs_y);                            \
    printf("rms y rel error: %.16Le\n", rms_rel_y);                            \
    printf("max z abs error: %.16Le\n", max_abs_z);                            \
    printf("max z rel error: %.16Le\n", max_rel_z);                            \
    printf("rms z abs error: %.16Le\n", rms_abs_z);                            \
    printf("rms z rel error: %.16Le\n", rms_rel_z);                            \
    free(x);                                                                   \
    free(y0);                                                                  \
    free(y1);                                                                  \
    free(z0);                                                                  \
    free(z1);                                                                  \
    return 0;                                                                  \
}

#define TEST5(type, begin, finish, f0, f1)                                     \
int main(void)                                                                 \
{                                                                              \
    long double max_abs = 0.0L;                                                \
    long double max_rel = 0.0L;                                                \
    long double rms_rel = 0.0L;                                                \
    long double rms_abs = 0.0L;                                                \
    long double temp;                                                          \
    signed int *x;                                                             \
    type *y0, *y1;                                                             \
    unsigned long int n;                                                       \
    clock_t t1, t2;                                                            \
                                                                               \
    const signed int start = (signed int)begin;                                \
    const signed int end = (signed int)finish;                                 \
    const size_t N = (size_t)(end - start);                                    \
                                                                               \
    x = malloc(sizeof(*x) * N);                                                \
                                                                               \
    if (!x)                                                                    \
    {                                                                          \
        puts("malloc failed and returned NULL for x. Aborting.");              \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y0 = malloc(sizeof(*y0) * N);                                              \
                                                                               \
    if (!y0)                                                                   \
    {                                                                          \
        puts("malloc failed and returned NULL for y0. Aborting.");             \
        free(x);                                                               \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    y1 = malloc(sizeof(*y1) * N);                                              \
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
    printf("start:   %.16Le\n", (long double)start);                           \
    printf("end:     %.16Le\n", (long double)end);                             \
    printf("samples: %zu\n", N);                                               \
                                                                               \
    x[0] = start;                                                              \
    for (n = 1UL; n < N; ++n)                                                  \
        x[n] = x[n-1] + 1;                                                     \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0UL; n < N; ++n)                                                  \
        y0[n] = f0(x[n]);                                                      \
    t2 = clock();                                                              \
    printf("libtmpl: %f seconds\n", (double)(t2-t1)/CLOCKS_PER_SEC);           \
                                                                               \
    t1 = clock();                                                              \
    for (n = 0UL; n < N; ++n)                                                  \
        y1[n] = f1(1.0, x[n]);                                                 \
    t2 = clock();                                                              \
    printf("C:       %f seconds\n", (double)(t2-t1)/CLOCKS_PER_SEC);           \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        temp = fabsl((long double)(y0[n] - y1[n]));                            \
        rms_abs += temp*temp;                                                  \
        if (max_abs < temp)                                                    \
            max_abs = temp;                                                    \
                                                                               \
        temp = fabsl((long double)((y0[n] - y1[n]) / y1[n]));                  \
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
    rms_rel = sqrtl(rms_rel / (long double)N);                                 \
    rms_abs = sqrtl(rms_abs / (long double)N);                                 \
    printf("max abs error: %.16Le\n", max_abs);                                \
    printf("max rel error: %.16Le\n", max_rel);                                \
    printf("rms abs error: %.16Le\n", rms_abs);                                \
    printf("rms rel error: %.16Le\n", rms_rel);                                \
    free(x);                                                                   \
    free(y0);                                                                  \
    free(y1);                                                                  \
    return 0;                                                                  \
}
