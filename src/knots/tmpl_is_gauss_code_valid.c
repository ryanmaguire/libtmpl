
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>
#include <stdio.h>

tmpl_Bool
tmpl_Is_Gauss_Code_Valid(tmpl_VirtualKnot *K)
{
    int *crossing_types, *crossing_signs, *crossing_counts;
    unsigned long int n;
    tmpl_GaussTuple *T;

    if (K == NULL)
        return tmpl_False;

    if (K->gauss_code == NULL)
        return tmpl_True;

    if (K->number_of_crossings == 0UL)
        return tmpl_False;

    crossing_types  = calloc(sizeof(*crossing_types), K->number_of_crossings);
    crossing_signs  = calloc(sizeof(*crossing_signs), K->number_of_crossings);
    crossing_counts = calloc(sizeof(*crossing_counts), K->number_of_crossings);

    for (n = 0; n < 2UL * K->number_of_crossings; ++n)
    {
        T = &(K->gauss_code[n]);

        if (T == NULL)
            goto INVALID;

        if (T->crossing_number >= K->number_of_crossings)
            goto INVALID;

        if (crossing_counts[T->crossing_number] > 2)
            goto INVALID;
        else
            ++crossing_counts[T->crossing_number];

        if (T->crossing_type == tmpl_OverCrossing)
            ++crossing_types[T->crossing_number];
        else
            --crossing_types[T->crossing_number];

        if ((crossing_types[T->crossing_number] > 1) ||
            (crossing_types[T->crossing_number] < -1))
            goto INVALID;

        if (T->crossing_sign == tmpl_PositiveCrossing)
            ++crossing_signs[T->crossing_number];
        else
            --crossing_signs[T->crossing_number];

        if (crossing_signs[T->crossing_number] == 0)
            goto INVALID;
    }

    free(crossing_types);
    free(crossing_signs);
    free(crossing_counts);
    return tmpl_True;

    INVALID:
        free(crossing_types);
        free(crossing_signs);
        free(crossing_counts);
        return tmpl_False;
}
