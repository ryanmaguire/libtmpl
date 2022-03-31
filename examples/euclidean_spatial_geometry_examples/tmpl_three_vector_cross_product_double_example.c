/******************************************************************************
 *                                  LICENSE                                   *
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
 ******************************************************************************/

/*  3D data types and functions found here.                                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  printf found here.                                                        */
#include <stdio.h>

/*  Function for showing basic use of tmpl_3DDouble_Cross_Product.            */
int main(void)
{
    /*  Declare all necessary variables.                                      */
    const double x0 = 1.0;
    const double y0 = 2.0;
    const double z0 = 3.0;
    const double x1 = 4.0;
    const double y1 = 5.0;
    const double z1 = 6.0;

    /*  Create two vectors from the given real values above.                  */
    const tmpl_ThreeVector V0 = tmpl_3DDouble_Rect(x0, y0, z0);
    const tmpl_ThreeVector V1 = tmpl_3DDouble_Rect(x1, y1, z1);

    /*  Compute the cross product of V0 and V1.                               */
    const tmpl_ThreeVector cross = tmpl_3DDouble_Cross_Product(&V0, &V1);

    /*  Extract the components from the cross product.                        */
    const double xs = tmpl_3DDouble_X(&cross);
    const double ys = tmpl_3DDouble_Y(&cross);
    const double zs = tmpl_3DDouble_Z(&cross);

    /*  Print the result.                                                     */
    printf("   (%f, %f, %f) x\n   (%f, %f, %f)\n = (%f, %f, %f)\n",
           x0, y0, z0, x1, y1, z1, xs, ys, zs);
    return 0;
}
/*  End of main.                                                              */
