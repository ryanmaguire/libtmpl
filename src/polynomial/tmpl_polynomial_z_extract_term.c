
#include <libtmpl/include/tmpl_polynomial.h>

signed long int
tmpl_PolynomialZ_Extract_Term(tmpl_PolynomialZ *P, unsigned long int term)
{
    if (P == NULL)
        return 0L;
    else if (P->error_occurred)
        return 0L;
    else if (P->coeffs == NULL)
        return 0L;
    else if (P->degree < term)
        return 0L;
    else
        return P->coeffs[term];
}
