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
 *                       tmpl_array_minmax_index_ullong                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the indices for min and max of an unsigned long long array.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULLong_Array_MinMax_Index                                        *
 *  Purpose:                                                                  *
 *      Finds the indices for the min and max of an unsigned long long array. *
 *  Arguments:                                                                *
 *      arr (const unsigned long long int * const):                           *
 *          An unsigned long long array.                                      *
 *      len (size_t):                                                         *
 *          The length of the array.                                          *
 *      minind (size_t *):                                                    *
 *          A pointer to a size_t. The index of the minimum is stored here.   *
 *      maxind (size_t *):                                                    *
 *          A pointer to a size_t. The index of the maximum is stored here.   *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through the elements of the array and compare.                   *
 *  Notes:                                                                    *
 *      This file is only compiled if long long support is available.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard header file containing the size_t typedef.               *
 *  2.) tmpl_inttype.h:                                                       *
 *          Header file with the TMPL_HAS_LONGLONG macro.                     *
 *  3.) tmpl_array_integer.h:                                                 *
 *          Header file with the function prototype.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 8, 2024                                                 *
 ******************************************************************************/

/*  The TMPL_HAS_LONGLONG macro is found here.                                */
#include <libtmpl/include/tmpl_inttype.h>

/*  Only compile this if long long support is available / requested.          */
#if TMPL_HAS_LONGLONG == 1

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_array_integer.h>

/*  Finds the index of the min and max of an unsigned long long array.        */
void
tmpl_ULLong_Array_MinMax_Index(const unsigned long long int * const arr,
                               size_t len,
                               size_t *minind,
                               size_t *maxind)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;

    /*  If the array is NULL or empty, the result is undefined.               */
    if (!arr || !len || !minind || !maxind)
        return;

    /*  Initialize the min and max variables to the zeroth element.           */
    *minind = 0;
    *maxind = 0;

    /*  Loop through the remaining elements and find the min and max.         */
    for (n = 1; n < len; ++n)
    {
        /*  If the current array element is smaller, reset the min index.     */
        if (arr[n] < arr[*minind])
            *minind = n;

        /*  If the current array element is larger, reset the max index.      */
        else if (arr[n] > arr[*maxind])
            *maxind = n;
    }
}
/*  End of tmpl_ULLong_Array_MinMax_Index.                                    */

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */
