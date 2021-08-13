/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

#include <limits.h>

#if ULONG_MAX == 0xFFFFFFFF

static const unsigned long int tmpl_factorial_values[13] = {
    1UL, 1UL, 2UL, 6UL,
    24, 120UL, 720UL, 5040UL,
    40320UL, 362880UL, 3628800UL, 39916800UL,
    479001600UL
};

/*  Factorial for 32-bit long.                                                */
unsigned long int tmpl_Factorial(unsigned int n)
{
    /*  n! returns an overflow for 32-bit long when n > 12. To indicate an    *
     *  error, return 0. n! is never zero for any positive integer.           */
    if (n > 12UL)
        return 0UL;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_factorial_values[n];
}
/*  End of tmpl_Factorial.                                                    */

#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFF

static const unsigned long int tmpl_factorial_values[21] = {
    1UL, 1UL, 2UL, 6UL, 24UL,
    120UL, 720UL, 5040UL, 40320UL, 362880UL,
    3628800UL, 39916800UL, 479001600UL, 6227020800UL, 87178291200UL,
    1307674368000UL, 20922789888000UL, 355687428096000UL, 6402373705728000UL,
    121645100408832000UL, 2432902008176640000UL
};

/*  Factorial for 64-bit long.                                                */
unsigned long int tmpl_Factorial(unsigned int n)
{
    /*  n! returns an overflow for 64-bit long when n > 20. To indicate an    *
     *  error, return 0. n! is never zero for any positive integer.           */
    if (n > 20UL)
        return 0UL;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_factorial_values[n];
}
/*  End of tmpl_Factorial.                                                    */

#else
/*  Portable algorithm for other sizes. long must be at least 32-bit, so we   *
 *  pre-compute a few values.                                                 */

static const unsigned long int tmpl_factorial_values[13] = {
    1UL, 1UL, 2UL, 6UL,
    24, 120UL, 720UL, 5040UL,
    40320UL, 362880UL, 3628800UL, 39916800UL,
    479001600UL
};

/*  Factorial function.                                                       */
unsigned long tmpl_Factorial(unsigned int N)
{
    unsigned int n;
    unsigned long factorial;

    if (n < 13)
        return tmpl_factorial_values[n];
    else
        factor = tmpl_factorial_values[12];

    for (n = 13UL; n <= N; ++n)
        factorial *= n;

    return factorial;
}
/*  End of factorial function.                                                */

#endif

