
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_knots.h>

/*  The macro NULL is defined here.                                           */
#include <stdlib.h>

tmpl_Bool
tmpl_Are_Gauss_Tuples_Identical(tmpl_GaussTuple *T0, tmpl_GaussTuple *T1)
{
    /*  If both pointers are NULL, return True. If only one pointer is NULL   *
     *  return False. If neither is NULL, proceed and compare the pointers.   */
    if ((T0 == NULL) && (T1 == NULL))
        return tmpl_True;
    
    /*  If we get here, at least one pointer is not NULL. Check that neither  *
     *  are NULL before proceeding. Trying to access NULL pointers may result *
     *  in a segmentation fault, so this is important.                        */
    else if ((T0 == NULL) || (T1 == NULL))
        return tmpl_False;

    /*  Check the crossing number. For different Gauss Tuples, this is likely *
     *  the component that won't be equal, so it makes sense to check first.  */
    else if (T0->crossing_number != T1->crossing_number)
        return tmpl_False;

    /*  Next, check the crossing sign and crossing type.                      */
    else if (T0->crossing_sign != T1->crossing_sign)
        return tmpl_False;
    
    else if (T0->crossing_type != T1->crossing_type)
        return tmpl_False;

    /*  If all of these are equal, the tuples are identical. Return True.     */
    else
        return tmpl_True;
}
/*  End of tmpl_Are_Gauss_Tuples_Identical.                                   */

