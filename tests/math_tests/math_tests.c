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

#define TEST_FUNC(cfunc, tmplfunc, type, start, end, samples)                  \
do {                                                                           \
    unsigned long int n;                                                       \
    type x = start;                                                            \
    type dx = (end - start) / (type)samples;                                   \
    type zero = (type)0;                                                       \
    type max_rel = zero;                                                       \
    type max_abs = zero;                                                       \
    type y, z, tmp;                                                            \
                                                                               \
    for (n = 0; n < samples; ++n)                                              \
    {                                                                          \
        y = cfunc(x);                                                          \
        z = tmplfunc(x);                                                       \
        tmp = y - z;                                                           \
                                                                               \
        if (tmp < zero)                                                        \
            tmp = -tmp;                                                        \
                                                                               \
        if (max_abs < tmp)                                                     \
            max_abs = tmp;                                                     \
                                                                               \
        tmp = (y - z)/y;                                                       \
                                                                               \
        if (tmp < zero)                                                        \
            tmp = -tmp;                                                        \
                                                                               \
        if (max_rel < tmp)                                                     \
            max_rel = tmp;                                                     \
                                                                               \
        x += dx;                                                               \
    }                                                                          \
                                                                               \
    printf(#cfunc " vs. " #tmplfunc "\n");                                     \
    printf("    Start: %.8Le\n", (long double)start);                          \
    printf("    End:   %.8Le\n", (long double)end);                            \
    printf("    Max Abs: %.8Le\n", (long double)max_abs);                      \
    printf("    Max Rel: %.8Le\n\n", (long double)max_rel);                    \
} while(0)

int main(void)
{
    unsigned long int N = 1E6;
    TEST_FUNC(fabsf, tmpl_Float_Abs, float, -100.0F, 100.0F, N);
    TEST_FUNC(fabs, tmpl_Double_Abs, double, -100.0, 100.0, N);
    TEST_FUNC(fabsl, tmpl_LDouble_Abs, long double, -100.0L, 100.0L, N);

    TEST_FUNC(atanf, tmpl_Float_Arctan, float, -1000.0F, 1000.0F, N);
    TEST_FUNC(atan, tmpl_Double_Arctan, double, -1000.0, 1000.0, N);
    TEST_FUNC(atanl, tmpl_LDouble_Arctan, long double, -1000.0L, 100.0L, N);

    TEST_FUNC(logf, tmpl_Float_Log, float, 0.0F, 100.0F, N);
    TEST_FUNC(log, tmpl_Double_Log, double, 0.0, 100.0, N);
    TEST_FUNC(logl, tmpl_LDouble_Log, long double, 0.0L, 100.0L, N);
    return 0;
}

