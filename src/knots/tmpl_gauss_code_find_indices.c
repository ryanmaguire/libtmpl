#include <libtmpl/include/types/tmpl_crossing_type.h>
#include <libtmpl/include/types/tmpl_crossing_indices.h>
#include <libtmpl/include/types/tmpl_gauss_tuple.h>
#include <libtmpl/include/types/tmpl_gauss_code.h>

extern void
tmpl_GaussCode_Find_Crossing_Indices(tmpl_GaussCode * const code,
                                     tmpl_CrossingIndices * const indices);

void
tmpl_GaussCode_Find_Crossing_Indices(tmpl_GaussCode * const code,
                                     tmpl_CrossingIndices * const indices)
{
    unsigned long int n;

    if (!code)
        return;

    if (code->number_of_crossings == 0UL)
        return;

    if (!indices)
    {
        code->error_occurred = tmpl_False;
        code->error_message =
            "Error Encountered: libtmpl\n"
            "    tmpl_GaussCode_Find_Crossing_Indices\n\n"
            "Input tmpl_CrossingIndices is NULL.\n";

        return;
    }

    for (n = 0UL; n < code->length; ++n)
    {
        const tmpl_GaussTuple * const tuple = &(code->tuples[n]);
        const unsigned long int index = tuple->crossing_number;

        if (tuple->crossing_type == TMPL_OVER_CROSSING)
            indices[index].over = n;
        else
            indices[index].under = n;
    }
}
