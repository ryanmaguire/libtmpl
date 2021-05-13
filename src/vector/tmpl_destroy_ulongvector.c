
#include <libtmpl/include/tmpl_vector.h>
#include <stdlib.h>

void tmpl_Destroy_ULongVector(tmpl_ULongVector **vec_ptr)
{
    tmpl_ULongVector *vec;
    if (vec_ptr == NULL)
        return;

    if (*vec_ptr == NULL)
        return;

    vec = *vec_ptr;

    if (vec->data != NULL)
    {
        free(vec->data);
        vec->data = NULL;
    }

    free(vec);
    vec = NULL;

    return;
}
