
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_knots.h>

/*  The macro NULL is defined here.                                           */
#include <stdlib.h>

tmpl_Bool
tmpl_Are_Virtual_Knots_Identical(tmpl_VirtualKnot *K0, tmpl_VirtualKnot *K1)
{
    /*  Variable for indexing over all of the Gauss tuples in the knots.      */
    tmpl_uint64 ind;
    
    /*  Variables for storing pointers to Gauss tuples.                       */
    tmpl_GaussTuple *T0, *T1;
    
    /*  If both pointers are NULL, return True. If only one pointer is NULL   *
     *  return False. If neither is NULL, proceed and compare the pointers.   */
    if ((K0 == NULL) && (K1 == NULL))
        return tmpl_True;
    
    /*  If we get here, at least one pointer is not NULL. Check that neither  *
     *  are NULL before proceeding. Trying to access NULL pointers may result *
     *  in a segmentation fault, so this is important.                        */
    else if ((K0 == NULL) || (K1 == NULL))
        return tmpl_False;

    /*  If the pointers have different crossing numbers, then we know the     *
     *  knots have different Gauss codes. This does NOT tell us the knots are *
     *  not isometric to one another. It is possible two knots with different *
     *  Gauss codes, and a different number of crossings, are the same with   *
     *  the application of the right (virtual) Reidemeister moves.            */
    if (K0->number_of_crossings != K1->number_of_crossings)
        return tmpl_False;

    /*  Loop through the Gauss tuples and see if they're all equal.           */
    for (ind = 0; ind < K0->number_of_crossings; ++ind)    
    {
        /*  The function tmpl_Are_Gauss_Tuples_Equal wants pointers to Gauss  *
         *  tuples. The value K0->gauss_code[n] is the nth Gauss tuple for    *
         *  the knot, but is a an actual Gauss tuple struct, not a pointer.   *
         *  Get the address with an ampersand &.                              */
        T0 = &(K0->gauss_code[ind]);
        
        /*  Do the same thing for T1, and we can use the pointers to compare. */
        T1 = &(K1->gauss_code[ind]);
        
        /*  If the two Gauss tuples are different, the Gauss codes are        *
         *  different so return false. Otherwise, proceed.                    */
        if (!tmpl_Are_Gauss_Tuples_Identical(T0, T1))
            return tmpl_False;
    }
    
    /*  If we get here, all values of the two knots are equal so return true. */
    return tmpl_True;
}
/*  End of tmpl_Are_Virtual_Knots_Equal.                                      */

