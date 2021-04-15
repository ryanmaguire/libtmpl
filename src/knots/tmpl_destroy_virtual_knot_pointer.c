
#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>

void tmpl_Destroy_Virtual_Knot_Pointer(tmpl_VirtualKnot **K_ptr)
{
    if (K_ptr == NULL)
        return;
    else if (*K_ptr == NULL)
        return;

    tmpl_Destroy_Gauss_Tuple_Pointer(&(*K_ptr)->gauss_code);

    free(*K_ptr);
    *K_ptr = NULL;
    return;
}

