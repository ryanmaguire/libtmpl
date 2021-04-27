#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>

unsigned long int
tmpl_Virtual_Knot_Genus(tmpl_VirtualKnot *K)
{
    unsigned char *have_visited;
    unsigned long int n, k, current_crossing, dir, genus;
    tmpl_GaussTuple *T;

    if (K == NULL)
        return 0;

    if (K->gauss_code == NULL)
        return 0UL;

    if (K->number_of_crossings == 0UL)
        return 0UL;

    have_visited = calloc(sizeof(*have_visited), 4UL * K->number_of_crossings);

    for (n = 0UL; n < K->number_of_crossings; ++n)
    {
        k = 4UL * n;
        T = &(K->gauss_code[n]);
        current_crossing = T->crossing_number;
        dir = 0UL;
        while (!have_visited[k])
        {
            T = &(K->gauss_code[current_crossing]);
            if (dir == 0UL)
            {
                if (current_crossing == K->number_of_crossings - 1UL)
                {
                    current_crossing = 0UL;
                }
                else
                {

                }
            }
        }
    }

    free(have_visited);
    return genus;
}

