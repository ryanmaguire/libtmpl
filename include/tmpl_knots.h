
/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_KNOTS_H__
#define __TMPL_KNOTS_H__

#include <libtmpl/include/tmpl_integer.h>

typedef enum _tmpl_CrossingType {
  tmpl_UnderCrossing,
  tmpl_OverCrossing
} tmpl_CrossingType;

typedef enum _tmpl_CrossingSign {
    tmpl_NegativeCrossing = -1,
    tmpl_PositiveCrossing = 1
} tmpl_CrossingSign;

/*  A Gauss tuple is an order triple (n, t, s), where n is the crossing       *
 *  number (which is an unsigned integer), t is the type (over or under), and *
 *  s is the sign of the crossing (+/- 1).                                    */
typedef struct _tmpl_GaussTuple {

    /*  The crossing number of the crossing. Note, a virtual knot's crossings *
     *  need to first be labelled 0 to n-1, where n is the number of          *
     *  crossings.                                                            */
    tmpl_uint64 crossing_number;
  
    /*  The crossing type (over or under) of this crossing.                   */
    tmpl_CrossingType crossing_type;
  
    /*  And the crossing sign (positive or negative).                         */
    tmpl_CrossingSign crossing_sign;
} tmpl_GaussTuple;

/*  A virtual knot is just the Gauss code of the knot. This is a sequence of  *
 *  Gauss tuples.                                                             */
typedef struct _tmpl_VirtualKnot {
    /*  Use a single unsigned integer to represent the number of (virtual)    *
     *  crossings in the knot. 32-bit architectures may find it beneficial /  *
     *  efficient to use 32-bit integers instead of 64. A 64-bit integer is   *
     *  extreme overkill, as it is.                                           */
    tmpl_uint64 number_of_crossings;
  
    /*  A pointer to an array of Gauss tuples, representing the Gaus code of  *
     *  the virtual knot. This pointer has 2*number_of_crossings elements.    */
    tmpl_GaussTuple *gauss_code;
} tmpl_VirtualKnot;

#endif
/*  End of include guard.                                                     */

