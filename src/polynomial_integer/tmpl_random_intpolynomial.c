#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_polynomial_integer.h>
#include <libtmpl/include/tmpl_string.h>
#include <stdlib.h>
#include <time.h>

tmpl_IntPolynomial
tmpl_IntPolynomial_Random(size_t degree)
{
    tmpl_IntPolynomial out;
    const size_t len = degree + (size_t)1;
    size_t n;
    static unsigned int seed = 3U;
    out.coeffs = malloc(sizeof(*out.coeffs) * len);

    if (!out.coeffs)
    {
        out.error_occurred = tmpl_True;
        out.error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Random\n\n"
            "malloc failed. Aborting.\n\n"
        );

        out.degree = (size_t)0;
        return out;
    }

    out.degree = degree;
    out.error_occurred = tmpl_False;
    out.error_message = NULL;

    seed *= 65407U;
    srand(seed);

    for (n = (size_t)0; n < len; ++n)
        out.coeffs[n] = rand() % 10;

    return out;
}
