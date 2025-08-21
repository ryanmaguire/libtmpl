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
 *                tmpl_cayley_table_is_associative_kernel_uint                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents an associative operation.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UIntCayleyTable_Is_Associative_Kernel                            *
 *  Purpose:                                                                  *
 *      Checks if a Cayley table represents an associative binary operation.  *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_associative (tmpl_Bool):                                           *
 *          Boolean indicating if the table is associative.                   *
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
 *      3.) Light's test is not used. The naive algorithm is implemented      *
 *          instead.                                                          *
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

/*  Checks if a Cayley table corresponds to an associative operation.         */
tmpl_Bool
tmpl_UIntCayleyTable_Is_Associative_Kernel(
    const tmpl_UIntCayleyTable * const table
)
{
    /*  Variables for indexing the table. We will check if (x*y)*z = x*(y*z)  *
     *  for each ordered triple (x, y, z) of elements from the structure.     */
    size_t x, y, z;

    /*  Variables for x*y, y*z, (x*y)*z, and x*(y*z), respectively.           */
    unsigned int xy, yz, left, right;

    /*  Loop through the ordered triples from the algebraic structure and     *
     *  check for associativity. This algorithm does not use Light's test,    *
     *  it uses the naive algorithm (which is faster when the table is indeed *
     *  associative).                                                         */
    for (x = 0; x < table->size; ++x)
    {
        for (y = 0; y < table->size; ++y)
        {
            /*  Compute the product x * y.                                    */
            xy = TMPL_CAYLEY_TABLE_ENTRY(table, x, y);

            for (z = 0; z < table->size; ++z)
            {
                /*  Compute y*z, (x*y)*z, and x*(y*z).                        */
                yz = TMPL_CAYLEY_TABLE_ENTRY(table, y, z);
                left = TMPL_CAYLEY_TABLE_ENTRY(table, xy, z);
                right = TMPL_CAYLEY_TABLE_ENTRY(table, x, yz);

                /*  If (x*y)*z != x*(y*z), the table is not associative.      */
                if (left != right)
                    return tmpl_False;
            }
        }
    }

    /*  We have (x*y)*z = x*(y*z) for all possible triples, so the table is   *
     *  indeed associative. Return true.                                      */
    return tmpl_True;
}
/*  End of tmpl_UIntCayleyTable_Is_Associative_Kernel.                        */
