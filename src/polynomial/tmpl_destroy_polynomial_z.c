
#include <libtmpl/include/tmpl_polynomial.h>
#include <stdlib.h>

void tmpl_Destroy_PolynomialZ(tmpl_PolynomialZ **poly_ptr)
{
    tmpl_PolynomialZ *poly;

    if (poly_ptr == NULL)
        return;

    if (*poly_ptr == NULL)
        return;

    poly = *poly_ptr;

    if (poly->coeffs != NULL)
    {
        free(poly->coeffs);
        poly->coeffs = NULL;
    }

    if (poly->error_message != NULL)
    {
        free(poly->error_message);
        poly->error_message = NULL;
    }

    free(poly);
    poly = NULL;
    return;
}
