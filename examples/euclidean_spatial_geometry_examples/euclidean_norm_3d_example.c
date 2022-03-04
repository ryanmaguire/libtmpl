/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *      Provides an example of using the Euclidean norm function for a three  *
 *      dimensional vector.                                                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 11, 2020                                             *
 ******************************************************************************/

/*  The Euclidean norm is declared here.                                      */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for computing the norm of the vector (1, 2, 3).                   */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ThreeVectorDouble p;
    double norm;

    /*  Set the x, y, and z values to 1, 2, and 3, respectively.              */
    const double x = 1.0;
    const double y = 2.0;
    const double z = 3.0;

    /*  Set p to the vector (x, y, z).                                        */
    p = tmpl_3DDouble_Rect(x, y, z);

    /*  Compute the norm of p.                                                */
    norm = tmpl_3DDouble_Norm(p);

    /*  Print the result:                                                     */
    printf("||(%f, %f, %f)|| = %f\n", x, y, z, norm);

    return 0;
}
/*  End of main.                                                              */
