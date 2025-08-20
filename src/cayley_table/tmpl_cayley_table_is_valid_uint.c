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
 *                       tmpl_cayley_table_is_valid_uint                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents a valid binary operation.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UIntCayleyTable_Is_Valid                                         *
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents a valid binary operation.         *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_valid (tmpl_Bool):                                                 *
 *          Boolean indicating if the table is valid.                         *
 *  Called Functions:                                                         *
 *      src/cayley_table/                                                     *
 *          tmpl_UIntCayleyTable_Is_Valid_Kernel:                             *
 *              Check if table->data[n] < table->size for all 0 <= n < size^2.*
 *  Method:                                                                   *
 *      We first check for a few errors, returning false in these cases:      *
 *                                                                            *
 *          1.) The input table is NULL.                                      *
 *          2.) The input data for the table is NULL and size is positive.    *
 *          3.) The input size is zero and the data for the table is not NULL.*
 *                                                                            *
 *      We also check for the "empty operation" which corresponds to the      *
 *      sole operation that is defined on the empty set.                      *
 *                                                                            *
 *      For a non-empty Cayley table we use the inner kernel function,        *
 *      tmpl_UIntCayleyTable_Is_Valid_Kernel, which checks if                 *
 *      table->data[n] < table->size for all 0 <= n < table->size*table->size.*
 *  Notes:                                                                    *
 *      1.) This routine checks for NULL pointers for both table and          *
 *          table->data, and it checks if table->size = 0.                    *
 *      2.) If table is the empty table (table->data = NULL, table->size = 0),*
 *          then this routine returns true. This is the "empty operation."    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_cayley_table_uint.h:                                             *
 *          Header file containing the typedef for Cayley tables.             *
 *  3.) tmpl_cayley_table.h:                                                  *
 *          Function prototype found here.                                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 20, 2025                                               *
 ******************************************************************************/

/*  Booleans provided here.                                                   */
#include <libtmpl/include/tmpl_bool.h>

/*  Typedef for unsigned integer Cayley tables given here.                    */
#include <libtmpl/include/types/tmpl_cayley_table_uint.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_cayley_table.h>

/*  Checks if a Cayley table corresponds to a valid binary operation.         */
tmpl_Bool
tmpl_UIntCayleyTable_Is_Valid(const tmpl_UIntCayleyTable * const table)
{
    /*  Safety check, make sure the pointer isn't NULL. A NULL table is not   *
     *  treated the same as an empty table. This is likely an error, hence we *
     *  return false.                                                         */
    if (!table)
        return tmpl_False;

    /*  Check for the empty Cayley table, which is the Cayley table for the   *
     *  "empty operation" on the empty set.                                   *
     *                                                                        *
     *  The empty Cayley table is given by a NULL data pointer and size = 0.  */
    if (!table->data)
    {
        /*  We have a NULL data pointer. If the size is zero, then we are     *
         *  working with the empty set. This is a valid binary operation.     */
        if (table->size == 0)
            return tmpl_True;

        /*  Otherwise we likely have an error. Return false.                  */
        return tmpl_False;
    }

    /*  If the data table is not NULL and size is zero, we have an error.     *
     *  Return false in this case as well.                                    */
    if (table->size == 0)
        return tmpl_False;

    /*  Perform the main check for table->data[n] < table->size.              */
    return tmpl_UIntCayleyTable_Is_Valid_Kernel(table);
}
/*  End of tmpl_UIntCayleyTable_Is_Valid.                                     */
