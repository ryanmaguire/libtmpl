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
#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif
}

#ifdef _MSC_VER
static size_t memsize()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return static_cast<size_t>(1000ULL*status.ullAvailPhys);
}
#else
static size_t memsize()
{
    long pages = sysconf(_SC_AVPHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return static_cast<size_t>(pages * page_size);
}
#endif

static double time_as_double(clock_t a, clock_t b)
{
    double t = static_cast<double>(b - a);
    return t / static_cast<double>(CLOCKS_PER_SEC);
}

#define NSAMPS(a) (3*memsize()/(4*sizeof(a)))
#define TEST1(type, f0, f1)                                                    \
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
    double tmpd;                                                               \
    const size_t N = NSAMPS(type) / 6;                                         \
    A = static_cast<type *>(std::malloc(sizeof(*A)*N));                        \
    if (!A)                                                                    \
    {                                                                          \
    	std::puts("Malloc failed for B. Aborting.");                           \
    	return -1;                                                             \
    }                                                                          \
    B = static_cast<type *>(std::malloc(sizeof(*B)*N));                        \
    if (!B)                                                                    \
    {                                                                          \
    	std::puts("Malloc failed for B. Aborting.");                           \
    	std::free(A);                                                          \
    	return -1;                                                             \
    }                                                                          \
    C = static_cast<type *>(std::malloc(sizeof(*C)*N));                        \
    if (!C)                                                                    \
    {                                                                          \
    	std::puts("Malloc failed for C. Aborting.");                           \
    	std::free(A);                                                          \
    	std::free(B);                                                          \
    	return -1;                                                             \
    }                                                                          \
    X = static_cast<type *>(std::malloc(sizeof(*X)*N));                        \
    if (!X)                                                                    \
    {                                                                          \
    	std::puts("Malloc failed for X. Aborting.");                           \
    	std::free(A);                                                          \
    	std::free(B);                                                          \
    	std::free(C);                                                          \
    	return -1;                                                             \
    }                                                                          \
    Y = static_cast<type *>(std::malloc(sizeof(*Y)*N));                        \
    if (!Y)                                                                    \
    {                                                                          \
    	std::puts("Malloc failed for Y. Aborting.");                           \
    	std::free(A);                                                          \
    	std::free(B);                                                          \
    	std::free(C);                                                          \
    	std::free(X);                                                          \
    	return -1;                                                             \
    }                                                                          \
    Z = static_cast<type *>(std::malloc(sizeof(*Z)*N));                        \
    if (!Z)                                                                    \
    {                                                                          \
    	std::puts("Malloc failed for Z. Aborting.");                           \
    	std::free(A);                                                          \
    	std::free(B);                                                          \
    	std::free(C);                                                          \
    	std::free(X);                                                          \
    	std::free(Y);                                                          \
    	return -1;                                                             \
    }                                                                          \
                                                                               \
    std::printf(#f0 " vs. " #f1 "\n");                                         \
    std::printf("samples: %zu\n", N);                                          \
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
        tmpd = static_cast<double>(tmp);                                       \
        rms += tmpd*tmpd;                                                      \
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
