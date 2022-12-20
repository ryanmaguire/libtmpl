/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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

/*  size_t typedef is here.                                                   */
#include <stddef.h>

/*  Function prototype give here.                                             */
#include <libtmpl/include/tmpl_math.h>

/*  Standard algorithm of time-complexity O(n) to take an array and reverse   *
 *  the order.                                                                */
void tmpl_Float_Array_Reverse(float *arr, size_t len)
{
    /*  Variable for saving the value of the nth element of the array.        */
    float tmp;

    /*  Variable for indexing.                                                */
    size_t n;

    /*  Two elements are swapped at a time, to only len/2 iterations needed.  */
    const size_t N = len >> 1U;

    /*  Loop over the elements of the array.                                  */
    for(n = 0; n < N; ++n)
    {
        /*  Perform a basic swap of two variables.                            */
        tmp = arr[n];
        arr[n] = arr[len - n - 1];
        arr[len - n - 1] = tmp;
    }
}
/*  End of tmpl_Float_Array_Reverse.                                          */
