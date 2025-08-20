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
 *                     tmpl_cayley_table_right_solve_uint                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Solves the equation a * x = b from a given Cayley table.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UIntCayleyTable_Right_Solve                                      *
 *  Purpose:                                                                  *
 *      Given a Cayley table, attempts to solve a * x = b.                    *
 *  Arguments:                                                                *
 *      table (const tmpl_UIntCayleyTable * const):                           *
 *          The Cayley table representing the algebraic structure.            *
 *      a (const unsigned int):                                               *
 *          The left multiplier for "x".                                      *
 *      b (const unsigned int):                                               *
 *          The right-hand side of the equation.                              *
 *  Output:                                                                   *
 *      x (unsigned int):                                                     *
 *          A solution to a * x = b (if it exists).                           *
 *  Called Functions:                                                         *
 *      src/cayley_table/                                                     *
 *          tmpl_UIntCayleyTable_Right_Solve_Kernel:                          *
 *              Loops through the "a" column of a Cayley table to find a      *
 *              solution to a * x = b.                                        *
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
 *      check for a * x = b. We return the first "x" that solves this.        *
 *  Notes:                                                                    *
 *      1.) This checks if table is NULL. UINT_MAX is returned in this case.  *
 *      2.) If the table is empty, UINT_MAX is returned.                      *
 *      3.) If "a" or "b" are larger than table->size, then they are not      *
 *          elements of the underlying set. We return UINT_MAX in this case.  *
 *      4.) It is possible for a * x = b to have multiple solutions. This     *
 *          function returns the smallest possible solution.                  *
 *      5.) It is possible for a * x = b to have no solutions. UINT_MAX is    *
 *          returned in this case.                                            *
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

/*  Checks if a Cayley table corresponds to a valid binary operation.         */
unsigned int
tmpl_UIntCayleyTable_Right_Solve(const tmpl_UIntCayleyTable * const table,
                                 const unsigned int a, const unsigned int b)
{
    /*  Value used to indicate an error. This is the largest possible         *
     *  unsigned int. There is only ambiguity if you happen to have a Cayley  *
     *  table for a set with UINT_MAX number of elements. Since unsigned int  *
     *  is usually 32-bits, this would require a Cayley table with roughly    *
     *  (2^32)^2 = 2^64 entries. It is very unlikely someone will ever need   *
     *  to work with such things.                                          */
    const unsigned int invalid = TMPL_CAST(-1, unsigned int);

    /*  Safety check, make sure the pointer isn't NULL.                       */
    if (!table)
        return invalid;

    /*  The empty table does not have any elements, so a and b cannot be part *
     *  of this table. If table->data is NULL or table->size is zero, this is *
     *  an error. Return invalid.                                             */
    if ((!table->data) || (table->size == 0))
        return invalid;

    /*  Lastly, for this to be a valid Cayley table, we need a < table->size  *
     *  and b < table->size. Check for this.                                  */
    if ((table->size <= a) || (table->size <= b))
        return invalid;

    /*  The main computation is done with the kernel function. This searches  *
     *  for an index "x" with table[a, x] = b.                                */
    return tmpl_UIntCayleyTable_Right_Solve_Kernel(table, a, b);
}
/*  End of tmpl_UIntCayleyTable_Right_Solve.                                  */
