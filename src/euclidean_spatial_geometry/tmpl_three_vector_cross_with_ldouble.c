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
 *                    tmpl_three_vector_cross_with_ldouble                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the Euclidean cross product of vectors    *
 *      in R^3 at long double precision.                                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_CrossWith                                              *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors at long double precision.   *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorLongDouble *):                                *
 *          A pointer to a vector in R^3. The product is stored here.         *
 *      source (const tmpl_ThreeVectorLongDouble *):                          *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of the cross product. If P = (Px, Py, Pz) and      *
 *      Q = (Qx, Qy, Qz), then the cross product PxQ has coordinates:         *
 *          x = PyQz - PzQy                                                   *
 *          y = PzQx - PxQz                                                   *
 *          z = PxQy - PyQx                                                   *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *                                                                            *
 *      The cross product is not commutative, but anti-commutative. That is,  *
 *      PxQ = -QxP. The order of P and Q matters for this function.           *
 *                                                                            *
 *      If tmpl_3DLDouble_Cross_Product is the equivalent of the "x" operator *
 *      for the tmpl_ThreeVectoLongrDouble struct, this is the equivalent of  *
 *      "x=". It is about 3x faster to do tmpl_3DLDouble_CrossWith(&P, &Q)    *
 *      instead of doing P = tmpl_3DLDouble_Cross_Product(&P, &Q).            *
 *                                                                            *
 *      The macro tmpl_CrossWithl is an alias for this function.              *
 *                                                                            *
 *      No checks for NULL pointers are performed.                            *
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
 *  Date:       March 18, 2022                                                *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Function for computing the cross product of vectors at double precision.  */
void
tmpl_3DLDouble_CrossWith(tmpl_ThreeVectorLongDouble *target,
                         const tmpl_ThreeVectorLongDouble *source)
{
    /*  Declare temporary variables for the x and y components of target.     */
    const long double x = target->dat[0];
    const long double y = target->dat[1];

    /*  Compute the components of the cross product PxQ.                      */
    target->dat[0] = y*source->dat[2] - target->dat[2]*source->dat[1];
    target->dat[1] = target->dat[2]*source->dat[0] - x*source->dat[2];
    target->dat[2] = x*source->dat[1] - y*source->dat[0];
}
/*  End of tmpl_3DLDouble_CrossWith.                                          */
