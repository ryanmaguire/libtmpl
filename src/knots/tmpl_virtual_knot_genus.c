#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>

typedef enum __path_dir {
    reverse = 0,
    forward = 1
} path_dir;

static void __tmpl_go_left(unsigned long int k,
                           unsigned long int *genus,
                           unsigned long int index,
                           path_dir dir,
                           unsigned char *have_visited,
                           tmpl_CrossingIndices *Indices,
                           tmpl_VirtualKnot *K)
{
    tmpl_GaussTuple *T;
    while (!have_visited[k])
    {
        have_visited[k] = 1U;

        if (dir == forward)
        {
            if (index == 2UL * K->number_of_crossings - 1UL)
                index = 0UL;
            else
                ++index;
        }
        else
        {
            if (index == 0UL)
                index = 2UL * K->number_of_crossings - 1UL;
            else
                --index;
        }

        T = &(K->gauss_code[index]);

        if (T->crossing_sign == tmpl_PositiveCrossing)
        {
            if (T->crossing_type == tmpl_OverCrossing)
                index = Indices[T->crossing_number].under;
            else
            {
                index = Indices[T->crossing_number].over;
                dir =  1 - dir;
            }
        }
        else
        {
            if (T->crossing_type == tmpl_OverCrossing)
                index = Indices[T->crossing_number].under;
            else
            {
                index = Indices[T->crossing_number].over;
                dir =  1 - dir;
            }
        }
        T = &(K->gauss_code[index]);
        k = 4UL * T->crossing_number;

        if (dir == reverse)
            k += 2UL;

        if (T->crossing_type == tmpl_UnderCrossing)
            k += 1UL;

        if (have_visited[k])
            *genus += 1UL;
    }
    return;
}

unsigned long int
tmpl_Virtual_Knot_Genus(tmpl_VirtualKnot *K)
{
    unsigned char *have_visited;
    unsigned long int n, k, genus, index, faces;
    tmpl_CrossingIndices *Indices;

    path_dir dir;

    if (K == NULL)
        return 0;

    if (K->gauss_code == NULL)
        return 0UL;

    if (K->number_of_crossings == 0UL)
        return 0UL;

    have_visited = calloc(sizeof(*have_visited), 4UL * K->number_of_crossings);
    Indices = tmpl_Find_Crossing_Indices(K);
    faces = 0UL;

    for (n = 0UL; n < K->number_of_crossings; ++n)
    {
        k = 4UL * n;
        dir = forward;
        index = Indices[n].over;
        __tmpl_go_left(k, &faces, index, dir, have_visited, Indices, K);

        k = 4UL * n + 1UL;
        dir = forward;
        index = Indices[n].under;
        __tmpl_go_left(k, &faces, index, dir, have_visited, Indices, K);

        k = 4UL * n + 2UL;
        dir = reverse;
        index = Indices[n].over;
        __tmpl_go_left(k, &faces, index, dir, have_visited, Indices, K);

        k = 4UL * n + 3UL;
        dir = reverse;
        index = Indices[n].under;
        __tmpl_go_left(k, &faces, index, dir, have_visited, Indices, K);
    }

    free(have_visited);
    tmpl_Destroy_Crossing_Indices(&Indices);

    faces = faces - 2UL;
    genus = (K->number_of_crossings - faces) / 2UL;
    return genus;
}

