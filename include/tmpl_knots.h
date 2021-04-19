/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                                tmpl_knots                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the prototypes and typedef's for a host of tools useful for  *
 *      knot theorists. This includes knot invariants like the Jones'         *
 *      polynomial. A (virtual) knot is represented via extended Gauss code.  *
 *      This can be combined with the graph theory sublibrary for a plethora  *
 *      of other computations.                                                *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file provided tmpl_Bool, tmpl_False, and tmpl_True.        *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       April 13, 2021                                                *
 ******************************************************************************
 *                          Revision History                                  *
 ******************************************************************************
 *  2021/04/13: Ryan Maguire                                                  *
 *      Created file.                                                         *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_KNOTS_H__
#define __TMPL_KNOTS_H__

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  We'll store a knot in a computer via it's Gauss code. This is a sequence  *
 *  of ordered triples of the form (n, t, s) where n is an unsigned integer   *
 *  and t and s represent the crossing number and sign, respectively. We'll   *
 *  typedef enum data types for crossing types and crossing signs.            */
typedef enum _tmpl_CrossingType {
  tmpl_UnderCrossing,
  tmpl_OverCrossing
} tmpl_CrossingType;

typedef enum _tmpl_CrossingSign {
    tmpl_NegativeCrossing = -1,
    tmpl_PositiveCrossing = 1
} tmpl_CrossingSign;

/*  A Gauss tuple will be an ordered triple (n, t, s), with n an unsigned     *
 *  integer, and t and s being tmpl_CrossingType and tmpl_CrossingSign        *
 *  variables. We'll typedef this into a struct.                              */
typedef struct _tmpl_GaussTuple {

    /*  The crossing number of the crossing. Note, a virtual knot's crossings *
     *  need to first be labelled 0 to n-1, where n is the number of          *
     *  crossings.                                                            */
    unsigned long int crossing_number;

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
    unsigned long int number_of_crossings;

    /*  A pointer to an array of Gauss tuples, representing the Gauss code of *
     *  the virtual knot. This pointer has 2*number_of_crossings elements.    */
    tmpl_GaussTuple *gauss_code;

  /*  A Boolean indicating if something went wrong in a computation. This     *
   *  should always be checked before trying to perform a computation.        */
  tmpl_Bool error_occured;

  /*  A string containing an error message that can be set if something goes  *
   *  wrong. This is set to NULL by default, meaning no error has occured.    */
  char *error_message;
} tmpl_VirtualKnot;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Are_Gauss_Tuples_Identical                                       *
 *  Purpose:                                                                  *
 *      Compares two Gauss tuples and determines if they are the same.        *
 *  Arguments:                                                                *
 *      tmpl_GaussTuple *T0:                                                  *
 *          A pointer to the zeroth Gauss tuple.                              *
 *      tmpl_GaussTuple *T1:                                                  *
 *          A pointer to the first Gauss tuple.                               *
 *  Output:                                                                   *
 *      tmpl_Bool endianness:                                                 *
 *          A Boolean which determines whether or not the tuples are equal.   *
 ******************************************************************************/
extern tmpl_Bool
tmpl_Are_Gauss_Tuples_Identical(tmpl_GaussTuple *T0, tmpl_GaussTuple *T1);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Are_Virtual_Knots_Identical                                      *
 *  Purpose:                                                                  *
 *      Compares the Gauss code of two knots to check if they're the same.    *
 *  Arguments:                                                                *
 *      tmpl_VirtualKnot *K0:                                                 *
 *          A pointer to the zeroth virtual knot.                             *
 *      tmpl_VirtualKnot *K1:                                                 *
 *          A pointer to the first virtual knot.                              *
 *  Output:                                                                   *
 *      tmpl_Bool endianness:                                                 *
 *          A Boolean which determines whether or not the two knots are equal.*
 ******************************************************************************/
extern tmpl_Bool
tmpl_Are_Virtual_Knots_Identical(tmpl_VirtualKnot *K0, tmpl_VirtualKnot *K1);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Delete_Virtual_Knot_Crossing                                     *
 *  Purpose:                                                                  *
 *      Deletes a crossing in a virtual knot and shifts the crossing numbers  *
 *      of all of the crossings accordingly.                                  *
 *  NOTES:                                                                    *
 *      If the crossing that is to be deleted is greater than the number of   *
 *      crossings, nothing is done. If there is only one crossing in the knot *
 *      and you are trying to delete this, the Gauss tuple pointer is set to  *
 *      NULL, representing the unknot.                                        *
 *  Arguments:                                                                *
 *      tmpl_VirtualKnot *K:                                                  *
 *          A pointer to a virtual knot.                                      *
 *      tmpl_uint64 crossing:                                                 *
 *          The crossing that is to be deleted.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Delete_Virtual_Knot_Crossing(tmpl_VirtualKnot *K,
                                  unsigned long int crossing);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Destroy_Gauss_Tuple_Pointer                                      *
 *  Purpose:                                                                  *
 *      Free's the memory allocated to a pointer to a Gauss tuple.            *
 *  NOTES:                                                                    *
 *      This takes a pointer to a pointer to a Gauss tuple. This is so we can *
 *      second the Gauss tuple pointer to NULL so we don't accidentally try   *
 *      to free it twice.                                                     *
 *  Arguments:                                                                *
 *      tmpl_VirtualKnot *K0:                                                 *
 *          A pointer to the zeroth virtual knot.                             *
 *      tmpl_VirtualKnot *K1:                                                 *
 *          A pointer to the first virtual knot.                              *
 *  Output:                                                                   *
 *      tmpl_Bool endianness:                                                 *
 *          A Boolean which determines whether or not the two knots are equal.*
 ******************************************************************************/
extern void tmpl_Destroy_Gauss_Tuple_Pointer(tmpl_GaussTuple **T_ptr);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Destroy_Virtual_Knot_Pointer                                     *
 *  Purpose:                                                                  *
 *      Free's the memory allocated to a pointer to a virtual knot.           *
 *  NOTES:                                                                    *
 *      This takes a pointer to a pointer to a virtual knot. This is so we    *
 *      can set the virtual knot pointer to NULL so we don't accidentally try *
 *      to free it twice.                                                     *
 *  Arguments:                                                                *
 *      tmpl_VirtualKnot **K:                                                 *
 *          A pointer to a pointer to a virtual knot.                         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Destroy_Virtual_Knot_Pointer(tmpl_VirtualKnot **K_ptr);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Gauss_Code_From_String                                           *
 *  Purpose:                                                                  *
 *      Creates a pointer to a virtual knot from a string, the Gauss code.    *
 *  NOTES:                                                                    *
 *      The string must be of the form "tnstnstns...tns" where t is the type, *
 *      either over ("O" or "o") or under ("U" or "u"), n is an unsigned      *
 *      integer (the crossing number), and s is the sign, either positive     *
 *      ("+") or negative ("-").                                              *
 *  Arguments:                                                                *
 *      char *str:                                                            *
 *          The string representing the Gauss code of the knot.               *
 *  Output:                                                                   *
 *      tmpl_VirtualKnot *K:                                                  *
 *          A pointer to a virtual knot struct given by the Gauss code of str.*
 ******************************************************************************/
extern tmpl_VirtualKnot *tmpl_Gauss_Code_From_String(char *str);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Print_Gauss_Code                                                 *
 *  Purpose:                                                                  *
 *      Prints the Gauss code of a knot.                                      *
 *  NOTES:                                                                    *
 *      If the input knot has the Gauss code pointer set to NULL, this        *
 *      function prints out "Unknot."                                         *
 *  Arguments:                                                                *
 *      tmpl_VirtualKnot *K0:                                                 *
 *          A pointer to the zeroth virtual knot.                             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Print_Gauss_Code(tmpl_VirtualKnot *K);

#endif
/*  End of include guard.                                                     */

