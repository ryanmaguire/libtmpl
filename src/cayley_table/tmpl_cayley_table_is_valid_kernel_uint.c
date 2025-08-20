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
 *                   tmpl_cayley_table_is_valid_kernel_uint                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents a valid binary operation.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UIntCayleyTable_Is_Valid_Kernel                                  *
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents a valid binary operation.         *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_valid (tmpl_Bool):                                                 *
 *          Boolean indicating if the table is valid.                         *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through and check if table->data[n] < table->size for all n.     *
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
 *  Date:       August 20, 2025                                               *
 ******************************************************************************/

/*  Booleans provided here.                                                   */
#include <libtmpl/include/tmpl_bool.h>

/*  Typedef for unsigned integer Cayley tables given here.                    */
#include <libtmpl/include/types/tmpl_cayley_table_uint.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_cayley_table.h>

/*  size_t typedef is provided here.                                          */
#include <stddef.h>

/*  Checks if a Cayley table represents a valid operation.                    */
tmpl_Bool
tmpl_UIntCayleyTable_Is_Valid_Kernel(const tmpl_UIntCayleyTable * const table)
{
    /*  Index for the table. We will check table->data[n] < table->size for   *
     *  all 0 <= n < table->size * table->size.                               */
    size_t n;

    /*  size represents the number of elements in the underlying set. The     *
     *  Cayley table has size^2 number of elements. We need this for the loop.*/
    const size_t number_of_elements = table->size * table->size;

    /*  Loop through every element of the table and check that the entries    *
     *  are numbers between 0 and size - 1.                                   */
    for (n = 0; n < number_of_elements; ++n)
    {
        /*  The entries must be between 0 and size - 1, since the underlying  *
         *  set is the integers 0, 1, ..., size - 2, size - 1. Check for this.*/
        if (table->size <= table->data[n])
            return tmpl_False;
    }

    /*  Every element of the table is between 0 and size - 1. This is a       *
     *  valid binary operation, return true.                                  */
    return tmpl_True;
}
/*  End of tmpl_UIntCayleyTable_Is_Valid_Kernel.                              */
