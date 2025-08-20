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
 *                tmpl_cayley_table_is_commutative_kernel_uint                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents a commutative operation.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UIntCayleyTable_Is_Commutative_Kernel                            *
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents a commutative binary operation.   *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_commutative (tmpl_Bool):                                           *
 *          Boolean indicating if the table is commutative.                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through all possible ordered triples (x, y, z), where x, y, and  *
 *      z are elements from the underlying set, and check for the equality:   *
 *                                                                            *
 *          table[table[x, y], z] = table[x, table[y, z]]                     *
 *                                                                            *
 *      which is equivalent to checking:                                      *
 *                                                                            *
 *          (x * y) * z = x * (y * z)                                         *
 *                                                                            *
 *      We return true if this equality always holds, and false otherwise.    *
 *  Notes:                                                                    *
 *      1.) This function does not check for NULL pointers (either for table  *
 *          or for table->data), and it does not check if table->size is zero.*
 *      2.) This function assumes the input table is indeed a valid Cayley    *
 *          table. This means table->data[n] < table->size for all entries    *
 *          of the table (for all 0 <= n < table-size * table-size).          *
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

/*  Checks if a Cayley table corresponds to a commutative operation.          */
tmpl_Bool
tmpl_UIntCayleyTable_Is_Commutative_Kernel(
    const tmpl_UIntCayleyTable * const table
)
{
    /*  Variables for indexing the table. We will check if x * y = x * y      *
     *  for each ordered pair (x, y) of elements from the structure.          */
    size_t x, y;

    /*  Variables for x * y and y * x, respectively.                          */
    unsigned int xy, yx;

    /*  Loop through the ordered pairs from the algebraic structure and       *
     *  check for commutativity.                                              */
    for (x = 0; x < table->size; ++x)
    {
        for (y = 0; y < table->size; ++y)
        {
            /*  Compute x * y and y * x.                                      */
            xy = TMPL_CAYLEY_TABLE_ENTRY(table, x, y);
            yx = TMPL_CAYLEY_TABLE_ENTRY(table, y, x);

            /*  If x * y != y * x, then the table is not commutative.         */
            if (xy != yx)
                return tmpl_False;
        }
    }

    /*  We have x * y = y * x for all possible pair, so the table is          *
     *  indeed commutative. Return true.                                      */
    return tmpl_True;
}
/*  End of tmpl_UIntCayleyTable_Is_Commutative_Kernel.                        */
