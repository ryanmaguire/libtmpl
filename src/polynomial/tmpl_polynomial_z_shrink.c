

#include <libtmpl/include/tmpl_polynomial.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_string.h>
#include <stdlib.h>

void tmpl_PolynomialZ_Shrink(tmpl_PolynomialZ *P)
{
    unsigned long int last, n;
    signed long int *tmp;
    if (P == NULL)
        return;

    if (P->coeffs == NULL)
        return;

    if (P->error_occurred)
        return;

    last = 0UL;
    for (n = 0UL; n <= P->degree; ++n)
        if (P->coeffs[n] != 0L)
            last = n;

    tmp = realloc(P->coeffs, sizeof(*P->coeffs) * (last+1));

    if (tmp == NULL)
    {
        P->error_occurred = tmpl_True;
        P->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Shrink\n\n"
            "realloc failed and returned NULL.\n"
        );
        return;
    }

    P->coeffs = tmp;
    P->degree = last;
    return;

}