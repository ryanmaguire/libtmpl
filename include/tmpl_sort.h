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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SORT_H
#define TMPL_SORT_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

#include "tmpl_exports.h"

/*  size_t typedef given here.                                                */
#include <stddef.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Merge_Sort                                                *
 *  Purpose:                                                                  *
 *      Sorts an array of real numbers using the merge sort algorithm.        *
 *  Arguments:                                                                *
 *      double *arr:                                                          *
 *          An array of real numbers.                                         *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      int success:                                                          *
 *          0 if fail (malloc returns NULL), 1 if successful.                 *
 *  Notes:                                                                    *
 *      This algorithm is O(N log(N)) in time, and O(N) + O(N) in space.      *
 *      There's the input of size N, but a malloc of size N is also called    *
 *      to store temporary data. This is free'd at the end of the algorithm.  *
 *                                                                            *
 *      If malloc fails and returns NULL the algorithm is aborted and 0 is    *
 *      returned. The data will be untouched and still unsorted.              *
 ******************************************************************************/
TMPL_EXPORT extern int tmpl_Double_Merge_Sort(double *arr, size_t arr_size);
TMPL_EXPORT extern int tmpl_Float_Merge_Sort(float *arr, size_t arr_size);
TMPL_EXPORT extern int tmpl_LDouble_Merge_Sort(long double *arr, size_t arr_size);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
