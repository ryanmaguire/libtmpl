
/*  Polynomial typedef's and functions.                                       */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  printf function found here.                                               */
#include <stdio.h>

int main(void)
{
    const size_t length = (size_t)5;
    const size_t deg = length - 1;
    tmpl_IntPolynomial P = tmpl_IntPolynomial_Calloc(length);
    tmpl_IntPolynomial Q = tmpl_IntPolynomial_Calloc(length);
    tmpl_IntPolynomial sum = tmpl_IntPolynomial_Empty();

    /*  Set P = 1 + x^4 and Q = 1 - x^4.                                      */
    P.coeffs[0] = 1;
    P.coeffs[deg] = 1;
    Q.coeffs[0] = 1;
    Q.coeffs[deg] = -1;

    tmpl_IntPolynomial_Add(&P, &Q, &sum);

    printf("  ");
    tmpl_IntPolynomial_Print(stdout, &P);
    printf("  \n+ ");
    tmpl_IntPolynomial_Print(stdout, &Q);
    printf("\n= ");
    tmpl_IntPolynomial_Print(stdout, &sum);
    printf("\n");

    tmpl_IntPolynomial_Destroy(&P);
    tmpl_IntPolynomial_Destroy(&Q);
    tmpl_IntPolynomial_Destroy(&sum);
    return 0;
}
