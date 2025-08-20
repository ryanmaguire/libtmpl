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
 *                    tmpl_cayley_table_is_associative_uint                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents an associative operation.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UIntCayleyTable_Is_Associative                                   *
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents an associative binary operation.  *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_associative (tmpl_Bool):                                           *
 *          Boolean indicating if the table is associative.                   *
 *  Called Functions:                                                         *
 *      src/cayley_table/                                                     *
 *          tmpl_UIntCayleyTable_Is_Associative_Kernel:                       *
 *              Check if (x*y)*z = x*(y*z) for all ordered triples (x, y, z)  *
 *              from the underlying set.                                      *
 *  Method:                                                                   *
 *      We first check for a few errors, returning false in these cases:      *
 *                                                                            *
 *          1.) The input table is NULL.                                      *
 *          2.) The input data for the table is NULL and size is positive.    *
 *          3.) The input size is zero and the data for the table is not NULL.*
 *                                                                            *
 *      We also check for the "empty operation" which corresponds to the      *
 *      sole operation that is defined on the empty set. The empty operation  *
 *      corresponds to a Cayley table with size = 0 and data = NULL.          *
 *                                                                            *
 *      For a non-empty Cayley table we use the inner kernel function,        *
 *      tmpl_UIntCayleyTable_Is_Associative_Kernel, which checks if           *
 *      (x*y)*z = x*(y*z) for all possible triples from the set.              *
 *  Notes:                                                                    *
 *      1.) This function assumes the table input is indeed a valid Cayley    *
 *          table. This means table->data[n] < table->size for all entries    *
 *          of the table (for all 0 <= n < table-size * table-size).          *
 *      2.) This routine checks for NULL pointers for both table and          *
 *          table->data, and it checks if table->size = 0.                    *
 *      3.) If table is the empty table (table->data = NULL, table->size = 0),*
 *          then this routine returns true. The empty binary operations is    *
 *          vacuously associative since there are no x, y, z in the set with  *
 *          (x*y)*z != x*(y*z).                                               *
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

/*  Checks if a Cayley table corresponds to an associative operation.         */
tmpl_Bool
tmpl_UIntCayleyTable_Is_Associative(const tmpl_UIntCayleyTable * const table)
{
    /*  Safety check, make sure the pointer isn't NULL. A NULL table is not   *
     *  treated the same as an empty table. This is likely an error, hence we *
     *  return false.                                                         */
    if (!table)
        return tmpl_False;

    /*  Check for the empty Cayley table, which is the Cayley table for the   *
     *  "empty operation" on the empty set. It is vacuously an associative    *
     *  table (there are no elements x, y, z in the empty set with            *
     *  x*(y*z) != (x*y)*z, so the operation is associative).                 *
     *                                                                        *
     *  The empty Cayley table is given by a NULL data pointer and size = 0.  */
    if (!table->data)
    {
        /*  We have a NULL data pointer. If the size is zero, then we are     *
         *  working with the empty set. The operation is hence associative.   */
        if (table->size == 0)
            return tmpl_True;

        /*  Otherwise we likely have an error. Return false.                  */
        return tmpl_False;
    }

    /*  If the data table is not NULL and size is zero, we have an error.     *
     *  Return false in this case as well.                                    */
    if (table->size == 0)
        return tmpl_False;

    /*  Perform the main check, looping through triples (x, y, z) and         *
     *  checking for (x*y)*z = x*(y*z).                                       */
    return tmpl_UIntCayleyTable_Is_Associative_Kernel(table);
}
/*  End of tmpl_UIntCayleyTable_Is_Associative.                               */
