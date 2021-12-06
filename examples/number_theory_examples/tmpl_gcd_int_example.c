#include <libtmpl/include/tmpl_number_theory.h>
#include <stdio.h>

int main(void)
{
    int n = 0x7FFFFFFF;
    int m = -0x7FFFFFFF;
    unsigned int gcd = tmpl_Int_GCD(m, n);
    printf("GCD = %u\n", gcd);
    return 0;
}

