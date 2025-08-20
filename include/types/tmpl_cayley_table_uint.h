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
 *                           tmpl_cayley_table_uint                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a Cayley table data type with unsigned int entries.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 20, 2025                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CAYLEY_TABLE_UINT_H
#define TMPL_CAYLEY_TABLE_UINT_H

/*  size_t typedef provided here.                                             */
#include <stddef.h>

/*  Cayley table structure (for groups, quandles, etc.) with unsigned ints.   */
typedef struct tmpl_UIntCayleyTable_Def {

    /*  Pointer to the data array. We do not use a 2D array, but instead use  *
     *  a single 1D array with size^2 elements allocated. The (n, m) entry    *
     *  corresponds to the n + size * m element of the array.                 */
    unsigned int *data;

    /*  The number of elements in the algebraic structure. The Cayley table   *
     *  hence has size^2 elements allocated to it.                            */
    size_t size;
} tmpl_UIntCayleyTable;

#endif
/*  End of include guard.                                                     */
