#include <libtmpl/include/tmpl_polynomial.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_string.h>
#include <stdlib.h>

void tmpl_PolynomialZ_Deriv(tmpl_PolynomialZ *poly, tmpl_PolynomialZ *deriv)
{
    signed long int *tmp;
    unsigned long int n;

    if (deriv == NULL)
        return;

    if (deriv->error_occurred)
        return;

    if (poly == NULL)
    {
        deriv->error_occurred = tmpl_True;
        deriv->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Deriv\n\n"
            "Input polynomial is NULL.\n"
        );
        return;
    }

    if (poly->error_occurred)
    {
        deriv->error_occurred = tmpl_True;
        deriv->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Deriv\n\n"
            "Input polynomial has error_occurred Boolean set to true.\n"
        );
        return;
    }

    if (poly->coeffs == NULL)
    {
        if (deriv->coeffs == NULL)
            return;
        else
        {
            free(deriv->coeffs);
            deriv->coeffs = NULL;
            return;
        }
    }

    if (poly->degree == 0UL)
    {
        deriv->degree = 0UL;
        if (deriv->coeffs == NULL)
        {
            deriv->coeffs = malloc(sizeof(*deriv->coeffs));
        }
        else
        {
            tmp = realloc(deriv->coeffs, sizeof(*deriv->coeffs));

            deriv->coeffs = tmp;
        }
        deriv->coeffs[0] = 0L;
    }
    else
    {
        deriv->degree = poly->degree - 1UL;
        if (deriv->coeffs == NULL)
        {
            deriv->coeffs = malloc(sizeof(*deriv->coeffs)*(deriv->degree+1UL));
        }
        else
        {
            tmp = realloc(deriv->coeffs,
                          sizeof(*deriv->coeffs)*(deriv->degree+1UL));

            deriv->coeffs = tmp;
        }
        for (n = 0UL; n <= deriv->degree; ++n)
            deriv->coeffs[n] = (signed long int)(n + 1UL)*poly->coeffs[n + 1UL];
    }
}
