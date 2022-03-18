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
 ******************************************************************************
 *                        tmpl_three_vector_add_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for performing vector addition at long double precision.*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Add                                                    *
 *  Purpose:                                                                  *
 *      Computes the vector sum of two vectors at long double precision.      *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble *):                               *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorLongDouble *):                               *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      sum (tmpl_ThreeVectorLongDouble):                                     *
 *          The vector sum P+Q.                                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of vector addition. If P = (Px, Py, Pz) and        *
 *      Q = (Qx, Qy, Qz), then the vector sum P+Q has coordinates:            *
 *          x = Px + Qx                                                       *
 *          y = Py + Qy                                                       *
 *          z = Pz + Qz                                                       *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *                                                                            *
 *      The macro tmpl_3D_Addl is an alias for this function.                 *
 *                                                                            *
 *      A 7% to 50% increase in performance was found (pending hardware and   *
 *      compiler used) by passing tmpl_ThreeVectorLongDouble's by reference   *
 *      instead of by value.                                                  *
 *                                                                            *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_euclidean_spatial_geometry.h:                                    *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *                             A NOTE ON COMMENTS                             *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                             A FRIENDLY WARNING                             *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/02: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 *  2022/03/17: Ryan Maguire                                                  *
 *      Changed function to pass by reference instead of by value.            *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Function for adding 2 three-dimensional vectors.                          */
tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Add(const tmpl_ThreeVectorLongDouble *P,
                   const tmpl_ThreeVectorLongDouble *Q)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVectorLongDouble sum;

    /*  The sum of two vectors simply adds their components together.         */
    sum.dat[0] = P->dat[0] + Q->dat[0];
    sum.dat[1] = P->dat[1] + Q->dat[1];
    sum.dat[2] = P->dat[2] + Q->dat[2];
    return sum;
}
/*  End of tmpl_3DLDouble_Add.                                                */
