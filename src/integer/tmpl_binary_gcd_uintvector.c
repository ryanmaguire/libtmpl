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
 ******************************************************************************
 *  Computes the GCD of two non-negative integers.                            *
 ******************************************************************************
 *  Author: Ryan Maguire, Dartmouth College                                   *
 *  Date:   2021/07/29                                                        *
 ******************************************************************************/

#include <libtmpl/include/tmpl_vector.h>
#include <libtmpl/include/tmpl_integer.h>

unsigned int tmpl_UIntVector_GCD(tmpl_UIntVector *arr)
{
    unsigned long int n;
    unsigned int gcd;

    if (!arr)
        return 0U;

    if (arr->error_occurred)
        return 0U;

    if (!arr->data)
        return 0U;

    if (arr->length == 0UL)
        return 0U;

    if (arr->length == 1UL)
        return arr->data[0];
    else
        gcd = tmpl_UInt_GCD(arr->data[0], arr->data[1]);

    for (n = 2UL; n < arr->length; ++n)
        gcd = tmpl_UInt_GCD(gcd, arr->data[n]);

    return gcd;
}
/*  End of tmpl_UIntVector_GCD.                                               */

