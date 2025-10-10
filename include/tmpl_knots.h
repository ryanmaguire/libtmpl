/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 13, 2021                                                *
 ******************************************************************************
 *                          Revision History                                  *
 ******************************************************************************
 *  2021/04/13: Ryan Maguire                                                  *
 *      Created file.                                                         *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_KNOTS_H
#define TMPL_KNOTS_H

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

#include <libtmpl/include/tmpl_polynomial.h>

#include <libtmpl/include/types/tmpl_crossing_sign.h>
#include <libtmpl/include/types/tmpl_crossing_type.h>
#include <libtmpl/include/types/tmpl_crossing_indices.h>
#include <libtmpl/include/types/tmpl_gauss_tuple.h>
#include <libtmpl/include/types/tmpl_gauss_code.h>




typedef struct tmpl_KnotCrossingArcTuple_Def {
    unsigned long int arc_travelling_on;
    unsigned long int arc_on_left;
    unsigned long int arc_on_right;
    unsigned long int crossing_number;
} tmpl_KnotArcCrossingTuple;

typedef struct tmpl_KnotArcTuple_Def {
    tmpl_GaussTuple *start;
    tmpl_GaussTuple *end;
} tmpl_KnotArcTuple;

typedef struct tmpl_KnotArcs_Def {
    tmpl_KnotArcCrossingTuple *arc_crossings;
    tmpl_KnotArcTuple *arcs;
    unsigned long int number_of_crossings;
} tmpl_KnotArcs;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_GaussCode_Are_Equal                                              *
 *  Purpose:                                                                  *
 *      Determines if two Gauss codes represent the same sequence.            *
 *  Arguments:                                                                *
 *      first (const tmpl_GaussCode * const):                                 *
 *          A Gauss code.                                                     *
 *      second (const tmpl_GaussCode * const):                                *
 *          A Gauss code, the one being compared to the first for equality.   *
 *  Output:                                                                   *
 *      are_equal (tmpl_Bool):                                                *
 *          Boolean indicating if the first and second codes are equal.       *
 ******************************************************************************/
extern tmpl_Bool
tmpl_GaussCode_Are_Equal(const tmpl_GaussCode * const first,
                         const tmpl_GaussCode * const second);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_GaussCode_Init                                                   *
 *  Purpose:                                                                  *
 *      Initializes a Gauss code to the empty sequence, which is the unknot.  *
 *  Arguments:                                                                *
 *      first (const tmpl_GaussCode * const):                                 *
 *          A Gauss code.                                                     *
 *      second (const tmpl_GaussCode * const):                                *
 *          A Gauss code, the one being compared to the first for equality.   *
 *  Output:                                                                   *
 *      are_equal (tmpl_Bool):                                                *
 *          Boolean indicating if the first and second codes are equal.       *
 ******************************************************************************/
extern tmpl_Bool
tmpl_GaussCode_Init(const tmpl_GaussCode * const code);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_GaussTuple_Are_Equal                                             *
 *  Purpose:                                                                  *
 *      Determines if two Gauss tuples represent the same ordered triples.    *
 *  Arguments:                                                                *
 *      first (const tmpl_GaussTuple * const first):                          *
 *          A Gauss tuple.                                                    *
 *      second (const tmpl_GaussTuple * const first):                         *
 *          A Gauss tuple, the one being compared to the first for equality.  *
 *  Output:                                                                   *
 *      are_equal (tmpl_Bool):                                                *
 *          Boolean indicating if the first and second tuples are equal.      *
 ******************************************************************************/
extern tmpl_Bool
tmpl_GaussTuple_Are_Equal(const tmpl_GaussTuple * const first,
                          const tmpl_GaussTuple * const second);

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
 *      tmpl_GaussCode *K:                                                    *
 *          A pointer to a virtual knot.                                      *
 *      tmpl_uint64 crossing:                                                 *
 *          The crossing that is to be deleted.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Delete_Virtual_Knot_Crossing(tmpl_GaussCode *K,
                                  unsigned long int crossing);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CrossingIndices_Destroy                                          *
 *  Purpose:                                                                  *
 *      Free's the memory allocated to a Gauss tuple.                         *
 *  Arguments:                                                                *
 *      tuple_ptr (tmpl_CrossingIndices ** const):                            *
 *          A pointer to the (pointer to the) Gauss tuple that is to be freed.*
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_CrossingIndices_Destroy(tmpl_CrossingIndices ** const ind_ptr);

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
 *      tmpl_GaussCode **K:                                                   *
 *          A pointer to a pointer to a virtual knot.                         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Destroy_Virtual_Knot_Pointer(tmpl_GaussCode **K_ptr);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_GaussCode_From_String                                           *
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
 *      tmpl_GaussCode *K:                                                    *
 *          A pointer to a virtual knot struct given by the Gauss code of str.*
 ******************************************************************************/
extern void
tmpl_GaussCode_From_String(const char * const str, tmpl_GaussCode * const code);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Print_Gauss_Code                                                 *
 *  Purpose:                                                                  *
 *      Prints the Gauss code of a knot.                                      *
 *  NOTES:                                                                    *
 *      If the input knot has the Gauss code pointer set to NULL, this        *
 *      function prints out "Unknot."                                         *
 *  Arguments:                                                                *
 *      tmpl_GaussCode *K0:                                                   *
 *          A pointer to the zeroth virtual knot.                             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Print_Gauss_Code(tmpl_GaussCode *K);

extern tmpl_Bool
tmpl_Is_Gauss_Code_Valid(tmpl_GaussCode *K);

extern tmpl_CrossingIndices *
tmpl_Find_Crossing_Indices(tmpl_GaussCode *K);

extern void
tmpl_Reidemeister_One_Reduction(tmpl_GaussCode *K);

unsigned long int
tmpl_Virtual_Knot_Genus(tmpl_GaussCode *K);

extern tmpl_PolynomialZ *
tmpl_Alexander_Polynomial(tmpl_GaussCode *K);

extern tmpl_KnotArcs *
tmpl_Compute_Knot_Arcs(tmpl_GaussCode *K);

extern void
tmpl_Destroy_Crossing_Indices(tmpl_CrossingIndices **Indices);

#endif
/*  End of include guard.                                                     */
