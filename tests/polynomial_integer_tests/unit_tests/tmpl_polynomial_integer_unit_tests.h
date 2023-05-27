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
#include <libtmpl/include/tmpl_polynomial_integer.h>
#include <stdio.h>

#define TEST1(func, pdat, qdat, rdat, type, ptype, pcreate, destroy)           \
int main(void)                                                                 \
{                                                                              \
    const type P_data[] = pdat;                                                \
    const type Q_data[] = qdat;                                                \
    const type result[] = rdat;                                                \
    const size_t P_len = sizeof(P_data) / sizeof(P_data[0]);                   \
    const size_t Q_len = sizeof(Q_data) / sizeof(Q_data[0]);                   \
    const size_t result_len = sizeof(result) / sizeof(result[0]);              \
    ptype P = pcreate(P_data, P_len);                                          \
    ptype Q = pcreate(Q_data, Q_len);                                          \
    ptype out = pcreate(NULL, (size_t)0);                                      \
    size_t n;                                                                  \
    func(&P, &Q, &out);                                                        \
                                                                               \
    if (!out.coeffs)                                                           \
    {                                                                          \
        puts("FAIL: out.coeffs is NULL.");                                     \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    if (out.error_occurred)                                                    \
    {                                                                          \
        puts("FAIL: Function set out.error_occurred = true.");                 \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    for (n = (size_t)0; n < result_len; ++n)                                   \
    {                                                                          \
        if (out.coeffs[n] != result[n])                                        \
        {                                                                      \
            puts("FAIL: out.coeffs != result");                                \
            goto CLEANUP;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
                                                                               \
CLEANUP:                                                                       \
    destroy(&P);                                                               \
    destroy(&Q);                                                               \
    destroy(&out);                                                             \
    return 0;                                                                  \
}

#define TEST2(func, pdat, rdat, type, ptype, pcreate, destroy)                 \
int main(void)                                                                 \
{                                                                              \
    const type P_data[] = pdat;                                                \
    const type result[] = rdat;                                                \
    const size_t P_len = sizeof(P_data) / sizeof(P_data[0]);                   \
    const size_t result_len = sizeof(result) / sizeof(result[0]);              \
    ptype P = pcreate(P_data, P_len);                                          \
    ptype Q = pcreate(NULL, (size_t)0);                                        \
    ptype out = pcreate(NULL, (size_t)0);                                      \
    size_t n;                                                                  \
    func(&P, &Q, &out);                                                        \
                                                                               \
    if (!out.coeffs)                                                           \
    {                                                                          \
        puts("FAIL: out.coeffs is NULL.");                                     \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    if (out.error_occurred)                                                    \
    {                                                                          \
        puts("FAIL: Function set out.error_occurred = true.");                 \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    for (n = (size_t)0; n < result_len; ++n)                                   \
    {                                                                          \
        if (out.coeffs[n] != result[n])                                        \
        {                                                                      \
            puts("FAIL: out.coeffs != result");                                \
            goto CLEANUP;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
                                                                               \
CLEANUP:                                                                       \
    destroy(&P);                                                               \
    destroy(&Q);                                                               \
    destroy(&out);                                                             \
    return 0;                                                                  \
}

#define TEST3(func, ptype, pempty, destroy)                                    \
int main(void)                                                                 \
{                                                                              \
    ptype P = pempty();                                                        \
    ptype Q = pempty();                                                        \
    ptype out = pempty();                                                      \
    func(&P, &Q, &out);                                                        \
                                                                               \
    if (out.error_occurred)                                                    \
    {                                                                          \
        puts("FAIL: Function set out.error_occurred = true.");                 \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    if (out.coeffs == NULL && out.degree == (size_t)0)                         \
        puts("PASS");                                                          \
    else                                                                       \
        puts("FAIL: Output is not the empty polynomial.");                     \
                                                                               \
CLEANUP:                                                                       \
    destroy(&out);                                                             \
    return 0;                                                                  \
}

#define TEST4(func, ptype, pempty, destroy)                                    \
int main(void)                                                                 \
{                                                                              \
    ptype *P_ptr = NULL;                                                       \
    ptype *Q_ptr = NULL;                                                       \
    ptype out = pempty();                                                      \
    func(P_ptr, Q_ptr, &out);                                                  \
                                                                               \
    if (out.error_occurred)                                                    \
    {                                                                          \
        puts("FAIL: Function set out.error_occurred = true.");                 \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    if (out.coeffs == NULL && out.degree == (size_t)0)                         \
        puts("PASS");                                                          \
    else                                                                       \
        puts("FAIL: Output is not the empty polynomial.");                     \
                                                                               \
CLEANUP:                                                                       \
    destroy(&out);                                                             \
    return 0;                                                                  \
}

#define TEST5(func, ptype, prand, destroy)                                     \
int main(void)                                                                 \
{                                                                              \
    const size_t deg = (size_t)100;                                            \
    ptype *P_ptr = NULL;                                                       \
    ptype *Q_ptr = NULL;                                                       \
    ptype out = prand(deg);                                                    \
    func(P_ptr, Q_ptr, &out);                                                  \
                                                                               \
    if (out.error_occurred)                                                    \
    {                                                                          \
        puts("FAIL: Function set out.error_occurred = true.");                 \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    if (out.coeffs == NULL && out.degree == (size_t)0)                         \
        puts("PASS");                                                          \
    else                                                                       \
        puts("FAIL: Output is not the empty polynomial.");                     \
                                                                               \
CLEANUP:                                                                       \
    destroy(&out);                                                             \
    return 0;                                                                  \
}

#define TEST6(func, pdat, qdat, rdat, type, ptype, pcreate, destroy)           \
int main(void)                                                                 \
{                                                                              \
    const type P_data[] = pdat;                                                \
    const type Q_data[] = qdat;                                                \
    const type result[] = rdat;                                                \
    const size_t P_len = sizeof(P_data) / sizeof(P_data[0]);                   \
    const size_t Q_len = sizeof(Q_data) / sizeof(Q_data[0]);                   \
    const size_t result_len = sizeof(result) / sizeof(result[0]);              \
    ptype P = pcreate(P_data, P_len);                                          \
    ptype Q = pcreate(Q_data, Q_len);                                          \
    size_t n;                                                                  \
    func(&P, &Q);                                                              \
                                                                               \
    if (!P.coeffs)                                                             \
    {                                                                          \
        puts("FAIL: P.coeffs is NULL.");                                       \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    if (P.error_occurred)                                                      \
    {                                                                          \
        puts("FAIL: Function set P.error_occurred = true.");                   \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    for (n = (size_t)0; n < result_len; ++n)                                   \
    {                                                                          \
        if (P.coeffs[n] != result[n])                                          \
        {                                                                      \
            puts("FAIL: P.coeffs != result");                                  \
            goto CLEANUP;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
                                                                               \
CLEANUP:                                                                       \
    destroy(&P);                                                               \
    destroy(&Q);                                                               \
    return 0;                                                                  \
}

#define TEST7(func, pdat, rdat, type, ptype, pcreate, destroy)                 \
int main(void)                                                                 \
{                                                                              \
    const type P_data[] = pdat;                                                \
    const type result[] = rdat;                                                \
    const size_t P_len = sizeof(P_data) / sizeof(P_data[0]);                   \
    const size_t result_len = sizeof(result) / sizeof(result[0]);              \
    ptype P = pcreate(P_data, P_len);                                          \
    ptype Q = pcreate(NULL, (size_t)0);                                        \
    size_t n;                                                                  \
    func(&P, &Q);                                                              \
                                                                               \
    if (!P.coeffs)                                                             \
    {                                                                          \
        puts("FAIL: P.coeffs is NULL.");                                       \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    if (P.error_occurred)                                                      \
    {                                                                          \
        puts("FAIL: Function set P.error_occurred = true.");                   \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    for (n = (size_t)0; n < result_len; ++n)                                   \
    {                                                                          \
        if (P.coeffs[n] != result[n])                                          \
        {                                                                      \
            puts("FAIL: P.coeffs != result");                                  \
            goto CLEANUP;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    puts("PASS");                                                              \
                                                                               \
CLEANUP:                                                                       \
    destroy(&P);                                                               \
    destroy(&Q);                                                               \
    return 0;                                                                  \
}

#define TEST8(func, ptype, pcreate, destroy)                                   \
int main(void)                                                                 \
{                                                                              \
    ptype P = pcreate(NULL, (size_t)0);                                        \
    ptype Q = pcreate(NULL, (size_t)0);                                        \
    func(&P, &Q);                                                              \
                                                                               \
    if (P.error_occurred)                                                      \
    {                                                                          \
        puts("FAIL: Function set P.error_occurred = true.");                   \
        goto CLEANUP;                                                          \
    }                                                                          \
                                                                               \
    if (P.coeffs == NULL && P.degree == (size_t)0)                             \
        puts("PASS");                                                          \
    else                                                                       \
        puts("FAIL: Output is not the empty polynomial.");                     \
                                                                               \
CLEANUP:                                                                       \
    destroy(&P);                                                               \
    destroy(&Q);                                                               \
    return 0;                                                                  \
}
