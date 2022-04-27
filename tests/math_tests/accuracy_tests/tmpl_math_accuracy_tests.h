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
#include <stdio.h>
#include <math.h>

#define RUN_TEST(type, begin, finish, samples, f0, f1)                         \
do {                                                                           \
    long double max_abs = 0.0L;                                                \
    long double max_rel = 0.0L;                                                \
    long double rms_rel = 0.0L;                                                \
    long double rms_abs = 0.0L;                                                \
    long double temp;                                                          \
    type x, y0, y1;                                                            \
    unsigned long int n;                                                       \
                                                                               \
    const type start = (type)begin;                                            \
    const type end = (type)finish;                                             \
    const unsigned long long int N = (unsigned long long int)samples;          \
    const type dx = (end - start) / (type)N;                                   \
                                                                               \
    printf(#f0 " vs. " #f1 "\n");                                              \
    printf("start:   %.16Le\n", (long double)start);                           \
    printf("end:     %.16Le\n", (long double)end);                             \
    printf("samples: %llu\n", N);                                              \
    printf("dx:      %.16Le\n", (long double)dx);                              \
                                                                               \
    x = start;                                                                 \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        y0 = f0(x);                                                            \
        y1 = f1(x);                                                            \
        temp = fabsl((long double)(y0 - y1));                                  \
        rms_abs += temp*temp;                                                  \
        if (max_abs < temp)                                                    \
            max_abs = temp;                                                    \
                                                                               \
        temp = fabsl((long double)((y0 - y1) / y1));                           \
                                                                               \
        if (y1 != 0)                                                           \
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
} while (0)
