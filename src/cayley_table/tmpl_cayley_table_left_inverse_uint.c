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
 *                    tmpl_cayley_table_left_inverse_uint                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Solves the equation x * element = 0 from a given Cayley table.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UIntCayleyTable_Left_Inverse                                     *
 *  Purpose:                                                                  *
 *      Given a Cayley table, attempts to solve x * element = 0.              *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The Cayley table representing the algebraic structure.            *
 *      element (const unsigned int):                                         *
 *          The element we are trying to find a left-inverse of.              *
 *  Output:                                                                   *
 *      x (unsigned int):                                                     *
 *          A solution to x * element = 0 (if it exists).                     *
 *  Called Functions:                                                         *
 *      src/cayley_table/                                                     *
 *          tmpl_UIntCayleyTable_Left_Inverse_Kernel:                         *
 *              Loops through and tries to find a left-inverse for "element". *
 *  Method:                                                                   *
 *      First check that the Cayley table is valid, returning UINT_MAX if it  *
 *      is not. Since Cayley tables on n elements must have entries between   *
 *      0 and n - 1, there is only ambiguity if the underlying set contains   *
 *      UINT_MAX elements, meaning the Cayley table has UINT_MAX^2 elements.  *
 *      Since UINT_MAX is usually 2^32 - 1, this would mean the Cayley table  *
 *      would require roughly 2^64 elements. It is highly unlikely anyone     *
 *      would ever need to work with such a table, meaning UINT_MAX is a      *
 *      reasonable error indicator.                                           *
 *                                                                            *
 *      If the inputs are valid, we loop through all possible values "x" and  *
 *      check for x * element = 0. We return the first "x" that solves this.  *
 *  Notes:                                                                    *
 *      1.) This checks if table is NULL. UINT_MAX is returned in this case.  *
 *      2.) If the table is empty, UINT_MAX is returned.                      *
 *      3.) If "element" is larger than table->size, then it is not a         *
 *          member of the underlying set. We return UINT_MAX in this case.    *
 *      4.) It is possible for x * element = 0 to have multiple solutions.    *
 *          This function returns the smallest possible solution.             *
 *      5.) It is possible for x * element = 0 to have no solutions. UINT_MAX *
 *          is returned in this case.                                         *
 *      6.) This function assumes the Cayley table has an identity, and that  *
 *          it is represented by "0". The output is meaningless if either of  *
 *          these two conditions are not met.                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_cayley_table_uint.h:                                             *
 *          Header file containing the typedef for Cayley tables.             *
 *  2.) tmpl_cayley_table.h:                                                  *
 *          Function prototype found here.                                    *
 *  3.) tmpl_cast.h:                                                          *
 *          Provides a macro for casting with C vs. C++ compatibility.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 20, 2025                                               *
 ******************************************************************************/

/*  Typedef for unsigned integer Cayley tables given here.                    */
#include <libtmpl/include/types/tmpl_cayley_table_uint.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_cayley_table.h>

/*  TMPL_CAST macro found here, providing C vs. C++ compatibility.            */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Finds a left-inverse for a given element in a Cayley table.               */
unsigned int
tmpl_UIntCayleyTable_Left_Inverse(const tmpl_UIntCayleyTable * const table,
                                  const unsigned int element)
{
    /*  Value used to indicate an error. This is the largest possible         *
     *  unsigned int. There is only ambiguity if you happen to have a Cayley  *
     *  table for a set with UINT_MAX number of elements. Since unsigned int  *
     *  is usually 32-bits, this would require a Cayley table with roughly    *
     *  (2^32)^2 = 2^64 entries. It is very unlikely someone will ever need   *
     *  to work with such things.                                             */
    const unsigned int invalid = TMPL_CAST(-1, unsigned int);

    /*  Safety check, make sure the pointer isn't NULL.                       */
    if (!table)
        return invalid;

    /*  The empty table does not have any elements, so element and 0 cannot   *
     *  be part of this table. If table->data is NULL or table->size is zero, *
     *  this is an error. Return invalid.                                     */
    if ((!table->data) || (table->size == 0))
        return invalid;

    /*  Lastly, for this to be a valid Cayley table, we need element to be a  *
     *  member of the underlying set, meaning element < table->size. Check.   */
    if (table->size <= element)
        return invalid;

    /*  The main computation is done with the kernel function. This searches  *
     *  for an index "x" with table[x, element] = 0.                          */
    return tmpl_UIntCayleyTable_Left_Inverse_Kernel(table, element);
}
/*  End of tmpl_UIntCayleyTable_Left_Inverse.                                 */
