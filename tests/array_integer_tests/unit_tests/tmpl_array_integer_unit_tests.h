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
#ifndef TMPL_ARRAY_INTEGER_UNIT_TESTS_H
#define TMPL_ARRAY_INTEGER_UNIT_TESTS_H
#include <stdio.h>
#include <libtmpl/include/tmpl_array_integer.h>

#define TEST1(type, func, arr, ans)                                            \
int main(void)                                                                 \
{                                                                              \
    const type in[] = arr;                                                     \
    const size_t len = sizeof(in) / sizeof(in[0]);                             \
    const type out = func(in, len);                                            \
                                                                               \
    if (out != ans)                                                            \
        puts("FAIL");                                                          \
    else                                                                       \
      puts("PASS");                                                            \
                                                                               \
    return 0;                                                                  \
}

#define TEST2(type, func, arr, ansa, ansb)                                     \
int main(void)                                                                 \
{                                                                              \
    const type in[] = arr;                                                     \
    const size_t len = sizeof(in) / sizeof(in[0]);                             \
    type outa, outb;                                                           \
    func(in, len, &outa, &outb);                                               \
                                                                               \
    if ((outa != ansa) && (outb != ansb))                                      \
        puts("FAIL");                                                          \
    else                                                                       \
        puts("PASS");                                                          \
                                                                               \
    return 0;                                                                  \
}

#define TEST3(type, func, arr, ans)                                            \
int main(void)                                                                 \
{                                                                              \
    const type in[] = arr;                                                     \
    const size_t len = sizeof(in) / sizeof(in[0]);                             \
    const size_t out = func(in, len);                                          \
                                                                               \
    if (out != ans)                                                            \
        puts("FAIL");                                                          \
    else                                                                       \
      puts("PASS");                                                            \
                                                                               \
    return 0;                                                                  \
}

#endif
