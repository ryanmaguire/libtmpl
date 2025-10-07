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
 *                        tmpl_gauss_tuples_are_equal                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks if two Gauss tuples represent the same ordered triple.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_GaussTuples_Are_Equal                                            *
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
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If both pointers are NULL, return true. If only one is NULL, return   *
 *      false. Otherwise, check the entries of the tuple and return true if   *
 *      and only if all three (crossing number, crossing type, and crossing   *
 *      sign) are equal.                                                      *
 *  Notes:                                                                    *
 *      These Gauss tuples include the crossing sign, meaning we are          *
 *      implicitly working with signed / extended Gauss code.                 *
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
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 15, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/01/15: Ryan Maguire                                                  *
 *      Update formatting and comments.                                       *
 *  2025/10/07: Ryan Maguire                                                  *
 *      Changed name, added license and doc-string, general cleanup.          *
 ******************************************************************************/

/*  Booleans (true and false) provided here.                                  */
#include <libtmpl/include/tmpl_bool.h>

/*  Typedef for the Gauss tuple struct provided here.                         */
#include <libtmpl/include/types/tmpl_gauss_tuple.h>

/*  Forward declaration for the function, also found in tmpl_knots.h.         */
extern tmpl_Bool
tmpl_GaussTuples_Are_Equal(const tmpl_GaussTuple * const first,
                           const tmpl_GaussTuple * const second);

/*  Function for comparing two Gauss tuples for equality.                     */
tmpl_Bool
tmpl_GaussTuples_Are_Equal(const tmpl_GaussTuple * const first,
                           const tmpl_GaussTuple * const second)
{
    /*  Simple check first, if the pointers are pointing to the same data,    *
     *  then the Gauss tuples are indeed identical. Return true.              */
    if (first == second)
        return tmpl_True;

    /*  Avoid dereferencing NULL pointers, first check that we have valid     *
     *  data to work with.                                                    */
    if (!first)
    {
        /*  The first tuple is simply NULL. If the second input is NULL, then *
         *  we'll treat these as equal tuples. They are both the NULL tuple.  */
        if (!second)
            return tmpl_True;

        /*  Otherwise the first tuple is NULL but the second one isn't. Treat *
         *  these as different tuples, return false.                          */
        return tmpl_False;
    }

    /*  If we get here, then the first tuple is not a NULL pointer, but it is *
     *  possible that the second one is. Check before dereferencing. Since    *
     *  the first tuple is not NULL, if the second one is NULL then these are *
     *  not identical. Return false.                                          */
    if (!second)
        return tmpl_False;

    /*  We now have two Gauss tuples to work with. A Gauss tuples is an       *
     *  ordered triple of the form (n, s, t) where n is the crossing number,  *
     *  which is the integer used to label the given crossing in the knot     *
     *  diagram, t is the type, meaning over or under, and s is the sign,     *
     *  which is positive or negative. This assumes we are working with       *
     *  oriented knot diagrams (either virtual or classical). Two Gauss       *
     *  tuples are equal if and only if all three of these components are the *
     *  same. First, check the crossing number.                               */
    if (first->crossing_number != second->crossing_number)
        return tmpl_False;

    /*  Next, check the crossing type. This may be over or under.             */
    if (first->crossing_type != second->crossing_type)
        return tmpl_False;

    /*  Lastly, the crossing sign. Note, since we are checking the sign we    *
     *  are implicitly working with signed Gauss codes, also called extended  *
     *  Gauss codes. Unsigned Gauss codes do not keep track of signs, but     *
     *  they are also unable to distinguish a knot from its mirror.           */
    if (first->crossing_sign != second->crossing_sign)
        return tmpl_False;

    /*  The crossing number, sign, and type are all the same. The tuples are  *
     *  identical, return true.                                               */
    return tmpl_True;
}
/*  End of tmpl_GaussTuples_Are_Equal.                                        */
