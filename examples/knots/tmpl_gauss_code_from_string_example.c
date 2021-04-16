#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char str[] = "O0+U1+O2+U0+O1+U2+";
	int to_delete = 0;
	tmpl_VirtualKnot *K = tmpl_Gauss_Code_From_String(str);

	printf("Before:\t");
	tmpl_Print_Gauss_Code(K);

	printf("Deleting Crossing: %d\n", to_delete);
	tmpl_Delete_Virtual_Knot_Crossing(K, to_delete);

	printf("After:\t");
	tmpl_Print_Gauss_Code(K);
	tmpl_Destroy_Virtual_Knot_Pointer(&K);
	return 0;
}
