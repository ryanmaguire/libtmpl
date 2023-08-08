
/*  Polynomial typedef's and functions.                                       */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  printf function found here.                                               */
#include <stdio.h>

int main(void)
{
    const size_t deg = (size_t)4;
    int dat1[5] = {0, 0, 1, 2, 3};
    int dat2[5] = {0, 1, 2, 3, 4};
    tmpl_IntPolynomial P = tmpl_IntPolynomial_Create_From_Data(dat1, deg);
    tmpl_IntPolynomial Q = tmpl_IntPolynomial_Create_From_Data(dat2, deg);
    tmpl_IntPolynomial sum = tmpl_IntPolynomial_Empty();

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
