

#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>

tmpl_CrossingIndices *
tmpl_Find_Crossing_Indices(tmpl_VirtualKnot *K)
{
    tmpl_CrossingIndices *Indices;
    tmpl_GaussTuple *T;
    unsigned long int n, ind;

    if (K == NULL)
        return NULL;

    if (K->number_of_crossings == 0UL)
        return NULL;

    Indices = malloc(sizeof(*Indices) * K->number_of_crossings);

    for (n = 0; n < 2UL * K->number_of_crossings; ++n)
    {
        T = &(K->gauss_code[n]);
        ind = T->crossing_number;

        if (T->crossing_type == tmpl_OverCrossing)
            Indices[ind].over = n;
        else
            Indices[ind].under = n;
    }
    return Indices;
}
