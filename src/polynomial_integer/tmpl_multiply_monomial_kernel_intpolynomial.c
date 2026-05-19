#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/compat/tmpl_realloc.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_string.h>
#include <libtmpl/include/tmpl_polynomial_integer.h>

void
tmpl_IntPolynomial_Multiply_Monomial_Kernel(const tmpl_IntPolynomial *P,
                                            size_t deg, int coeff,
                                            tmpl_IntPolynomial *prod)
{
    size_t n;
    const size_t len = P->degree + deg + 1;

    if (prod->degree != P->degree + deg)
    {

        void * const tmp = TMPL_REALLOC(prod->coeffs, len);

        if (!tmp)
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Multiply_Monomial\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }

        else
        {
            prod->coeffs = TMPL_CAST(tmp, int *);
            prod->degree = P->degree + deg;
        }
    }

    for (n = 0; n <= P->degree; ++n)
        prod->coeffs[n + deg] = coeff * P->coeffs[n];

    for (n = 0; n < deg; ++n)
        prod->coeffs[n] = 0;
}
