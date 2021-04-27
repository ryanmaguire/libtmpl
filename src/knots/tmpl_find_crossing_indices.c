

#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>

tmpl_CrossingIndices *
tmpl_Find_Crossing_Indices(tmpl_VirtualKnot *K)
{
    tmpl_CrossingIndices *Indices;
    unsigned long int n, ind;
    tmpl_Bool *has_been_set;

    if (K == NULL)
        return NULL;

    if (K->number_of_crossings == 0UL)
        return NULL;

    Indices = malloc(sizeof(*Indices) * K->number_of_crossings);
    has_been_set = calloc(sizeof(*has_been_set), K->number_of_crossings);

    for (n = 0; n < 2UL * K->number_of_crossings; ++n)
    {
        ind = (K->gauss_code[n]).crossing_number;

        if (has_been_set[ind])
        {
            Indices[ind].zeroth = n;
            has_been_set[ind] = tmpl_True;
        }
        else
        {
            Indices[ind].first = n;
        }
    }
    return Indices;
}
