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
 *                       tmpl_euclidean_planar_geometry                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Define data types for two dimensional Euclidean geometry, and give    *
 *      the prototypes for useful functions in planar geometry.               *
 *                                                                            *
 *  NOTES:                                                                    *
 *      A lot of the code comes from code I wrote for both rss_ringoccs, and  *
 *      for my vector graphics library KissVG. Many of the tools are being    *
 *      centralized to this project to save myself from maintaining repeat    *
 *      code.                                                                 *
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
 *  2020/09/20: Ryan Maguire                                                  *
 *      Created file (KissVG).                                                *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EUCLIDEAN_PLANAR_GEOMETRY_H
#define TMPL_EUCLIDEAN_PLANAR_GEOMETRY_H

#include <libtmpl/include/tmpl_bool.h>

/*  Data types for two dimensional points and transformations, respectively.  */
typedef struct tmpl_TwoVector {
    double dat[2];
} tmpl_TwoVector;

typedef struct tmpl_TwoByTwoMatrix {
    double dat[2][2];
} tmpl_TwoByTwoMatrix;

typedef struct tmpl_Line2D {
    tmpl_TwoVector P;
    tmpl_TwoVector V;
} tmpl_Line2D;

typedef struct tmpl_Circle2D {
    union Data {
        tmpl_TwoVector center;
        tmpl_Line2D line;
    } data;
    double radius;
    tmpl_Bool is_line;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_Circle2D;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_GET_2x2_MATRIX_COMPONENT                                         *
 *  Purpose:                                                                  *
 *      Returns the (m,n) element of a 2x2 matrix.                            *
 *  Arguments:                                                                *
 *      tmpl_TwoByTwoMatrix A:                                                *
 *          A 2x2 matrix.                                                     *
 *      int m:                                                                *
 *          The first index of the element.                                   *
 *      int n:                                                                *
 *          The second index of the element.                                  *
 *  Outputs:                                                                  *
 *      double out:                                                           *
 *          The (m,n) component of the tmpl_TwoByTwoMatrix                    *
 *  Note:                                                                     *
 *      This is not a function, but rather a preprocessor macro.              *
 ******************************************************************************/
#define tmpl_GET_2x2_MATRIX_COMPONENT(A, m, n) (A.dat[m][n])

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoByTwoMatrix_Component                                         *
 *  Purpose:                                                                  *
 *      Returns the (m,n) element of a 2x2 matrix.                            *
 *  Arguments:                                                                *
 *      tmpl_TwoByTwoMatrix A:                                                *
 *          A 2x2 matrix.                                                     *
 *      int m:                                                                *
 *          The first index of the element.                                   *
 *      int n:                                                                *
 *          The second index of the element.                                  *
 *  Outputs:                                                                  *
 *      double out:                                                           *
 *          The (m,n) component of the tmpl_TwoByTwoMatrix                    *
 *  Note:                                                                     *
 *      This is not a function, but rather a preprocessor macro.              *
 ******************************************************************************/
extern double
tmpl_TwoByTwoMatrix_Component(tmpl_TwoByTwoMatrix A,
                              unsigned int m, unsigned int n);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_New_TwoByTwoMatrix                                               *
 *  Purpose:                                                                  *
 *      Create a new tmpl_TwoByTwoMatrix from four doubles. This returns:     *
 *           -       -                                                        *
 *          |  a   b  |                                                       *
 *          |  c   d  |                                                       *
 *           -       -                                                        *
 *  Arguments:                                                                *
 *      double a:                                                             *
 *      double b:                                                             *
 *      double c:                                                             *
 *      double d:                                                             *
 *  Outputs:                                                                  *
 *      tmpl_TwoByTwoMatrix:                                                  *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern tmpl_TwoByTwoMatrix
tmpl_TwoByTwoMatrix_New(double a, double b, double c, double d);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Matrix_Transform                                       *
 *  Purpose:                                                                  *
 *      Given a matrix A and a vector P, computes AP.                         *
 *  Arguments:                                                                *
 *      tmpl_TwoByTwoMatrix A:                                                *
 *          A 2x2 matrix.                                                     *
 *      tmpl_TwoVector P:                                                     *
 *          A two element vector.                                             *
 *  Outputs:                                                                  *
 *      tmpl_TwoVector out:                                                   *
 *          The vector P transformed by A.                                    *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern tmpl_TwoVector
tmpl_TwoVector_Matrix_Transform(tmpl_TwoByTwoMatrix A, tmpl_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Rotation_Matrix_2D                                               *
 *  Purpose:                                                                  *
 *      Returns the rotation matrix corresponding to the angle theta.         *
 *  Arguments:                                                                *
 *      double theta:                                                         *
 *          A real number, the angle to rotate by.                            *
 *  Outputs:                                                                  *
 *      tmpl_TwoByTwoMatrix R:                                                *
 *          The rotation matrix.                                              *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern tmpl_TwoByTwoMatrix tmpl_Rotation_Matrix_2D(double theta);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoByTwoMatrix_Scale                                             *
 *  Purpose:                                                                  *
 *      Returns the rotation matrix corresponding to the angle theta.         *
 *  Arguments:                                                                *
 *      double theta:                                                         *
 *          A real number, the angle to rotate by.                            *
 *  Outputs:                                                                  *
 *      tmpl_TwoByTwoMatrix R:                                                *
 *          The rotation matrix.                                              *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern tmpl_TwoByTwoMatrix
tmpl_TwoByTwoMatrix_Scale(double r, tmpl_TwoByTwoMatrix P);

extern double tmpl_TwoByTwoMatrix_Determinant(tmpl_TwoByTwoMatrix A);

extern tmpl_TwoByTwoMatrix tmpl_TwoByTwoMatrix_Inverse(tmpl_TwoByTwoMatrix A);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Euclidean_Midpoint                                     *
 *  Purpose:                                                                  *
 *      Compute the midpoint of two tmpl_TwoVector's.                         *
 *  Arguments:                                                                *
 *      tmpl_TwoVector P:                                                     *
 *          An arbitrary tmpl_TwoVector.                                      *
 *      tmpl_TwoVector Q:                                                     *
 *          Another vector.                                                   *
 *  Outputs:                                                                  *
 *      tmpl_TwoVector mid:                                                   *
 *          The midpoint of P and Q, defined to be (P + Q) / 2.               *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern tmpl_TwoVector
tmpl_TwoVector_Euclidean_Midpoint(tmpl_TwoVector P, tmpl_TwoVector Q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Rect                                                   *
 *  Purpose:                                                                  *
 *      Create a new tmpl_TwoVector from two doubles, the x component and     *
 *      the y. This is the main function for defining tmpl_TwoVector's.       *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          The x component of the desired vector.                            *
 *      double y:                                                             *
 *          The y component of the desired vector.                            *
 *  Outputs:                                                                  *
 *      tmpl_TwoVector:                                                       *
 *          An instance of the tmpl_TwoVector structure with zeroth entry     *
 *          set to x and first entry set to y. This is mathematically         *
 *          equivalent to the vector (x, y).                                  *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern tmpl_TwoVector tmpl_TwoVector_Rect(double x, double y);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_X                                                      *
 *  Purpose:                                                                  *
 *      Returns the x component of a tmpl_TwoVector. This is equivalent to    *
 *      the mathematical concept of projecting a vector along the y-axis.     *
 *  Arguments:                                                                *
 *      tmpl_TwoVector P:                                                     *
 *  Outputs:                                                                  *
 *      double x:                                                             *
 *          The x component of the tmpl_TwoVector P. If we represent P by     *
 *          (x, y), this is equivalent to returning x.                        *
 *  Note:                                                                     *
 *      This is not a function, but rather a preprocessor macro.              *
 ******************************************************************************/
extern double tmpl_TwoVector_X(tmpl_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Y                                                      *
 *  Purpose:                                                                  *
 *      Returns the y component of a tmpl_TwoVector. This is equivalent to    *
 *      the mathematical concept of projecting a vector along the x-axis.     *
 *  Arguments:                                                                *
 *      tmpl_TwoVector P:                                                     *
 *  Outputs:                                                                  *
 *      double y:                                                             *
 *          The y component of the tmpl_TwoVector P. If we represent P by     *
 *          (x, y), this is equivalent to returning y.                        *
 *  Note:                                                                     *
 *      This is not a function, but rather a preprocessor macro.              *
 ******************************************************************************/
extern double tmpl_TwoVector_Y(tmpl_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Add                                                    *
 *  Purpose:                                                                  *
 *      Given two tmpl_TwoVector's, compute the vector sum of them.           *
 *  Arguments:                                                                *
 *      tmpl_TwoVector P:                                                     *
 *          An arbitrary tmpl_TwoVector.                                      *
 *      tmpl_TwoVector Q:                                                     *
 *          The vector we wish to add to P.                                   *
 *  Outputs:                                                                  *
 *      tmpl_TwoVector sum:                                                   *
 *          The vector sum P+Q.                                               *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern tmpl_TwoVector tmpl_TwoVector_Add(tmpl_TwoVector P, tmpl_TwoVector Q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Subtract                                               *
 *  Purpose:                                                                  *
 *      Given two tmpl_TwoVector's P and Q, compute P-Q.                      *
 *  Arguments:                                                                *
 *      tmpl_TwoVector P:                                                     *
 *          An arbitrary tmpl_TwoVector.                                      *
 *      tmpl_TwoVector Q:                                                     *
 *          The vector we wish to subtract from P.                            *
 *  Outputs:                                                                  *
 *      tmpl_TwoVector sum:                                                   *
 *          The vector subtraction P-Q.                                       *
 *  NOTE:                                                                     *
 *      Unlike tmpl_TwoVectorAdd, the order of the inputs for                 *
 *      tmpl_TwoVectorSubtract matters. This routine compute P - Q, and not   *
 *      Q - P. That is, we subtract the second argument from the first one.   *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern tmpl_TwoVector
tmpl_TwoVector_Subtract(tmpl_TwoVector P, tmpl_TwoVector Q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Scale                                                  *
 *  Purpose:                                                                  *
 *      Scale a vector P by a scalar (real number) r.                         *
 *  Arguments:                                                                *
 *      double r:                                                             *
 *          An arbitrary real number.                                         *
 *      tmpl_TwoVector P:                                                     *
 *          The vector we wish to scale by r.                                 *
 *  Outputs:                                                                  *
 *      tmpl_TwoVector rP:                                                    *
 *          The vector P multiplied by r.                                     *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern tmpl_TwoVector tmpl_TwoVector_Scale(double r, tmpl_TwoVector P);

extern tmpl_TwoVector tmpl_TwoVector_Polar(double r, double theta);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Euclidean_Norm                                         *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm of a tmpl_TwoVector.                      *
 *  Arguments:                                                                *
 *      tmpl_TwoVector P:                                                     *
 *          An arbitrary tmpl_TwoVector.                                      *
 *  Outputs:                                                                  *
 *      double norm:                                                          *
 *          The Euclidean norm of P. If we represent P by (x, y), norm is     *
 *          defined by norm = sqrt(x^2 + y^2).                                *
 *  Source Code:                                                              *
 *      src/euclidean_planar_geometry/tmpl_two_vector_euclidean_norm.c        *
 ******************************************************************************/
extern double tmpl_TwoVector_Euclidean_Norm(tmpl_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Euclidean_Norm_Squared                                 *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm squared of a tmpl_TwoVector.              *
 *  Arguments:                                                                *
 *      tmpl_TwoVector P:                                                     *
 *          An arbitrary tmpl_TwoVector.                                      *
 *  Outputs:                                                                  *
 *      double norm:                                                          *
 *          The square of the Euclidean norm of P. If we represent P by       *
 *          (x, y), this is defined by norm^2 = x^2 + y^2.                    *
 *  Source Code:                                                              *
 *      src/euclidean_planar_geometry/tmpl_two_vector_euclidean_norm_squared.c*
 ******************************************************************************/
extern double tmpl_TwoVector_Euclidean_Norm_Squared(tmpl_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Dot_Product                                            *
 *  Purpose:                                                                  *
 *      Compute the Euclidean dot product of two 2D vectors.                  *
 *  Arguments:                                                                *
 *      tmpl_TwoVector P:                                                     *
 *          A 2D vector.                                                      *
 *      tmpl_TwoVector Q:                                                     *
 *          Another 2D vector.                                                *
 *  Outputs:                                                                  *
 *      double dot_prod:                                                      *
 *          The dot product of P and Q.                                       *
 *  Source Code:                                                              *
 *      src/euclidean_planar_geometry/tmpl_two_vector_dot_product.c           *
 ******************************************************************************/
extern double tmpl_TwoVector_Dot_Product(tmpl_TwoVector P, tmpl_TwoVector Q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Normalize                                              *
 *  Purpose:                                                                  *
 *      Compute the Euclidean dot product of two 2D vectors.                  *
 *  Arguments:                                                                *
 *      tmpl_TwoVector P:                                                     *
 *          A 2D vector.                                                      *
 *  Outputs:                                                                  *
 *      tmpl_TwoVector P_hat:                                                 *
 *          A vector of length 1 in the same direction of P.                  *
 *  NOTES:                                                                    *
 *      If P is the zero vector P = (0, 0), this function returns (NaN, NaN). *
 ******************************************************************************/
extern tmpl_TwoVector tmpl_TwoVector_Normalize(tmpl_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Euclidean_Rel_Angle                                    *
 *  Purpose:                                                                  *
 *      Compute the angle between P and Q with respect to the point O.        *
 *                                                                            *
 *     y^                                                                     *
 *      |                           Q *                                       *
 *      |                            /                                        *
 *      |                           /                                         *
 *      |                          /                                          *
 *      |                         /                                           *
 *      |                        /__                                          *
 *      |                       /    \  Theta                                 *
 *      |                      /      |                                       *
 *      |                     *----------------*                              *
 *      |                     O                P                              *
 *      |                                                                     *
 *      |                                                                     *
 *     -|-------------------------------------------------->                  *
 *                                                         x                  *
 *  Arguments:                                                                *
 *      tmpl_TwoVector O:                                                     *
 *          The vector we wish to view P and Q with respect to.               *
 *      tmpl_TwoVector P:                                                     *
 *          An arbitrary tmpl_TwoVector.                                      *
 *      tmpl_TwoVector Q:                                                     *
 *          Another vector.                                                   *
 *  Outputs:                                                                  *
 *      double angle:                                                         *
 *          The angle between P and Q relative to O.                          *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern double
tmpl_TwoVector_Euclidean_Rel_Angle(tmpl_TwoVector O, tmpl_TwoVector P,
                                   tmpl_TwoVector Q);

extern tmpl_Bool
tmpl_TwoVector_Euclidean_Is_Collinear(tmpl_TwoVector A,
                                      tmpl_TwoVector B,
                                      tmpl_TwoVector C);

extern double
tmpl_TwoVector_Euclidean_Distance(tmpl_TwoVector A, tmpl_TwoVector B);

#endif
/*  End of include guard.                                                     */
