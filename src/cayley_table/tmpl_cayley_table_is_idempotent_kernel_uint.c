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
 *                 tmpl_cayley_table_is_idempotent_kernel_uint                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents an idempotent operation.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UIntCayleyTable_Is_Idempotent_Kernel                             *
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents an idempotent binary operation.   *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_idempotent (tmpl_Bool):                                            *
 *          Boolean indicating if the table is idempotent.                    *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through and check if table[x, x] = x for all x.                  *
 *  Notes:                                                                    *
 *      1.) This routine does not check for NULL pointers or table->size = 0. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_cayley_table_uint.h:                                             *
 *          Header file containing the typedef for Cayley tables.             *
 *  3.) tmpl_cayley_table.h:                                                  *
 *          Function prototype found here.                                    *
 *  4.) stddef.h:                                                             *
 *          Standard header file providing the size_t data type.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 21, 2025                                               *
 ******************************************************************************/

/*  Booleans provided here.                                                   */
#include <libtmpl/include/tmpl_bool.h>

/*  Typedef for unsigned integer Cayley tables given here.                    */
#include <libtmpl/include/types/tmpl_cayley_table_uint.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_cayley_table.h>

/*  size_t typedef is provided here.                                          */
#include <stddef.h>

/*  Checks if a Cayley table represents an idempotent operation.              */
tmpl_Bool
tmpl_UIntCayleyTable_Is_Idempotent_Kernel(
    const tmpl_UIntCayleyTable * const table
)
{
    /*  Index for the table. We will check if table[x, x] = x for each x.     */
    size_t x;

    /*  Loop through each element of the underlying set.                      */
    for (x = 0; x < table->size; ++x)
    {
        /*  An idempotent operation has x * x = x for all x. Check this.      */
        if (TMPL_CAYLEY_TABLE_ENTRY(table, x, x) != x)
            return tmpl_False;
    }

    /*  Every element satisfies x * x = x, the operation is idempotent.       */
    return tmpl_True;
}
/*  End of tmpl_UIntCayleyTable_Is_Idempotent_Kernel.                         */
