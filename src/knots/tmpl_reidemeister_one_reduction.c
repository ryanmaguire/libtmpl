
#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>

void
tmpl_Reidemeister_One_Reduction(tmpl_VirtualKnot *K)
{
    unsigned long int n;
    tmpl_GaussTuple *S, *T;

    if (K == NULL)
        return;

    if (K->number_of_crossings == 0)
        return;

    n = 0UL;
    while (n < 2*K->number_of_crossings - 1)
    {
        T = &(K->gauss_code[n]);
        S = &(K->gauss_code[n+1]);
        if (S->crossing_number == T->crossing_number)
        {
            tmpl_Delete_Virtual_Knot_Crossing(K, S->crossing_number);
            if (n != 0)
                --n;
        }
        else
            ++n;
    }

    T = &(K->gauss_code[0]);
    S = &(K->gauss_code[2*K->number_of_crossings - 1]);
    if (S->crossing_number == T->crossing_number)
        tmpl_Delete_Virtual_Knot_Crossing(K, S->crossing_number);
}

