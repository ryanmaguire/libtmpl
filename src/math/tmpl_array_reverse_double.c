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
 *                          tmpl_array_reverse_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Reverse the order of a double array.                                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Array_Reverse                                             *
 *  Purpose:                                                                  *
 *      Reverse the order of the elements of an array of doubles.             *
 *  Arguments:                                                                *
 *      arr (double *):                                                       *
 *          An array of doubles.                                              *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through the array and swap the elements two at a time.           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          size_t found here.                                                *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 31, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/12/20: Ryan Maguire                                                  *
 *      Added license and description.                                        *
 ******************************************************************************/

/*  size_t typedef is here.                                                   */
#include <stddef.h>

/*  Function prototype give here.                                             */
#include <libtmpl/include/tmpl_math.h>

/*  Standard algorithm of time-complexity O(n) to take an array and reverse   *
 *  the order.                                                                */
void tmpl_Double_Array_Reverse(double *arr, size_t len)
{
    /*  Variable for saving the value of the nth element of the array.        */
    double tmp;

    /*  Variable for indexing.                                                */
    size_t n;

    /*  Two elements are swapped at a time, to only len/2 iterations needed.  */
    const size_t N = len >> 1U;

    /*  Check if the array is empty, or the length is zero.                   */
    if (!arr || !len)
        return;

    /*  Loop over the elements of the array.                                  */
    for(n = 0; n < N; ++n)
    {
        /*  Perform a basic swap of two variables.                            */
        tmp = arr[n];
        arr[n] = arr[len - n - 1];
        arr[len - n - 1] = tmp;
    }
}
/*  End of tmpl_Double_Array_Reverse.                                         */
