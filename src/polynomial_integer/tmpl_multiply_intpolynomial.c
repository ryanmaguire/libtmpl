#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  TODO:
 *      Make this a hybrid Karatsuba / Naive algorithm, pending degrees.
 *      Experiment with DFT's for large degree polynomials.
 */

void
tmpl_IntPolynomial_Multiply(const tmpl_IntPolynomial *P,
                            const tmpl_IntPolynomial *Q,
                            tmpl_IntPolynomial *prod)
{
    tmpl_IntPolynomial_Naive_Multiply(P, Q, prod);
}
