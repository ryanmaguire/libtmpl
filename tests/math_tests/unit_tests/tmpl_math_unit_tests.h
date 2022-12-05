/******************************************************************************
 *                                  LICENSE                                   *
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
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 16, 2022                                             *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  libtmpl math library found here.                                          */
#include <libtmpl/include/tmpl_math.h>

/*  Standard library math functions here.                                     */
#include <math.h>

/*  puts function found here.                                                 */
#include <stdio.h>

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  DBL_MIN, DBL_MAX, and other constants found here.                         */
#include <float.h>

#ifdef T
#undef T
#endif
#ifdef F
#undef F
#endif
#ifdef TINF
#undef TINF
#endif
#ifdef TNAN
#undef TNAN
#endif
#ifdef DNUM
#undef DNUM
#endif
#ifdef BNUM
#undef BNUM
#endif
#define T tmpl_True
#define F tmpl_False
#define TINF tmpl_Double_Infinity()
#define TNAN tmpl_Double_NaN()
#define DNUM pow(2.0, 1 - (TMPL_DOUBLE_BIAS + TMPL_DOUBLE_MANTISSA_LENGTH))
#define BNUM pow(2.0, (TMPL_DOUBLE_BIAS))

#define TEST1(type, func, indata, outdata, is_nan)                             \
int main(void)                                                                 \
{                                                                              \
    const type in[] = indata;                                                  \
    const type out[] = outdata;                                                \
    type output;                                                               \
    size_t n;                                                                  \
                                                                               \
    for (n = (size_t)0; n < sizeof(in)/sizeof(in[0]); ++n)                     \
    {                                                                          \
        output = func(in[n]);                                                  \
                                                                               \
        if (is_nan(output))                                                    \
        {                                                                      \
            if (!is_nan(out[n]))                                               \
            {                                                                  \
                puts("FAIL");                                                  \
                return -1;                                                     \
            }                                                                  \
        }                                                                      \
        else if (output != out[n])                                             \
        {                                                                      \
            puts("FAIL");                                                      \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#define TEST2(type, func, indata, outdata)                                     \
int main(void)                                                                 \
{                                                                              \
    const type in[] = indata;                                                  \
    const tmpl_Bool out[] = outdata;                                           \
    tmpl_Bool output;                                                          \
    size_t n;                                                                  \
                                                                               \
    for (n = (size_t)0; n < sizeof(in)/sizeof(in[0]); ++n)                     \
    {                                                                          \
        output = func(in[n]);                                                  \
        if (output != out[n])                                                  \
        {                                                                      \
            puts("FAIL");                                                      \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#define TEST3(type, func0, func1, indata, is_nan, eps)                         \
int main(void)                                                                 \
{                                                                              \
    typedef struct {type x, y;} arr2;                                          \
    const arr2 in[] = indata;                                                  \
    type out0, out1;                                                           \
    size_t n;                                                                  \
    const long double EPS = (long double)eps;                                  \
                                                                               \
    for (n = (size_t)0; n < sizeof(in)/sizeof(in[0]); ++n)                     \
    {                                                                          \
        out0 = func0(in[n].x, in[n].y);                                        \
        out1 = func1(in[n].x, in[n].y);                                        \
                                                                               \
        if (is_nan(out0))                                                      \
        {                                                                      \
            if (!is_nan(out1))                                                 \
            {                                                                  \
                puts("FAIL");                                                  \
                return -1;                                                     \
            }                                                                  \
        }                                                                      \
        else if (tmpl_LDouble_Abs((long double)(out0 - out1)) > EPS)           \
        {                                                                      \
            puts("FAIL");                                                      \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
    return 0;                                                                  \
}
