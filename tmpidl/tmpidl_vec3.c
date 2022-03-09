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
 *                                 tmpidl_math                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide the 3D geometry sublibrary of libtmpl for IDL users.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 9, 2022                                                 *
 ******************************************************************************/

/*  Geometry routines found here.                                             */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  IDL's ULONG is 32-bits. Use stdint for portability.                       */
#include <stdint.h>

extern void tmpidl_Vec3_Norm(int argc, void *argv[]);

/*  Function for computing the 3D Euclidean norm of a 2D array.               */
void tmpidl_Vec2_Norm(int argc, void *argv[])
{
    /*  Pointers for the input and output data.                               */
    tmpl_ThreeVector *in;
    double *out;

    /*  Variable for indexing and for the total number of elements            */
    uint32_t n, size;

    /*  We're expecting 3 inputs from IDL.                                    */
    if (argc != 3)
        return;

    /*  Extract the data.                                                     */
    in = (tmpl_ThreeVector *)argv[0];
    size = *(uint32_t *)argv[1];
    out = (double *)argv[2];

    /*  Loop through the data and perform the computation.                    */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0UL; n < size; ++n)
        out[n] = tmpl_3DDouble_Norm(in[n]);
}
/*  End of tmpidl_Vec2_Norm.                                                  */
