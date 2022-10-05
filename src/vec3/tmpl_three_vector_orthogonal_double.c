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
 *      Computes the cross product of two vectors.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Function for computing an orthogonal vector to the given input.           */
tmpl_ThreeVector
tmpl_3DDouble_Orthogonal(tmpl_ThreeVector P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVector out;

    /*  If the x component is zero, (1,0,0) will be orthogonal to P since the *
     *  dot product will be 1*0 + 0*Py + 0*Pz = 0. Return (1,0,0).            */
    if (P.dat[0] == 0.0)
    {
        out.dat[0] = 1.0;
        out.dat[1] = 0.0;
        out.dat[2] = 0.0;
    }
    else
    {
        /*  Similarly, if the y component is zero, return (0,1,0).            */
        if (P.dat[1] == 0.0)
        {
            out.dat[0] = 0.0;
            out.dat[1] = 1.0;
            out.dat[2] = 0.0;
        }

        /*  If both the x and y components are non-zero, we can set the       *
         *  output to (1, -Px/Py, 0), which is orthogonal to P.               */
        else
        {
            out.dat[0] = 1.0;
            out.dat[1] = -P.dat[0]/P.dat[1];
            out.dat[2] = 0.0;
        }
        /*  End of if (Py == 0.0).                                            */
    }
    /*  End of if (Px == 0.0).                                                */

    return out;
}
/*  End of tmpl_Orthogonal_ThreeVector.                                */
