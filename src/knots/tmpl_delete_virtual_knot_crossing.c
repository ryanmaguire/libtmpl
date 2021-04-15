

#include <libtmpl/include/tmpl_knots.h>
#include <libtmpl/include/tmpl_integer.h>

/*  Needed for the NULL macro.                                                */
#include <stdlib.h>

void
tmpl_Delete_Virtual_Knot_Crossing(tmpl_VirtualKnot *K, tmpl_uint64 crossing)
{
    tmpl_uint64 ind;
    tmpl_uint64 pos0, pos1;
    tmpl_Bool found_pos0;
    tmpl_uint64 gauss_code_length;

    /*  First things first, before trying to access elements of the pointer   *
     *  K, make sure that it is not NULL.                                     */
    if (K == NULL)
        return;

    /*  If you are trying to delete a crossing that doesn't exist, so that    *
     *  crossing is greater than K->crossing_number, abort the computation.   *
     *  Note that the crossings are index 0 to N-1, where N is the number of  *
     *  crossings. So crossing should be strictly less than N.                */
    if (K->number_of_crossings <= crossing)
        return;

    /*  If the knot has a single virtual crossing, deleting it results in the *
     *  unknot. We can simply delete the Gauss tuple.                         */
    if (K->number_of_crossings == 1)
    {
        tmpl_Destroy_Gauss_Tuple_Pointer(&(K->gauss_code));
        K->number_of_crossings = 0;
    }
    else
    {
        gauss_code_length = 2*K->number_of_crossings;
        found_pos0 = tmpl_False;

        for (ind = 0; ind < gauss_code_length; ++ind)
        {
            if ((K->gauss_code[ind]).crossing_number == crossing)
            {
                if (found_pos0)
                    pos1 = ind;
                else
                {
                    pos0 = ind;
                    found_pos0 = tmpl_True;
                }
            }
            else if ((K->gauss_code[ind]).crossing_number > crossing)
                --(K->gauss_code[ind]).crossing_number;
        }

        for (ind = pos0; ind < pos1-1; ++ind)
            K->gauss_code[ind] = K->gauss_code[ind+1];

        for (ind = pos1; ind < gauss_code_length-1; ++ind)
            K->gauss_code[ind-1] = K->gauss_code[ind+1];

        gauss_code_length -= 2;
        K->gauss_code = realloc(K->gauss_code,
                                sizeof(*K->gauss_code)*gauss_code_length);
        
        --K->number_of_crossings;
    }
}

