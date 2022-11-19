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
#ifdef T
#undef T
#endif
#ifdef F
#undef F
#endif
#define T tmpl_True
#define F tmpl_False

/*  libtmpl math library found here.                                          */
#include <libtmpl/include/tmpl_math.h>

/*  puts function found here.                                                 */
#include <stdio.h>

/*  size_t typedef found here.                                                */
#include <stdlib.h>

/*  DBL_MIN, DBL_MAX, and other constants found here.                         */
#include <float.h>

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
