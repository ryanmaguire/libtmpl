
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_string.h>
#include <libtmpl/include/tmpl_polynomial.h>
#include <stdlib.h>

void
tmpl_PolynomialZ_Set_Term(tmpl_PolynomialZ *poly,
                          unsigned long int term,
                          signed long int coefficient)
{
    unsigned long int n;
    signed long int *tmp;
    if (poly == NULL)
        return;

    if (poly->error_occurred)
        return;

    if (poly->coeffs == NULL)
    {
        poly->error_occurred = tmpl_True;
        poly->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Set_Term\n\n"
            "Input polynomial has NULL coeffs pointer.\n"
        );
        return;
    }

    if (poly->degree < term)
    {
        tmp = realloc(poly->coeffs, sizeof(*poly->coeffs) * (term + 1UL));
        if (tmp == NULL)
        {
            poly->error_occurred = tmpl_True;
            poly->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Set_Term\n\n"
                "realloc failed and returned NULL.\n"
            );   
        }
        else
            poly->coeffs = tmp;

        for (n = poly->degree + 1UL; n < term; ++n)
            poly->coeffs[n] = 0L;

        poly->coeffs[term] = coefficient;
        poly->degree = term;
    }
    else
        poly->coeffs[term] = coefficient;
    return;
}
