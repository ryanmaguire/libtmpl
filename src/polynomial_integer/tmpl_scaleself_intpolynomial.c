#include <libtmpl/include/tmpl_polynomial_integer.h>

void
tmpl_IntPolynomial_ScaleSelf(tmpl_IntPolynomial *poly, int scale)
{
    if (!poly)
        return;

    if (poly->error_occurred)
        return;

    if (!poly->coeffs)
        return;

    tmpl_IntPolynomial_ScaleSelf_Kernel(poly, scale);
}
