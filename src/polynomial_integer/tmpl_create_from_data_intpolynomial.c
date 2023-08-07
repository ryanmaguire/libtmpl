

#include <stdlib.h>
#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_string.h>
#include <libtmpl/include/tmpl_polynomial_integer.h>

#if TMPL_USE_MEMCPY == 1
#include <string.h>
#endif

tmpl_IntPolynomial
tmpl_IntPolynomial_Create_From_Data(const int *data, size_t len)
{
    tmpl_IntPolynomial out;

#if TMPL_USE_MEMCPY != 1
    size_t n;
#endif

    if (!data || len == (size_t)0)
    {
        tmpl_IntPolynomial_Init(&out);
        return out;
    }

    out.coeffs = malloc(sizeof(*out.coeffs) * len);

    if (!out.coeffs)
    {
        out.degree = (size_t)0;
        out.error_occurred = tmpl_True;
        out.error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Create_From_Data\n\n"
            "malloc failed and returned NULL. Aborting.\n\n"
        );
        return out;
    }

    out.error_message = NULL;
    out.error_occurred = tmpl_False;
    out.degree = len - (size_t)1;

#if TMPL_USE_MEMCPY == 1
    memcpy(out.coeffs, data, len*sizeof(*data));
#else
    for (n = (size_t)0; n < len; ++n)
        out.coeffs[n] = data[n];
#endif

    return out;
}
