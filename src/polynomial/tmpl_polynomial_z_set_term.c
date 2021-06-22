
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_string.h>
#include <libtmpl/include/tmpl_polynomial.h>

void
tmpl_PolynomialZ_Set_Term(tmpl_PolynomialZ *P,
                          unsigned long int term,
                          signed long int coefficient)
{
    if (P == NULL)
        return;

    if (P->error_occurred)
        return;

    if (P->coeffs == NULL)
    {
        P->error_occurred = tmpl_True;
        P->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Set_Term\n\n"
            "Input polynomial has NULL coeffs pointer.\n"
        );
        return;
    }

    if (P->degree < term)
    {
        P->error_occurred = tmpl_True;
        P->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Set_Term\n\n"
            "Input term is greater than the degree of the polynomial.\n"
        );
        return;
    }

    P->coeffs[term] = coefficient;
    return;
}
