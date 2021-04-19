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
 *  Purpose:                                                                  *
 *      Returns the z component of a three dimensional vector/spacial point.  *
 *      That is, given (x, y, z), return z.                                   *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Function for returning the z component of a three dimensional vector.     */
double tmpl_ThreeVector_Z(tmpl_ThreeVector P)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double z;

    /*  tmpl_ThreeVector is a struct consisting of a single double            *
     *  array dat with three entries. The z component corresponds to the      *
     *  second entry. Retrieve this and return.                               */
    z = P.dat[2];
    return z;
}
/*  End of tmpl_ThreeVector_Z.                                                */

