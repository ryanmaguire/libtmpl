#include <libtmpl/include/tmpl_polynomial.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    tmpl_PolynomialZ *P = tmpl_Create_Zero_PolynomialZ(1);
    tmpl_PolynomialZ *Q = tmpl_Create_Zero_PolynomialZ(1);
    tmpl_PolynomialZ *prod = tmpl_Create_Empty_PolynomialZ();
    tmpl_PolynomialZ *sum = tmpl_Create_Empty_PolynomialZ();

    P->coeffs[0] = 1UL;
    P->coeffs[1] = 1UL;
    Q->coeffs[0] = 1UL;
    Q->coeffs[1] = 1UL;

    tmpl_PolynomialZ_Multiply(P, Q, prod);
    tmpl_PolynomialZ_Add(P, Q, sum);
    char *Pstr = tmpl_PolynomialZ_Get_String(P);
    char *Qstr = tmpl_PolynomialZ_Get_String(Q);
    char *prodstr = tmpl_PolynomialZ_Get_String(prod);
    char *sumstr = tmpl_PolynomialZ_Get_String(sum);
    printf("(%s) * (%s) = %s\n", Pstr, Qstr, prodstr);
    printf("(%s) + (%s) = %s\n", Pstr, Qstr, sumstr);


    puts("Trying out print function:");

    fprintf(stderr, "P = ");
    tmpl_PolynomialZ_Print_String(stderr, P);
    puts("");

    fprintf(stderr, "Q = ");
    tmpl_PolynomialZ_Print_String(stderr, Q);
    puts("");

    fprintf(stderr, "P * Q = ");
    tmpl_PolynomialZ_Print_String(stderr, prod);
    puts("");

    fprintf(stderr, "P + Q = ");
    tmpl_PolynomialZ_Print_String(stderr, sum);
    puts("");

    tmpl_Destroy_PolynomialZ(&P);
    tmpl_Destroy_PolynomialZ(&Q);
    tmpl_Destroy_PolynomialZ(&prod);
    tmpl_Destroy_PolynomialZ(&sum);
    free(prodstr);
    free(sumstr);
    free(Qstr);
    free(Pstr);
    return 0;
}
