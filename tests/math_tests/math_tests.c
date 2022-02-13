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

#include <libtmpl/include/tmpl_math.h>
#include <stdio.h>
#include <math.h>

#define TEST_FUNC(cfunc, tmplfunc, type, start, end, nsamples)                 \
do {                                                                           \
    unsigned long long int n;                                                  \
    type x = start;                                                            \
    type dx = (end - start) / (type)nsamples;                                  \
    long double max_rel = 0.0L;                                                \
    long double max_abs = 0.0L;                                                \
    long double rms_rel = 0.0L;                                                \
    long double rms_abs = 0.0L;                                                \
    long double tmp;                                                           \
    type y, z;                                                                 \
                                                                               \
    for (n = 0ULL; n < nsamples; ++n)                                          \
    {                                                                          \
        y = cfunc(x);                                                          \
        z = tmplfunc(x);                                                       \
        tmp = fabsl((long double)(y - z));                                     \
        rms_abs += tmp*tmp;                                                    \
                                                                               \
        if (max_abs < tmp)                                                     \
            max_abs = tmp;                                                     \
                                                                               \
        tmp = fabsl((long double)((y - z)/y));                                 \
        rms_rel += tmp*tmp;                                                    \
                                                                               \
        if (max_rel < tmp)                                                     \
            max_rel = tmp;                                                     \
                                                                               \
        x += dx;                                                               \
    }                                                                          \
                                                                               \
    rms_abs = sqrtl(rms_abs / (long double)N);                                 \
    rms_rel = sqrtl(rms_rel / (long double)N);                                 \
                                                                               \
    printf(#cfunc " vs. " #tmplfunc "\n");                                     \
    printf("    start: %.8Le\n", (long double)start);                          \
    printf("    end:   %.8Le\n", (long double)end);                            \
    printf("    samples: %llu\n", nsamples);                                   \
    printf("    max abs: %.8Le\n", max_abs);                                   \
    printf("    max rel: %.8Le\n", max_rel);                                   \
    printf("    rms abs: %.8Le\n", rms_abs);                                   \
    printf("    rms rel: %.8Le\n\n", rms_rel);                                 \
} while(0)

int main(void)
{
    unsigned long long int N = 1000000ULL;
    TEST_FUNC(fabsf, tmpl_Float_Abs, float, -100.0F, 100.0F, N);
    TEST_FUNC(fabs, tmpl_Double_Abs, double, -100.0, 100.0, N);
    TEST_FUNC(fabsl, tmpl_LDouble_Abs, long double, -100.0L, 100.0L, N);

    TEST_FUNC(atanf, tmpl_Float_Arctan, float, -1000.0F, 1000.0F, N);
    TEST_FUNC(atan, tmpl_Double_Arctan, double, -1000.0, 1000.0, N);
    TEST_FUNC(atanl, tmpl_LDouble_Arctan, long double, -1000.0L, 1000.0L, N);

    TEST_FUNC(logf, tmpl_Float_Log, float, 1.0E-6F, 100.0F, N);
    TEST_FUNC(log, tmpl_Double_Log, double, 1.0E-6, 100.0, N);
    TEST_FUNC(logl, tmpl_LDouble_Log, long double, 1.0E-6L, 100.0L, N);
    return 0;
}

