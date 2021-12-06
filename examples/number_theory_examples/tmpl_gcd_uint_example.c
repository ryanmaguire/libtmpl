#include <libtmpl/include/tmpl_number_theory.h>
#include <stdio.h>

int main(void)
{
    unsigned int n = 255U;
    unsigned int m = 505U;
    unsigned int gcd = tmpl_UInt_GCD(m, n);
    printf("GCD = %u\n", gcd);
    return 0;
}

