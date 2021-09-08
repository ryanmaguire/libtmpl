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
 *                            tmpl_two_vector_add                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Source code for computing the vector sum of two points in the plane.  *
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
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/21: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

/*  TMPL_NAN defined here.                                                    */
#include <libtmpl/include/tmpl_math.h>
#include <math.h>

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>

/*  Function for computing the angle between the lines OP and OQ given three  *
 *  tmpl_TwoVector's O, P, and Q.                                             */
double tmpl_TwoVector_Euclidean_Rel_Angle(tmpl_TwoVector O, tmpl_TwoVector P,
                                          tmpl_TwoVector Q)
{
    /*  Declare all necessary variables.                                      */
    double dot_prod;
    double abs_prod;
    double rel_angle;

    /*  We need to compute the vector from O to P and O to Q so declare these.*/
    tmpl_TwoVector OP;
    tmpl_TwoVector OQ;

    /*  Compute the vector pointing from O to P, which is simply P-O. Do the  *
     *  same thing for O and Q.                                               */
    OP = tmpl_TwoVector_Subtract(P, O);
    OQ = tmpl_TwoVector_Subtract(Q, O);

    /*  The angle formula is arccos(a dot b / norm(a)norm(b)). First we'll    *
     *  compute the dot product, then check that norm(a)norm(b) is non-zero.  */
    dot_prod = tmpl_TwoVector_Dot_Product(OP, OQ);

    /*  abs_prod represents the quantity ||OP|| * ||OQ||.                     */
    abs_prod = tmpl_TwoVector_Euclidean_Norm(OP) *
               tmpl_TwoVector_Euclidean_Norm(OQ);

    /*  If norm(OP)norm(OQ) is zero, then one of these vectors is the zero    *
     *  vector, meaning the angle is undefined. We then return Not-A-Number.  */
    if (abs_prod == 0.0)
        rel_angle = TMPL_NAN;

    /*  If norm(OP)norm(OQ) is non-zero, we may use the angle formula.        */
    else
        rel_angle = acos(dot_prod/abs_prod);

    return rel_angle;
}
/*  End of tmpl_TwoVector_Euclidean_Rel_Angle.                                */

