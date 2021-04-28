

#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>

void
tmpl_Destroy_Crossing_Indices(tmpl_CrossingIndices **Indices)
{
    if (Indices == NULL)
        return;
    
    if (*Indices == NULL)
        return;

    free(*Indices);
    *Indices = NULL;
    return;
}
