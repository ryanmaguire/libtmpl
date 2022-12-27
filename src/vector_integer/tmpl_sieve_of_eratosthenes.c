/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 ******************************************************************************
 *  This file contains he Sieve of Eratosthenes, which is an algorithm for    *
 *  computing all prime numbers up to some fixed number N.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2021/04/19                                                    *
 ******************************************************************************/

/*  malloc and size_t typedef given here.                                     */
#include <stdlib.h>

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_vector_integer.h>

/*  tmpl_strdup found here.                                                   */
#include <libtmpl/include/tmpl_string.h>

#if 0

/*  Function for computing all prime numbers less than N.                     */
tmpl_ULongVector *tmpl_ULong_Sieve_of_Eratosthenes(unsigned long int N)
{
    tmpl_ULongVector *sieve = malloc(sizeof(*sieve));
    tmpl_Bool *is_prime;
    unsigned long int n, k;

    /*  Check if malloc failed. Return NULL if so.                            */
    if (sieve == NULL)
        return NULL;

    /*  0 and 1 are not prime. In this case the out vector is empty.          */
    if (N < 2)
    {
        sieve->data = NULL;
        sieve->length = 0UL;
        return sieve;
    }

    is_prime = malloc(sizeof(*is_prime) * (N - 1UL));
    if (is_prime == NULL)
    {
        sieve->data = NULL;
        sieve->length = (size_t)0;
        sieve->error_occurred = tmpl_True;
        sieve->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "    tmpl_ULong_Sieve_of_Eratosthenes\n\n"
            "malloc failed for is_prime and returned NULL."
        );
        return sieve;
    }

    for (n = 2UL; n <= N; ++n)
        is_prime[N - 2UL] = tmpl_True;

    for (n = 2UL; n*n <= N; ++n)
    {
        if (is_prime[n - 2UL])
        {
            for (k = n*n; k <= N; k += n)
                is_prime[k - 2UL] = tmpl_False;
        }
    }

    sieve->length = 0UL;
    for (n = 0UL; n < N; ++n)
    {
        if (is_prime[n])
            sieve->length++;
    }

    sieve->data = malloc(sizeof(*sieve->data) * sieve->length);
    k = 0U;
    for (n = 0UL; n < sieve->length; ++n)
    {
        while (!is_prime[k - 2UL])
            ++k;
        sieve->data[n] = k;
        ++k;
    }

    return sieve;
}

#else

tmpl_ULongVector *tmpl_ULong_Sieve_of_Eratosthenes(unsigned long N)
{
    tmpl_ULongVector *sieve = malloc(sizeof(*sieve));
    tmpl_Bool *is_prime, *has_been_visited;
    unsigned long n, k, factor;

    if (sieve == NULL)
        return NULL;

    if (N < 2)
    {
        sieve->data = NULL;
        sieve->length = 0UL;
        return sieve;
    }

    is_prime = malloc(sizeof(*is_prime) * N);
    if (is_prime == NULL)
    {
        free(sieve);
        return NULL;
    }

    has_been_visited = calloc(sizeof(*has_been_visited), N);
    if (has_been_visited == NULL)
    {
        free(sieve);
        return NULL;
    }

    n = 2UL;
    sieve->length = 0UL;
    factor = 1UL;

    while (n < N)
    {
        if (!has_been_visited[n])
        {
            is_prime[n] = tmpl_True;
            sieve->length++;
            k = n + factor*n;
            while(k < N)
            {
                is_prime[k] = tmpl_False;
                has_been_visited[k] = tmpl_True;
                k += factor*n;
            }
        }
        factor = n;
        ++n;
    }

    sieve->data = malloc(sizeof(*sieve->data) * sieve->length);
    k = 0U;
    for (n=0U; n<sieve->length; ++n)
    {
        while (!is_prime[k])
            ++k;
        sieve->data[n] = k;
        ++k;
    }

    return sieve;
}

#endif
