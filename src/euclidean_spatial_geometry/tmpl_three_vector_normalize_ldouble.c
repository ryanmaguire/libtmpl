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
 *                     tmpl_three_vector_normalize_ldouble                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing unit normal vectors.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Normalize                                              *
 *  Purpose:                                                                  *
 *      Computes the unit normal of the input non-zero vector.                *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorLongDouble):                                       *
 *          A non-zero vector in R^3.                                         *
 *  Output:                                                                   *
 *      P_hat (tmpl_ThreeVectorLongDouble):                                   *
 *          The unit normal of P.                                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of unit normal. If P = (x, y, z), the norm is:     *
 *                                                                            *
 *          norm = sqrt(x^2 + y^2 + z^2).                                     *
 *                                                                            *
 *      For a non-zero vector norm is positive. The unit normal is given by:  *
 *                                                                            *
 *          P_hat = P / norm                                                  *
 *                                                                            *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *                                                                            *
 *      If the vector is zero, (NaN, NaN, NaN) is returned.                   *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_euclidean_spatial_geometry.h:                                    *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
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
 *                             Revision History                               *
 ******************************************************************************
 *  2022/03/02: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  NaN is defined here.                                                      */
#include <libtmpl/include/tmpl_math.h>

/*  Function that normalizes non-zero three dimensional vectors.              */
tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Normalize(tmpl_ThreeVectorLongDouble P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double rcpr_norm;
    tmpl_ThreeVectorLongDouble P_normalized;

    /*  Get the norm of the input vector P.                                   */
    const long double norm = tmpl_3DLDouble_L2_Norm(&P);

    /*  If the norm is zero we cannot normalize. Return NaN in this case.     */
    if (norm == 0.0L)
    {
        P_normalized.dat[0] = TMPL_NANL;
        P_normalized.dat[1] = TMPL_NANL;
        P_normalized.dat[2] = TMPL_NANL;
    }
    else
    {
        /*  Compute the reciprocal of the norm. Precomputing a division and   *
         *  using multiplication later is faster than repeated division.      */
        rcpr_norm = 1.0L / norm;

        /*  Compute the components of the normalized vector.                  */
        P_normalized.dat[0] = P.dat[0]*rcpr_norm;
        P_normalized.dat[0] = P.dat[0]*rcpr_norm;
        P_normalized.dat[0] = P.dat[0]*rcpr_norm;
    }
    /*  End of if (norm == 0.0).                                              */

    return P_normalized;
}
/*  End of tmpl_3DDouble_Normalize.                                           */
