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
 *                         tmpl_gauss_code_are_equal                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks if two Gauss codes represent the same sequences.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
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
 *  Called Functions:                                                         *
 *      src/knots/                                                            *
 *          tmpl_GaussTuple_Are_Equal:                                        *
 *              Determines if two Gauss tuples are the same.                  *
 *  Method:                                                                   *
 *      If both pointers are NULL, return true. If only one is NULL, return   *
 *      false. Otherwise, check each tuple in the two Gauss codes, returning  *
 *      true if all of them are the same, and false otherwise.                *
 *  Notes:                                                                    *
 *      The input Gauss code is signed, not unsigned. That is, the signs of   *
 *      the crossings are included in the Gauss tuples.                       *
 *  References:                                                               *
 *      1.) Livingston, Charles and Moore, Allison                            *
 *          LinkInfo / KnotInfo                                               *
 *          https://linkinfo.knotinfo.org/descriptions/gauss_notation.html    *
 *                                                                            *
 *          KnotInfo page describing unsigned and signed Gauss codes.         *
 *                                                                            *
 *      2.) Bar-Natan, Dror                                                   *
 *          Knot Atlas                                                        *
 *          http://katlas.org/wiki/Gauss_Codes                                *
 *                                                                            *
 *          Knot atlas entry for Gauss codes.                                 *
 *                                                                            *
 *      3.) Maguire, Ryan                                                     *
 *          Khovanov Homology and Legendrian Simple Knots                     *
 *                                                                            *
 *          Ph.D. thesis, the conventions used in libtmpl are described in    *
 *          chapter 2, sections 1 and 2.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_gauss_tuple.h:                                                   *
 *          Header file providing the typedef for Gauss tuples.               *
 *  3.) tmpl_gauss_code.h:                                                    *
 *          Header file with the definition for Gauss code.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 15, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/10/07: Ryan Maguire                                                  *
 *      Changed name, added license and doc-string, general cleanup.          *
 ******************************************************************************/

/*  Booleans (true and false) provided here.                                  */
#include <libtmpl/include/tmpl_bool.h>

/*  Typedef for the Gauss tuple struct provided here.                         */
#include <libtmpl/include/types/tmpl_gauss_tuple.h>

/*  Gauss code data type defined here.                                        */
#include <libtmpl/include/types/tmpl_gauss_code.h>

/*  Function used for comparing two Gauss tuples, found in tmpl_knots.h.      */
extern tmpl_Bool
tmpl_GaussTuple_Are_Equal(const tmpl_GaussTuple * const first,
                          const tmpl_GaussTuple * const second);

/*  Forward declaration for the function, also found in tmpl_knots.h.         */
extern tmpl_Bool
tmpl_GaussCode_Are_Equal(const tmpl_GaussCode * const first,
                         const tmpl_GaussCode * const second);

/*  Function for comparing two Gauss codes for equality.                      */
tmpl_Bool
tmpl_GaussCode_Are_Equal(const tmpl_GaussCode * const first,
                         const tmpl_GaussCode * const second)
{
    /*  Variable for indexing over all of the Gauss tuples in the knots.      */
    unsigned long int ind;

    /*  Simple check first, if the pointers are pointing to the same data,    *
     *  then the Gauss codes are indeed identical. Return true.               */
    if (first == second)
        return tmpl_True;

    /*  Avoid dereferencing NULL pointers, first check that we have valid     *
     *  data to work with.                                                    */
    if (!first)
    {
        /*  The first tuple is simply NULL. If the second input is NULL, then *
         *  we'll treat these as equal Gauss codes. They are both NULL code.  */
        if (!second)
            return tmpl_True;

        /*  Otherwise the first sequence is NULL but the second one isn't.    *
         *  Treat these as different tuples, return false.                    */
        return tmpl_False;
    }

    /*  If we get here, then the first tuple is not a NULL pointer, but it is *
     *  possible that the second one is. Check before dereferencing. Since    *
     *  the first tuple is not NULL, if the second one is NULL then these are *
     *  not identical. Return false.                                          */
    if (!second)
        return tmpl_False;

    /*  It either Gauss code contains an error, return false. It is possible  *
     *  that one of the sequences contains corrupted data and should not be   *
     *  dereferenced. The user should handle the error before calling this.   */
    if (first->error_occurred || second->error_occurred)
        return tmpl_False;

    /*  If the pointers have different crossing numbers, then we know the     *
     *  knots have different Gauss codes. This does not tell us the knots are *
     *  not isomorphic to each other. It is possible two knots with different *
     *  Gauss codes, and a different number of crossings, are the same with   *
     *  the application of the right sequence of (virtual) Reidemeister moves.*/
    if (first->number_of_crossings != second->number_of_crossings)
        return tmpl_False;

    /*  Lastly, before performing the actual comparison, check to make sure   *
     *  the data for the Gauss tuples have been initialized.                  */
    if (!first->gauss_code)
    {
        /*  If we get here, then the data for the first Gauss code is NULL.   *
         *  Like the previous check, if the data for the second Gauss code is *
         *  also NULL, then we will treat these as equal. A NULL pointer for  *
         *  the Gauss tuples is valid, it represents a knot with no crossings.*
         *  This is the unknot, which is the simplest knot.                   */
        if (!second->gauss_code)
            return tmpl_True;

        /*  Otherwise the first code is empty but the second one is not.      *
         *  The Gauss codes are not identical, return false.                  */
        return tmpl_False;
    }

    /*  Loop through the Gauss tuples and see if they're all equal.           */
    for (ind = 0; ind < first->number_of_crossings; ++ind)
    {
        /*  The function tmpl_GaussTuple_Are_Equal wants pointers to Gauss    *
         *  tuples. The value first->gauss_code[ind] is the nth Gauss tuple   *
         *  for the knot, but is an actual Gauss tuple struct, not a pointer. *
         *  Get the address with an ampersand &.                              */
        const tmpl_GaussTuple * const first_tuple = &(first->gauss_code[ind]);

        /*  Do the same thing for the second Gauss code.                      */
        const tmpl_GaussTuple * const second_tuple = &(second->gauss_code[ind]);

        /*  If the two Gauss tuples are different, the Gauss codes are        *
         *  different so return false. Otherwise, proceed.                    */
        if (!tmpl_GaussTuple_Are_Equal(first_tuple, second_tuple))
            return tmpl_False;
    }

    /*  If we get here, all tuples in the two codes are equal. Return true.   */
    return tmpl_True;
}
/*  End of tmpl_GaussCode_Are_Equal.                                          */
