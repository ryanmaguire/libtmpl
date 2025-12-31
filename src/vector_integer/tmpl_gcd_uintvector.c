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
 *  Computes the GCD of a vector of non-negative integers.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2021/07/29                                                    *
 ******************************************************************************/

/*  size_t found here.                                                        */
#include <stddef.h>

/*  GCD function found here.                                                  */
#include <libtmpl/include/tmpl_integer.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_vector_integer.h>

/*  Function for computing the GCD of a vector of non-negative integers.      */
unsigned int tmpl_UIntVector_GCD(tmpl_UIntVector *arr)
{
    size_t n;
    unsigned int gcd;

    if (!arr)
        return 0U;

    if (arr->error_occurred || !arr->data || arr->length == 0UL)
        return 0U;

    /*  If there is only one element, the GCD is just that element.           */
    if (arr->length == 1UL)
        return arr->data[0];

    /*  Otherwise the GCD is computed via GCD(a, b, ...) = GCD(GCD(a, b), ...).
     *  Start the computation by computing the GCD of the first two elements. */
    else
        gcd = tmpl_UInt_GCD(arr->data[0], arr->data[1]);

    /*  Loop over the remaining elements and iteratively compute the GCD.     */
    for (n = (size_t)2; n < arr->length; ++n)
        gcd = tmpl_UInt_GCD(gcd, arr->data[n]);

    return gcd;
}
/*  End of tmpl_UIntVector_GCD.                                               */
