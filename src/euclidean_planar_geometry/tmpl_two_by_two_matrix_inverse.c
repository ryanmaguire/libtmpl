/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
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
 *                     tmpl_two_by_two_matrix_inverse                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the inverse of a 2x2 matrix.                                 *
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
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 28, 2020                                            *
 ******************************************************************************/

/*  NaN found here.                                                           */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>

/*  Machine precision found here.                                             */
#include <float.h>

/*  Function for computing the inverse of a 2x2 matrix.                       */
tmpl_FloatTwoByTwoMatrix
tmpl_FloatTwoByTwoMatrix_Inverse(tmpl_FloatTwoByTwoMatrix A)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float ainv, binv, cinv, dinv, det_rcp;

    /*  Extract the components from the matrix.                               */
    const float a = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 0);
    const float b = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 1);
    const float c = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 0);
    const float d = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 1);

    /*  Compute the determinant.                                              */
    const float det = a*c - b*d;

    /*  If the determinant is epsilon-small, avoid division with this. Treat  *
     *  it as division by zero and return NaN (not-a-number).                 */
    if ((det < FLT_MIN) && (det > -FLT_MIN))
    {
        ainv = TMPL_NANF;
        binv = TMPL_NANF;
        cinv = TMPL_NANF;
        dinv = TMPL_NANF;
    }

    /*  Otherwise, use the inverse formula for 2x2 matrices.                  */
    else
    {
        det_rcp = 1.0F/det;
        ainv = d*det_rcp;
        binv = -b*det_rcp;
        cinv = -c*det_rcp;
        dinv = a*det_rcp;
    }

    /*  Create the output matrix with tmpl_DoubleTwoByTwoMatrix_New.          */
    return tmpl_FloatTwoByTwoMatrix_New(ainv, binv, cinv, dinv);
}
/*  End of tmpl_FloatTwoByTwoMatrix_Inverse.                                  */

/*  Function for computing the inverse of a 2x2 matrix.                       */
tmpl_DoubleTwoByTwoMatrix
tmpl_DoubleTwoByTwoMatrix_Inverse(tmpl_DoubleTwoByTwoMatrix A)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double ainv, binv, cinv, dinv, det_rcp;

    /*  Extract the components from the matrix.                               */
    const double a = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 0);
    const double b = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 1);
    const double c = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 0);
    const double d = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 1);

    /*  Compute the determinant.                                              */
    const double det = a*c - b*d;

    /*  If the determinant is epsilon-small, avoid division with this. Treat  *
     *  it as division by zero and return NaN (not-a-number).                 */
    if ((det < DBL_MIN) && (det > -DBL_MIN))
    {
        ainv = TMPL_NAN;
        binv = TMPL_NAN;
        cinv = TMPL_NAN;
        dinv = TMPL_NAN;
    }

    /*  Otherwise, use the inverse formula for 2x2 matrices.                  */
    else
    {
        det_rcp = 1.0/det;
        ainv = d*det_rcp;
        binv = -b*det_rcp;
        cinv = -c*det_rcp;
        dinv = a*det_rcp;
    }

    /*  Create the output matrix with tmpl_DoubleTwoByTwoMatrix_New.          */
    return tmpl_DoubleTwoByTwoMatrix_New(ainv, binv, cinv, dinv);
}
/*  End of tmpl_DoubleTwoByTwoMatrix_Inverse.                                 */

/*  Function for computing the inverse of a 2x2 matrix.                       */
tmpl_LDoubleTwoByTwoMatrix
tmpl_LDoubleTwoByTwoMatrix_Inverse(tmpl_LDoubleTwoByTwoMatrix A)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double ainv, binv, cinv, dinv, det_rcp;

    /*  Extract the components from the matrix.                               */
    const long double a = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 0);
    const long double b = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 1);
    const long double c = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 0);
    const long double d = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 1);

    /*  Compute the determinant.                                              */
    const long double det = a*c - b*d;

    /*  If the determinant is epsilon-small, avoid division with this. Treat  *
     *  it as division by zero and return NaN (not-a-number).                 */
    if ((det < LDBL_MIN) && (det > -LDBL_MIN))
    {
        ainv = TMPL_NANL;
        binv = TMPL_NANL;
        cinv = TMPL_NANL;
        dinv = TMPL_NANL;
    }

    /*  Otherwise, use the inverse formula for 2x2 matrices.                  */
    else
    {
        det_rcp = 1.0L/det;
        ainv = d*det_rcp;
        binv = -b*det_rcp;
        cinv = -c*det_rcp;
        dinv = a*det_rcp;
    }

    /*  Create the output matrix with tmpl_DoubleTwoByTwoMatrix_New.          */
    return tmpl_LDoubleTwoByTwoMatrix_New(ainv, binv, cinv, dinv);
}
/*  End of tmpl_LDoubleTwoByTwoMatrix_Inverse.                                */
