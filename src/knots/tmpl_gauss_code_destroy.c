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
 *                          tmpl_gauss_code_destroy                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Free's a dynamically allocated Gauss code and sets it to NULL.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_GaussCode_Destroy                                                *
 *  Purpose:                                                                  *
 *      Safely free's the memory in a dynamically allocated Gauss code.       *
 *  Arguments:                                                                *
 *      code_ptr (tmpl_GaussCode ** const):                                   *
 *          A pointer to a Gauss code.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          free:                                                             *
 *              Free's dynamically allocated memory.                          *
 *  Method:                                                                   *
 *      Use the TMPL_FREE macro to check if the code is NULL, freeing it if   *
 *      is not, and then setting the code to NULL to avoid double frees.      *
 *      The tuples pointer is also free'd and set to NULL.                    *
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
 *  2025/10/14: Ryan Maguire                                                  *
 *      Added docstring and replaced free with TMPL_FREE. Renamed function to *
 *      be consistent with other routines.                                    *
 ******************************************************************************/

/*  Typedef for the Gauss tuple struct provided here.                         */
#include <libtmpl/include/types/tmpl_gauss_tuple.h>

/*  Gauss code data type defined here.                                        */
#include <libtmpl/include/types/tmpl_gauss_code.h>

/*  Location of the TMPL_FREE macro.                                          */
#include <libtmpl/include/compat/tmpl_free.h>

/*  Forward declaration / function prototype, found in tmpl_knots.h as well.  */
extern void tmpl_GaussCode_Destroy(tmpl_GaussCode ** const code_ptr);

/*  Function used for freeing the data allocated to a Gauss tuple array.      */
extern void tmpl_GaussTuple_Destroy(tmpl_GaussTuple ** const tuples_ptr);

/*  Function for freeing memory in a dynamically allocated Gauss code.        */
void tmpl_GaussCode_Destroy(tmpl_GaussCode ** const code_ptr)
{
    /*  Pointer for the actual Gauss code. We'll set this after checking that *
     *  code_ptr is not NULL.                                                 */
    tmpl_GaussCode *code;

    /*  Pointer for the tuples array, which is part of the Gauss code struct. */
    tmpl_GaussTuple *tuples;

    /*  If the input pointer is NULL, there's nothing to be done. Return.     */
    if (!code_ptr)
        return;

    /*  Get a pointer for the Gauss code. We'll free this and set it to NULL. */
    code = *code_ptr;

    /*  Avoid dereferencing a NULL pointer. Nothing to be done in this case.  */
    if (!code)
        return;

    /*  Get the actual tuples array. This is the majority of the data that    *
     *  needs to be freed.                                                    */
    tuples = code->tuples;

    /*  This function safely free's the data and sets the pointer to NULL.    */
    tmpl_GaussTuple_Destroy(&tuples);

    /*  TMPL_FREE will free the code if it is not NULL, and then set the      *
     *  pointer to be NULL after freeing. Use this.                           */
    TMPL_FREE(code);
}
/*  End of tmpl_GaussCode_Destroy.                                            */
