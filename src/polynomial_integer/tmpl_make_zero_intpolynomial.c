#include <stdlib.h>
#include <libtmpl/include/tmpl_string.h>
#include <libtmpl/include/tmpl_polynomial_integer.h>

void tmpl_IntPolynomial_Make_Zero(tmpl_IntPolynomial *poly)
{
    void *tmp;

    if (!poly)
        return;

    if (poly->error_occurred)
        return;

    tmp = realloc(poly->coeffs, sizeof(*poly->coeffs));

    if (!tmp)
    {
        poly->error_occurred = tmpl_True;
        poly->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Make_Zero\n\n"
            "realloc failed and returned NULL. Aborting.\n\n"
        );

        return;
    }

    else
    {
        poly->coeffs = tmp;
        poly->degree = (size_t)0;
        poly->coeffs[0] = 0;
    }
}
