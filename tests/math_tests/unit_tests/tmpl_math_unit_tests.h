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
#ifndef EPS
#undef EPS
#endif
#ifdef TINFF
#undef TINFF
#endif
#ifdef TNANF
#undef TNANF
#endif
#ifdef DNUMF
#undef DNUMF
#endif
#ifdef BNUMF
#undef BNUMF
#endif
#ifndef EPSF
#undef EPSF
#endif
#ifdef TINFL
#undef TINFL
#endif
#ifdef TNANL
#undef TNANL
#endif
#ifdef DNUML
#undef DNUML
#endif
#ifdef BNUML
#undef BNUML
#endif
#ifndef EPSL
#undef EPSL
#endif
#define T tmpl_True
#define F tmpl_False
#define TINF tmpl_Double_Infinity()
#define TNAN tmpl_Double_NaN()
#if TMPL_HAS_IEEE754_DOUBLE == 1
#define DNUM pow(2.0, 1 - (TMPL_DOUBLE_BIAS + TMPL_DOUBLE_MANTISSA_LENGTH))
#define BNUM pow(2.0, (TMPL_DOUBLE_BIAS))
#else
#define DNUM DBL_MIN
#define BNUM DBL_MAX
#endif
#define EPS (10.0 * DBL_EPSILON)
#define TINFF tmpl_Float_Infinity()
#define TNANF tmpl_Float_NaN()
#if TMPL_HAS_IEEE754_FLOAT == 1
#define DNUMF powf(2.0F, 1 - (TMPL_FLOAT_BIAS + TMPL_FLOAT_MANTISSA_LENGTH))
#define BNUMF powf(2.0F, (TMPL_FLOAT_BIAS))
#else
#define DNUMF FLT_MIN
#define BNUMF FLT_MAX
#endif
#define EPSF (10.0F * FLT_EPSILON)
#define TINFL tmpl_LDouble_Infinity()
#define TNANL tmpl_LDouble_NaN()
#if TMPL_HAS_IEEE754_LDOUBLE == 1
#define DNUML powl(2.0L, 1 - (TMPL_LDOUBLE_BIAS + TMPL_LDOUBLE_MANTISSA_LENGTH))
#define BNUML powl(2.0L, (TMPL_LDOUBLE_BIAS))
#else
#define DNUML LDBL_MIN
#define BNUML LDBL_MAX
#endif
#define EPSL (10.0L * LDBL_EPSILON)

#ifdef GET_EPS
#undef GET_EPS
#endif
#define GET_EPS(x) _Generic((x),\
    long double: EPSL,          \
    default: EPS,               \
    float: EPSF                 \
)

#ifdef CHECK_NAN
#undef CHECK_NAN
#endif
#define CHECK_NAN(x) _Generic((x),    \
    long double: tmpl_LDouble_Is_NaN, \
    default: tmpl_Double_Is_NaN,      \
    float: tmpl_Float_Is_NaN          \
)(x)

#define TEST1(type, func, indata, outdata)                                     \
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
        if (CHECK_NAN(output))                                                 \
        {                                                                      \
            if (!CHECK_NAN(out[n]))                                            \
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

#define TEST3(type, func0, func1, indata)                                      \
int main(void)                                                                 \
{                                                                              \
    typedef struct {type x, y;} arr2;                                          \
    const arr2 in[] = indata;                                                  \
    type out0, out1;                                                           \
    size_t n;                                                                  \
    const long double eps = (long double)GET_EPS(out0);                        \
    long double err = 0.0L;                                                    \
    type zero = (type)0;                                                       \
                                                                               \
    for (n = (size_t)0; n < sizeof(in)/sizeof(in[0]); ++n)                     \
    {                                                                          \
        out0 = func0(in[n].x, in[n].y);                                        \
        out1 = func1(in[n].x, in[n].y);                                        \
                                                                               \
        if (CHECK_NAN(out0))                                                   \
        {                                                                      \
            if (!CHECK_NAN(out1))                                              \
            {                                                                  \
                puts("FAIL");                                                  \
                return -1;                                                     \
            }                                                                  \
        }                                                                      \
        else if (out1 == zero)                                                 \
            err = tmpl_LDouble_Abs((long double)(out0 - out1));                \
        else                                                                   \
            err = tmpl_LDouble_Abs((long double)((out0 - out1)/out1));         \
                                                                               \
        if (err > eps)                                                         \
        {                                                                      \
            puts("FAIL");                                                      \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
    return 0;                                                                  \
}
