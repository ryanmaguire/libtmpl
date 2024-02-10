#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char str[] = "O0+U1+O2+O3-O4+U0+U3-U2+O1+U4+";
    tmpl_VirtualKnot *K = tmpl_Gauss_Code_From_String(str);

    printf("Input Gauss Code: ");
    tmpl_Print_Gauss_Code(K);

    if (tmpl_Is_Gauss_Code_Valid(K))
        puts("This is a valid Gauss code.\n");
    else
        puts("This is an invalid Gauss code.\n");

    printf("Genus: %lu\n\n", tmpl_Virtual_Knot_Genus(K));

    tmpl_Destroy_Virtual_Knot_Pointer(&K);
    return 0;
}

