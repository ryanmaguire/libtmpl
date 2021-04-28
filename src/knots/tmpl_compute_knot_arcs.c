

#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>

tmpl_KnotArcs *
tmpl_Compute_Knot_Arcs(tmpl_VirtualKnot *K)
{
    unsigned long int n, arc_ind, crossing_ind;
    tmpl_GaussTuple *T;
    tmpl_KnotArcs *A;
    tmpl_CrossingIndices *Indices;
    tmpl_KnotArcCrossingTuple *C;
    unsigned long int *arc_index, *start_index, *end_index;
    
    if (K == NULL)
        return NULL;
    
    if (K->gauss_code == NULL)
        return NULL;
    
    if (K->number_of_crossings == 0UL)
        return NULL;
    
    A = malloc(sizeof(*A));
    A->number_of_crossings = K->number_of_crossings;
    A->arcs = malloc(sizeof(*(A->arcs)) * A->number_of_crossings);

    A->arc_crossings
        = malloc(sizeof(*(A->arc_crossings)) * A->number_of_crossings);

    Indices = tmpl_Find_Crossing_Indices(K);
    arc_index = malloc(sizeof(*arc_index) * K->number_of_crossings);
    start_index = malloc(sizeof(*start_index) * K->number_of_crossings);
    end_index = malloc(sizeof(*end_index) * K->number_of_crossings);

    for (arc_ind = 0UL; arc_ind < K->number_of_crossings; ++arc_ind)
    {
        n = Indices[arc_ind].under;
        T = &(K->gauss_code[n]);
        (A->arcs[arc_ind]).start = T;
        start_index[T->crossing_number] = arc_ind;

        while (1)
        {
            if (n == 2UL * K->number_of_crossings - 1UL)
                n = 0UL;
            else
                ++n;

            T = &(K->gauss_code[n]);
            if (T->crossing_type == tmpl_UnderCrossing)
                break;
            else
                arc_index[T->crossing_number] = arc_ind;
        }

        (A->arcs[arc_ind]).end = T;
        end_index[T->crossing_number] = arc_ind;
    }

    for (n = 0UL; n < K->number_of_crossings; ++n)
    {
        arc_ind = arc_index[n];
        crossing_ind = Indices[n].under;
        T = &(K->gauss_code[crossing_ind]);
        C = &(A->arc_crossings[n]);
        
        C->arc_travelling_on = arc_ind;
        C->crossing_number = T->crossing_number;
        
        if (T->crossing_sign == tmpl_PositiveCrossing)
        {
            C->arc_on_left = start_index[T->crossing_number];
            C->arc_on_right = end_index[T->crossing_number];
        }
        else
        {
            C->arc_on_left = end_index[T->crossing_number];
            C->arc_on_right = start_index[T->crossing_number];
        }        
    }

    free(arc_index);
    free(start_index);
    free(end_index);
    tmpl_Destroy_Crossing_Indices(&Indices);
    return A;
}

