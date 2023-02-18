

#include <stdlib.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_string.h>
#include <libtmpl/include/tmpl_polynomial_integer.h>

void tmpl_IntPolynomial_Shrink(tmpl_IntPolynomial *P)
{
    size_t new_deg;
    void *tmp;
    if (!P)
        return;

    if (P->error_occurred)
        return;

    if (!P->coeffs || P->degree == (size_t)0)
        return;

    new_deg = P->degree;

    while (!P->coeffs[new_deg]) {
        --new_deg;
    }

    if (new_deg == P->degree)
        return;

    tmp = realloc(P->coeffs, sizeof(*P->coeffs) * (new_deg + (size_t)1));

    if (tmp)
    {
        P->coeffs = tmp;
        P->degree = new_deg;
    }
    else
    {
        P->error_occurred = tmpl_True;
        P->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Naive_Multiply\n\n"
            "realloc failed. Aborting.\n\n"
        );
    }
}
