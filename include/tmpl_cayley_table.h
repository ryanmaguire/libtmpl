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
 *                             tmpl_cayley_table                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides simple tools for working with Cayley tables.                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/09/20: Ryan Maguire                                                  *
 *      Created file (KissVG).                                                *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2021/09/15: Ryan Maguire                                                  *
 *      Adding tools for working with planar polygons.                        *
 *  2022/12/30: Ryan Maguire                                                  *
 *      Changed naming convention to match vec3 and complex. Changed          *
 *      functions to pass by address instead of value. More reorganizing.     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CAYLEY_TABLE_H
#define TMPL_CAYLEY_TABLE_H

/*  size_t type given here.                                                   */
#include <stddef.h>

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Typedefs for Cayley tables with various data types.                       */
#include <libtmpl/include/types/tmpl_cayley_table_uint.h>

/*  Macro for extracting the (n, m) entry of a Cayley table. This does not    *
 *  check the size of the input, so it should only be used when you are sure  *
 *  that n < table->size and m < table->size.                                 */
#define TMPL_CAYLEY_TABLE_ENTRY(table, n, m) table->data[n + table->size * m]

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UIntCayleyTable_Init                                             *
 *  Purpose:                                                                  *
 *      Initialized a Cayley table to the empty operation.                    *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) This checks if table is NULL. Nothing is done in this case.       *
 *      2.) A memory leak will occur if table->data was already allocated     *
 *          memory. This function sets table->data = NULL and table-size = 0. *
 ******************************************************************************/
extern void tmpl_UIntCayleyTable_Init(tmpl_UIntCayleyTable * const table);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UIntCayleyTable_Is_Associative                                   *
 *  Purpose:                                                                  *
 *      Checks if a Cayley table corresponds to an associative operation.     *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_associative (tmpl_Bool):                                           *
 *          Boolean indicating if the table is associative.                   *
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
 ******************************************************************************/
extern tmpl_Bool
tmpl_UIntCayleyTable_Is_Associative(const tmpl_UIntCayleyTable * const table);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UIntCayleyTable_Is_Associative_Kernel                            *
 *  Purpose:                                                                  *
 *      Main part of the associativity checker, this loops over ordered       *
 *      triples (x, y, z) and checks if (x*y)*z = x*(y*z).                    *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_associative (tmpl_Bool):                                           *
 *          Boolean indicating if the table is associative.                   *
 *  Notes:                                                                    *
 *      1.) This function does not check for NULL pointers (either for table  *
 *          or for table->data), and it does not check if table->size is zero.*
 *      2.) This function assumes the table input is indeed a valid Cayley    *
 *          table. This means table->data[n] < table->size for all entries    *
 *          of the table (for all 0 <= n < table-size * table-size).          *
 ******************************************************************************/
extern tmpl_Bool
tmpl_UIntCayleyTable_Is_Associative_Kernel(
    const tmpl_UIntCayleyTable * const table
);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UIntCayleyTable_Is_Commutative                                   *
 *  Purpose:                                                                  *
 *      Checks if a Cayley table corresponds to a commutative operation.      *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_commutative (tmpl_Bool):                                           *
 *          Boolean indicating if the table is commutative.                   *
 *  Notes:                                                                    *
 *      1.) This function assumes the table input is indeed a valid Cayley    *
 *          table. This means table->data[n] < table->size for all entries    *
 *          of the table (for all 0 <= n < table-size * table-size).          *
 *      2.) This routine checks for NULL pointers for both table and          *
 *          table->data, and it checks if table->size = 0.                    *
 *      3.) If table is the empty table (table->data = NULL, table->size = 0),*
 *          then this routine returns true. The empty binary operations is    *
 *          vacuously commutative since there are no x, y in the set with     *
 *          x * y != y * x.                                                   *
 ******************************************************************************/
extern tmpl_Bool
tmpl_UIntCayleyTable_Is_Commutative(const tmpl_UIntCayleyTable * const table);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UIntCayleyTable_Is_Commutative_Kernel                            *
 *  Purpose:                                                                  *
 *      Main part of the commutativity checker, this loops over ordered       *
 *      pairs (x, y) and checks if x * y = y * x.                             *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_commutative (tmpl_Bool):                                           *
 *          Boolean indicating if the table is commutative.                   *
 *  Notes:                                                                    *
 *      1.) This function does not check for NULL pointers (either for table  *
 *          or for table->data), and it does not check if table->size is zero.*
 *      2.) This function assumes the table input is indeed a valid Cayley    *
 *          table. This means table->data[n] < table->size for all entries    *
 *          of the table (for all 0 <= n < table-size * table-size).          *
 ******************************************************************************/
extern tmpl_Bool
tmpl_UIntCayleyTable_Is_Commutative_Kernel(
    const tmpl_UIntCayleyTable * const table
);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UIntCayleyTable_Is_Valid                                         *
 *  Purpose:                                                                  *
 *      Checks if a Cayley table corresponds to a valid binary operation.     *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_valid (tmpl_Bool):                                                 *
 *          Boolean indicating if the table represents a binary operation.    *
 *  Notes:                                                                    *
 *      1.) This routine checks for NULL pointers for both table and          *
 *          table->data, and it checks if table->size = 0.                    *
 *      2.) If table is the empty table (table->data = NULL, table->size = 0),*
 *          then this routine returns true. This is the "empty operation."    *
 ******************************************************************************/
extern tmpl_Bool
tmpl_UIntCayleyTable_Is_Valid(const tmpl_UIntCayleyTable * const table);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UIntCayleyTable_Is_Valid_Kernel                                  *
 *  Purpose:                                                                  *
 *      Performs the main for-loop for checking if a Cayley table is valid.   *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The input Cayley table.                                           *
 *  Output:                                                                   *
 *      is_valid (tmpl_Bool):                                                 *
 *          Boolean indicating if the table represents a binary operation.    *
 *  Notes:                                                                    *
 *      1.) This routine does not check for NULL pointers or table->size = 0. *
 ******************************************************************************/
extern tmpl_Bool
tmpl_UIntCayleyTable_Is_Valid_Kernel(const tmpl_UIntCayleyTable * const table);

#endif
/*  End of include guard.                                                     */
