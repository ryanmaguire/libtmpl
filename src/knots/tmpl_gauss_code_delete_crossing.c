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
 *                      tmpl_gauss_code_delete_crossing                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Deletes a crossing from a Gauss code and resets the remaining entries.*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_GaussCode_Delete_Crossing                                        *
 *  Purpose:                                                                  *
 *      Deletes a crossing (both under and over) from a Gauss code.           *
 *  Arguments:                                                                *
 *      code (tmpl_GaussCode * const):                                        *
 *          The Gauss code we are working with.                               *
 *      crossing (unsigned long int):                                         *
 *          The index for the crossing we are deleting.                       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          free:                                                             *
 *              Free's dynamically allocated memory.                          *
 *          realloc:                                                          *
 *              Resizes a dynamically allocated array.                        *
 *  Method:                                                                   *
 *      Find the location of the under and over crossing for the crossing we  *
 *      are deleting. For entries between these entries, shift them back by   *
 *      one, and for entries after both shift back by two. Entries before     *
 *      both are left alone. Once done, resize the tuples array with realloc. *
 *  Notes:                                                                    *
 *      1.) Deleting a crossing from a one crossing knot produces the unknot. *
 *          The tuples array is set to NULL in this case.                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_cast.h:                                                          *
 *          Header providing TMPL_CAST with C vs. C++ compatibility.          *
 *  2.) tmpl_free.h:                                                          *
 *          Header providing TMPL_FREE with C vs. C++ compatibility.          *
 *  3.) tmpl_realloc.h:                                                       *
 *          Header providing TMPL_REALLOC with C vs. C++ compatibility.       *
 *  4.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  5.) tmpl_gauss_tuple.h:                                                   *
 *          Header file providing the typedef for Gauss tuples.               *
 *  6.) tmpl_gauss_code.h:                                                    *
 *          Header file with the definition for Gauss code.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 15, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/10/14: Ryan Maguire                                                  *
 *      Added docstring and replaced free with TMPL_FREE. Renamed function to *
 *      be consistent with other routines. Replaced realloc with TMPL_REALLOC.*
 ******************************************************************************/

/*  TMPL_CAST macro found here, providing C vs. C++ compatibility.            */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Location of the TMPL_FREE macro.                                          */
#include <libtmpl/include/compat/tmpl_free.h>

/*  TMPL_REALLOC found here. Provides C vs. C++ compatibility.                */
#include <libtmpl/include/compat/tmpl_realloc.h>

/*  Booleans (true and false) provided here.                                  */
#include <libtmpl/include/tmpl_bool.h>

/*  Typedef for the Gauss tuple struct provided here.                         */
#include <libtmpl/include/types/tmpl_gauss_tuple.h>

/*  Gauss code data type defined here.                                        */
#include <libtmpl/include/types/tmpl_gauss_code.h>

/*  Forward declaration / function prototype, found in tmpl_knots.h as well.  */
extern void
tmpl_GaussCode_Delete_Crossing(tmpl_GaussCode * const code,
                               unsigned long int crossing);

/*  Function for deleting a crossing from a Gauss code.                       */
void
tmpl_GaussCode_Delete_Crossing(tmpl_GaussCode * const code,
                               unsigned long int crossing)
{
    /*  Temporary pointer used with realloc.                                  */
    void *tmp;

    /*  Variable for keeping track of the index in the Gauss code.            */
    unsigned long int ind;

    /*  Variables for the location of the first and second occurrences of the *
     *  crossing in the Gauss code.                                           */
    unsigned long int pos0, pos1;

    /*  Booleans for tracking which positions have been found.                */
    tmpl_Bool found_pos0 = tmpl_False;
    tmpl_Bool found_pos1 = tmpl_False;

    /*  Avoid dereferencing a NULL pointer, make sure the input is valid.     */
    if (!code)
        return;

    /*  Do not attempt to modify a Gauss code that contains an error. Abort.  */
    if (code->error_occurred)
        return;

    /*  If you are trying to delete a crossing that doesn't exist, so that    *
     *  crossing is greater than the number of crossing, exit the function.   *
     *  Note that the crossings are index 0 to N-1, where N is the number of  *
     *  crossings. so crossing should be strictly less than N.                */
    if (code->number_of_crossings <= crossing)
        return;

    /*  If the knot has a single crossing, deleting it results in the unknot. *
     *  We can simply delete the Gauss tuple and set it to NULL.              */
    if (code->number_of_crossings == 1UL)
    {
        /*  The TMPL_FREE macro will safely free the data and set it to NULL  *
         *  to avoid double free's. Use this.                                 */
        TMPL_FREE(code->tuples);

        /*  We now have the unknot. There are zero crossings, and the Gauss   *
         *  code is empty, meaning the length is zero.                        */
        code->number_of_crossings = 0UL;
        code->length = 0UL;
        return;
    }

    /*  Loop through and find where this crossing occurs in the code.         */
    for (ind = 0; ind < code->length; ++ind)
    {
        /*  Check if we've found the crossing we want to delete.              */
        if (code->tuples[ind].crossing_number == crossing)
        {
            /*  If both instances have been found, this Gauss code has more   *
             *  than two entries with the same crossing index. This is an     *
             *  invalid Gauss code, treat this as an error.                   */
            if (found_pos1)
            {
                code->error_occurred = tmpl_True;
                code->error_message =
                    "Error Encountered: libtmpl\n"
                    "    tmpl_GaussCode_Delete_Crossing\n\n"
                    "There are more than three entries in the Gauss code\n"
                    "with this crossing index. The Gauss code is invalid.\n";

                return;
            }

            /*  If the input Gauss code is valid, there should be exactly two *
             *  instances of this crossing number in the code. We set the     *
             *  position variables accordingly. Check if we found the first   *
             *  occurrence of this crossing number.                           */
            if (found_pos0)
            {
                pos1 = ind;
                found_pos1 = tmpl_True;
            }

            /*  We initialized the found_pos0 Boolean to false, meaning if it *
             *  is still false, then we have found the first instance of this *
             *  crossing in the Gauss code. Set the position index and flip   *
             *  the Boolean to true so that we may search for the second      *
             *  occurrence.                                                   */
            else
            {
                pos0 = ind;
                found_pos0 = tmpl_True;
            }
        }

        /*  For entries that are after the deleted crossing we need to adjust *
         *  the crossing number (since the deleted crossing is now gone).     *
         *  We are deleting one crossing, so we simply need to decrement the  *
         *  crossing number for these entries.                                */
        else if (code->tuples[ind].crossing_number > crossing)
            --code->tuples[ind].crossing_number;
    }

    /*  If the found_pos0 Boolean is still false, then we never found a       *
     *  crossing in the Gauss code with this number as its label. But we have *
     *  also checked that crossing < code->number_of_crossings, meaning there *
     *  should be a crossing with this label. Hence we have an invalid Gauss  *
     *  code. Treat this as an error.                                         */
    if (!found_pos0)
    {
        code->error_occurred = tmpl_True;
        code->error_message =
            "Error Encountered: libtmpl\n"
            "    tmpl_GaussCode_Delete_Crossing\n\n"
            "No crossing with this crossing index, but the crossing\n"
            "index is less than the number of crossings. The input\n"
            "Gauss code is not valid.\n";

        return;
    }

    /*  We now need to rewrite the entries in the Gauss tuples array since we *
     *  are deleting two entries (one crossing with an entry for the under    *
     *  crossing and another for the over crossing). The entries that are     *
     *  before the first occurrence of the deleted crossing are unchanged.    *
     *  Entries between the first and second crossing are shifted back by one.*/
    for (ind = pos0; ind < pos1 - 1; ++ind)
        code->tuples[ind] = code->tuples[ind + 1];

    /*  Entries after the second occurrence are shifted back by two.          */
    for (ind = pos1; ind < code->length - 1; ++ind)
        code->tuples[ind - 1] = code->tuples[ind + 1];

    /*  We've deleted one crossing, which means the Gauss code lost two       *
     *  entries. Decrement the number_of_crossings by 1 and the length by 2.  */
    code->number_of_crossings -= 1UL;
    code->length -= 2UL;

    /*  Free up the unused memory using realloc.                              */
    tmp = TMPL_REALLOC(code->tuples, code->length);

    /*  Check if realloc was successful before resetting the pointer.         *
     *  If realloc failed, the Gauss tuples pointer still points to the       *
     *  original array. This array is larger than needed, but it does         *
     *  contain the correct data.                                             */
    if (tmp)
        code->tuples = TMPL_CAST(tmp, tmpl_GaussTuple *);
}
/*  End of tmpl_GaussCode_Delete_Crossing.                                    */
