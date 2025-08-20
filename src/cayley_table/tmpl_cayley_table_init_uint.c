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
 *                         tmpl_cayley_table_init_uint                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Initializes a Cayley table to the empty binary operation.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UIntCayleyTable_Init                                             *
 *  Purpose:                                                                  *
 *      Initialize a Cayley table to the empty binary operation.              *
 *  Arguments:                                                                *
 *      table (tmpl_UIntCayleyTable * const):                                 *
 *          The Cayley table to be initialized.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Set the data pointer to NULL and the size to zero.                    *
 *  Notes:                                                                    *
 *      1.) This checks if table is NULL. Nothing is done in this case.       *
 *      2.) A memory leak will occur if table->data was already allocated     *
 *          memory. This function sets table->data = NULL and table-size = 0. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_cayley_table_uint.h:                                             *
 *          Header file containing the typedef for Cayley tables.             *
 *  2.) tmpl_cayley_table.h:                                                  *
 *          Function prototype found here.                                    *
 *  3.) stddef.h:                                                             *
 *          Standard header file providing the NULL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 20, 2025                                               *
 ******************************************************************************/

/*  Typedef for unsigned integer Cayley tables given here.                    */
#include <libtmpl/include/types/tmpl_cayley_table_uint.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_cayley_table.h>

/*  NULL is found here.                                                       */
#include <stddef.h>

/*  Checks if a Cayley table corresponds to a valid binary operation.         */
void tmpl_UIntCayleyTable_Init(tmpl_UIntCayleyTable * const table)
{
    /*  Safety check, make sure the pointer isn't NULL.                       */
    if (!table)
        return;

    /*  Initialize the table to the empty operation. This has a NULL data     *
     *  pointer and zero elements, hence the size is zero.                    */
    table->data = NULL;
    table->size = 0;
}
/*  End of tmpl_UIntCayleyTable_Init.                                         */
