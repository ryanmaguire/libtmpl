#include <libtmpl/include/tmpl_polynomial_integer.h>
#include <stdio.h>

int main(void)
{
    const size_t p_deg = (size_t)4;
    const size_t q_deg = (size_t)5;
    tmpl_IntPolynomial P = tmpl_IntPolynomial_Random(p_deg);
    tmpl_IntPolynomial Q = tmpl_IntPolynomial_Random(q_deg);
    tmpl_IntPolynomial sum = tmpl_IntPolynomial_Empty();

    tmpl_IntPolynomial_Add(&P, &Q, &sum);

    printf("  ");
    tmpl_IntPolynomial_Print_String(stdout, &P);
    printf("  \n+ ");
    tmpl_IntPolynomial_Print_String(stdout, &Q);
    printf("\n= ");
    tmpl_IntPolynomial_Print_String(stdout, &sum);
    printf("\n");

    tmpl_IntPolynomial_Destroy(&P);
    tmpl_IntPolynomial_Destroy(&Q);
    tmpl_IntPolynomial_Destroy(&sum);
    return 0;
}
