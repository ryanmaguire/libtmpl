

#include <stddef.h>
#include <libtmpl/include/tmpl_polynomial_integer.h>

void
tmpl_IntPolynomial_ScaleSelf_Kernel(tmpl_IntPolynomial *poly, int scale)
{
    size_t n;
    for (n = (size_t)0; n <= poly->degree; ++n)
        poly->coeffs[n] *= scale;
}
