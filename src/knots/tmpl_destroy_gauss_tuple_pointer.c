
#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>

void tmpl_Destroy_Gauss_Tuple_Pointer(tmpl_GaussTuple **T_ptr)
{
    if (T_ptr == NULL)
        return;
    else if (*T_ptr == NULL)
        return;

    free(*T_ptr);
    *T_ptr = NULL;
    return;
}
