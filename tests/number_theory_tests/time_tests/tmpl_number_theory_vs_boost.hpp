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
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <boost/integer/common_factor.hpp>

extern "C" {
#include <libtmpl/include/tmpl_number_theory.h>
}

static double time_as_double(clock_t a, clock_t b)
{
    double t = static_cast<double>(b - a);
    return t / static_cast<double>(CLOCKS_PER_SEC);
}

#define TEST1(type, f0, f1, N)                                                 \
                                                                               \
static type random_int(void)                                                   \
{                                                                              \
    int a = std::rand();                                                       \
                                                                               \
    while (a == 0)                                                             \
    {                                                                          \
        a = std::rand();                                                       \
    }                                                                          \
                                                                               \
    return static_cast<type>(a);                                               \
}                                                                              \
                                                                               \
int main(void)                                                                 \
{                                                                              \
    type *A, *B, *C, *X, *Y, *Z;                                               \
    unsigned long int n;                                                       \
    clock_t t1, t2;                                                            \
    type tmp;                                                                  \
    type max = 0;                                                              \
    double rms = 0.0;                                                          \
    A = static_cast<type *>(std::malloc(sizeof(*A)*N));                        \
    B = static_cast<type *>(std::malloc(sizeof(*B)*N));                        \
    C = static_cast<type *>(std::malloc(sizeof(*C)*N));                        \
    X = static_cast<type *>(std::malloc(sizeof(*X)*N));                        \
    Y = static_cast<type *>(std::malloc(sizeof(*Y)*N));                        \
    Z = static_cast<type *>(std::malloc(sizeof(*Z)*N));                        \
                                                                               \
    std::printf(#f0 " vs. " #f1 "\n");                                         \
    std::printf("samples: %lu\n", N);                                          \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        A[n] = X[n] = random_int();                                            \
        B[n] = Y[n] = random_int();                                            \
    }                                                                          \
                                                                               \
    t1 = std::clock();                                                         \
    for (n = 0; n < N; ++n)                                                    \
        C[n] = f0(A[n], B[n]);                                                 \
    t2 = std::clock();                                                         \
    printf("libtmpl: %f\n", time_as_double(t1, t2));                           \
                                                                               \
    t1 = std::clock();                                                         \
    for (n = 0; n < N; ++n)                                                    \
        Z[n] = f1(X[n], Y[n]);                                                 \
    t2 = std::clock();                                                         \
    printf("boost:   %f\n", time_as_double(t1, t2));                           \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        tmp = (Z[n] < C[n] ? C[n] - Z[n] : Z[n] - C[n]);                       \
        rms += tmp*tmp;                                                        \
        if (max < tmp)                                                         \
            max = tmp;                                                         \
    }                                                                          \
                                                                               \
    rms = std::sqrt(rms / static_cast<double>(N));                             \
    printf("rms error: %e\n", rms);                                            \
    printf("max error: %e\n", static_cast<double>(max));                       \
                                                                               \
    std::free(A);                                                              \
    std::free(B);                                                              \
    std::free(C);                                                              \
    std::free(X);                                                              \
    std::free(Y);                                                              \
    std::free(Z);                                                              \
    return 0;                                                                  \
}

#define TEST2(f, op, N)                                                        \
int main(void)                                                                 \
{                                                                              \
    tmpl_RationalNumber *A, *B;                                                \
    boost_rational *X, *Y;                                                     \
    unsigned long int n;                                                       \
    clock_t t1, t2;                                                            \
    double tmp;                                                                \
    double max = 0.0;                                                          \
    double rms = 0.0;                                                          \
    A = static_cast<tmpl_RationalNumber *>(std::malloc(sizeof(*A)*N));         \
    B = static_cast<tmpl_RationalNumber *>(std::malloc(sizeof(*B)*N));         \
    X = static_cast<boost_rational *>(std::malloc(sizeof(*X)*N));              \
    Y = static_cast<boost_rational *>(std::malloc(sizeof(*Y)*N));              \
                                                                               \
    std::printf(#f " vs. boost/rational " #op "\n");                           \
    std::printf("samples: %lu\n", N);                                          \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        signed long int a = random_int();                                      \
        signed long int b = random_int();                                      \
        signed long int c = random_int();                                      \
        signed long int d = random_int();                                      \
        A[n] = tmpl_RationalNumber_Create(a, b);                               \
        B[n] = tmpl_RationalNumber_Create(c, d);                               \
        X[n] = boost_rational(a, b);                                           \
        Y[n] = boost_rational(c, d);                                           \
    }                                                                          \
                                                                               \
    t1 = std::clock();                                                         \
    for (n = 0; n < N; ++n)                                                    \
        f(&A[n], &B[n]);                                                       \
    t2 = std::clock();                                                         \
    printf("libtmpl: %f\n", time_as_double(t1, t2));                           \
                                                                               \
    t1 = std::clock();                                                         \
    for (n = 0; n < N; ++n)                                                    \
        X[n] op Y[n];                                                          \
    t2 = std::clock();                                                         \
    printf("boost:   %f\n", time_as_double(t1, t2));                           \
                                                                               \
    for (n = 0UL; n < N; ++n)                                                  \
    {                                                                          \
        double x = boost::rational_cast<double>(X[n]);                         \
        double y = tmpl_RationalNumber_As_Double(&A[n]);                       \
        tmp = std::fabs((x - y)/y);                                            \
        rms += tmp*tmp;                                                        \
        if (max < tmp)                                                         \
            max = tmp;                                                         \
    }                                                                          \
                                                                               \
    rms = std::sqrt(rms / static_cast<double>(N));                             \
    printf("rms error: %e\n", rms);                                            \
    printf("max error: %e\n", max);                                            \
                                                                               \
    std::free(A);                                                              \
    std::free(B);                                                              \
    std::free(X);                                                              \
    std::free(Y);                                                              \
    return 0;                                                                  \
}
