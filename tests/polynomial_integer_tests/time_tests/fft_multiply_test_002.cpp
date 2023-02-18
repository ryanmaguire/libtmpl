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

/*  TODO: Fix this absolute mess of a test.                                   */

#include <libtmpl/include/tmpl_polynomial_integer.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_fft.h>
#include <boost/math/tools/polynomial.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace boost::math::tools;

static void rand_poly(int *coeffs, size_t deg)
{
    size_t n;
    for (n = (size_t)0; n <= deg; ++n)
        coeffs[n] = rand() & 20;
}

static void
poly_prod(const tmpl_IntPolynomial *P,
          const tmpl_IntPolynomial *Q,
          tmpl_IntPolynomial *out,
          void *buffer)
{
    size_t n;
    void *tmp;
    const size_t len = 2*P->degree + (size_t)1;
    tmpl_ComplexDouble *c = (tmpl_ComplexDouble *)buffer;
    tmpl_ComplexDouble *d = c + len;

    for (n = (size_t)0; n <= P->degree; ++n)
    {
        c[n].dat[0] = (double)P->coeffs[n];
        c[n].dat[1] = 0.0;
        d[n].dat[0] = (double)Q->coeffs[n];
        d[n].dat[1] = 0.0;
    }

    for (n = P->degree + (size_t)1; n < len; ++n)
    {
        c[n].dat[0] = 0.0;
        c[n].dat[1] = 0.0;
        d[n].dat[0] = 0.0;
        d[n].dat[1] = 0.0;
    }

    tmpl_CDouble_FFT(c, c, len);
    tmpl_CDouble_FFT(d, d, len);

    for (n = (size_t)0; n < len; ++n)
        c[n] = tmpl_CDouble_Multiply(c[n], d[n]);

    tmpl_CDouble_IFFT(c, c, len);

    out->degree = len - (size_t)1;
    tmp = realloc(out->coeffs, sizeof(*out->coeffs)*len);
    out->coeffs = (int *)tmp;

    for (n = (size_t)0; n < len; ++n)
        out->coeffs[n] = (int)round(c[n].dat[0]);

    tmpl_IntPolynomial_Shrink(out);
}

int main(void)
{
    size_t n, m;
    clock_t t1, t2;
    const size_t deg = (size_t)100000;
    const size_t N = (size_t)10;
    polynomial<int> *P0 = (polynomial<int> *)(std::malloc(sizeof(*P0)*N));
    polynomial<int> *P1 = (polynomial<int> *)(std::malloc(sizeof(*P1)*N));
    polynomial<int> *P2 = (polynomial<int> *)(std::malloc(sizeof(*P2)*N));
    tmpl_IntPolynomial *Q0 = (tmpl_IntPolynomial *)(std::malloc(sizeof(*Q0)*N));
    tmpl_IntPolynomial *Q1 = (tmpl_IntPolynomial *)(std::malloc(sizeof(*Q1)*N));
    tmpl_IntPolynomial *Q2 = (tmpl_IntPolynomial *)(std::malloc(sizeof(*Q2)*N));
    int coeffs0[deg + (size_t)1], coeffs1[deg + (size_t)1];
    void *buffer = malloc(2*sizeof(tmpl_ComplexDouble)*(2*deg + 1));
    for (n = 0; n < N; ++n) {
        rand_poly(coeffs0, deg);
        rand_poly(coeffs1, deg);

        Q0[n].error_occurred = tmpl_False;
        Q0[n].error_message = NULL;
        Q0[n].degree = deg;
        Q0[n].coeffs = (int *)malloc(sizeof(*Q0[n].coeffs) * (deg + 1));

        Q1[n].error_occurred = tmpl_False;
        Q1[n].error_message = NULL;
        Q1[n].degree = deg;
        Q1[n].coeffs = (int *)malloc(sizeof(*Q0[n].coeffs) * (deg + 1));

        for (m = 0; m <= deg; ++m) {
            Q0[n].coeffs[m] = coeffs0[m];
            Q1[n].coeffs[m] = coeffs1[m];
        }

        tmpl_IntPolynomial_Init(&Q2[n]);
        P0[n] = polynomial<int>(coeffs0, deg);
        P1[n] = polynomial<int>(coeffs1, deg);
        P2[n] = polynomial<int>();
    }

    t1 = clock();
    for (n = (size_t)0; n < N; ++n)
        poly_prod(&Q0[n], &Q1[n], &Q2[n], buffer);
    t2 = clock();
    std::printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = (size_t)0; n < N; ++n)
        P2[n] = P0[n] * P1[n];
    t2 = clock();
    std::printf("boost:   %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    for (n = (size_t)0; n < N; ++n)
    {
        for (m = (size_t)0; m <= Q2[n].degree; ++m)
        {
            if (P2[n][m] != Q2[n].coeffs[m])
            {
                puts("FAIL");
                goto END;
            }
        }
    }

END:
    for (n = 0; n < N; ++n)
    {
        tmpl_IntPolynomial_Destroy(&Q0[n]);
        tmpl_IntPolynomial_Destroy(&Q1[n]);
        tmpl_IntPolynomial_Destroy(&Q2[n]);
    }

    std::free(P0);
    std::free(P1);
    std::free(P2);
    std::free(Q0);
    std::free(Q1);
    std::free(Q2);
    std::free(buffer);
}
