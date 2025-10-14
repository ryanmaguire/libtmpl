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
 *                          tmpl_gauss_tuple_destroy                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Free's a dynamically allocated Gauss tuple and sets it to NULL.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_GaussTuple_Destroy                                               *
 *  Purpose:                                                                  *
 *      Safely free's the memory in a dynamically allocated Gauss tuple.      *
 *  Arguments:                                                                *
 *      tuple_ptr (tmpl_GaussTuple ** const):                                 *
 *          A pointer to a Gauss tuple.                                       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          free:                                                             *
 *              Free's dynamically allocated memory.                          *
 *  Method:                                                                   *
 *      Use the TMPL_FREE macro to check if the tuple is NULL, freeing it if  *
 *      is not, and then setting the tuple to NULL to avoid double frees.     *
 *  Notes:                                                                    *
 *      This function checks if either tuple_ptr or *tuple_ptr are NULL.      *
 *      Nothing is done in these cases.                                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_free.h:                                                          *
 *          Header providing TMPL_FREE with C vs. C++ compatibility.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 15, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/10/09: Ryan Maguire                                                  *
 *      Added docstring and replaced free with TMPL_FREE. Renamed function to *
 *      be consistent with other routines.                                    *
 ******************************************************************************/

/*  Typedef to the Gauss tuples struct provided here.                         */
#include <libtmpl/include/types/tmpl_gauss_tuple.h>

/*  Location of the TMPL_FREE macro.                                          */
#include <libtmpl/include/compat/tmpl_free.h>

/*  Forward declaration / function prototype, found in tmpl_knots.h as well.  */
extern void tmpl_GaussTuple_Destroy(tmpl_GaussTuple ** const tuples_ptr);

/*  Function for freeing memory in a dynamically allocated Gauss tuple.       */
void tmpl_GaussTuple_Destroy(tmpl_GaussTuple ** const tuples_ptr)
{
    /*  If the input pointer is NULL, there's nothing to be done. Return.     */
    if (!tuples_ptr)
        return;

    /*  TMPL_FREE will free the tuple if it is not NULL, and then set the     *
     *  pointer to be NULL after freeing. Use this.                           */
    TMPL_FREE(*tuples_ptr);
}
/*  End of tmpl_GaussTuple_Destroy.                                           */
