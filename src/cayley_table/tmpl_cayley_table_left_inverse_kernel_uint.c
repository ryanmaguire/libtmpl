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
 *                 tmpl_cayley_table_left_inverse_kernel_uint                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Solves the equation x * element = 0 from a given Cayley table.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UIntCayleyTable_Left_Inverse_Kernel                              *
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
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through all possible values "x" and check for x * element = 0.   *
 *      We return the first "x" that solves this.                             *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers or table->size = 0.         *
 *      2.) It is possible for x * element = 0 to have multiple solutions.    *
 *          This function returns the smallest possible solution.             *
 *      3.) It is possible for x * element = 0 to have no solutions. UINT_MAX *
 *          is returned in this case.                                         *
 *      4.) This function assumes the Cayley table has an identity, and that  *
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

/*  Searches for a left-inverse to a given element in a Cayley table.         */
unsigned int
tmpl_UIntCayleyTable_Left_Inverse_Kernel(
    const tmpl_UIntCayleyTable * const table,
    const unsigned int element
)
{
    /*  Value used to indicate an error. This is the largest possible         *
     *  unsigned int. There is only ambiguity if you happen to have a Cayley  *
     *  table for a set with UINT_MAX number of elements. Since unsigned int  *
     *  is usually 32-bits, this would require a Cayley table with roughly    *
     *  (2^32)^2 = 2^64 entries. It is very unlikely someone will ever need   *
     *  to work with such things.                                             */
    const unsigned int invalid = TMPL_CAST(-1, unsigned int);

    /*  The table->size member is of type size_t. To avoid repeatedly casting *
     *  between data types while indexing through the table, convert element  *
     *  to type size_t as well and compute with that.                         */
    const size_t element_ind = TMPL_CAST(element, size_t);

    /*  Variable for indexing over the row in the table. We use this to       *
     *  search for solutions to x * element = 0.                              */
    size_t x;

    /*  Loop through the element row, searching for an x with x * element = 0.*/
    for (x = 0; x < table->size; ++x)
    {
        /*  Solving for x * element = 0 means we are looking for an index x   *
         *  with table[x, element] = 0. Check each element in the row.        */
        if (TMPL_CAYLEY_TABLE_ENTRY(table, x, element_ind) == 0)
            return TMPL_CAST(x, unsigned int);
    }

    /*  No solution was found, meaning x * element = 0 cannot be solved.      *
     *  Return invalid to caller. Note, there is no guarantee that this       *
     *  Cayley table represents a group, or some other algebraic structure    *
     *  where inverses exist. It is certainly possible for "element" to not   *
     *  have a left inverse in a general Cayley table.                        */
    return invalid;
}
/*  End of tmpl_UIntCayleyTable_Left_Inverse_Kernel.                          */
