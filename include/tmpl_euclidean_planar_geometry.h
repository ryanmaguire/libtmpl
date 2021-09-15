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
 *  NOTE:                                                                     *
 *      A lot of the code comes from code I wrote for both rss_ringoccs, and  *
 *      for my vector graphics library KissVG. Many of the tools are being    *
 *      centralized to this project to save myself from maintaining repeat    *
 *      code.                                                                 *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
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
 *  2021/09/15: Ryan Maguire                                                  *
 *      Adding tools for working with planar polygons.                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EUCLIDEAN_PLANAR_GEOMETRY_H
#define TMPL_EUCLIDEAN_PLANAR_GEOMETRY_H

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Data types for two dimensional points at various precisions.              */
typedef struct _tmpl_FloatTwoVector {
    float dat[2];
} tmpl_FloatTwoVector;

typedef struct _tmpl_DoubleTwoVector {
    double dat[2];
} tmpl_DoubleTwoVector;

typedef struct _tmpl_LDoubleTwoVector {
    long double dat[2];
} tmpl_LDoubleTwoVector;

/*  For simplicity, TwoVector is typedef'd to double precision.               */
typedef tmpl_DoubleTwoVector tmpl_TwoVector;

/*  Data types for linear transformations of the plane.                       */
typedef struct _tmpl_FloatTwoByTwoMatrix {
    float dat[2][2];
} tmpl_FloatTwoByTwoMatrix;

typedef struct _tmpl_DoubleTwoByTwoMatrix {
    double dat[2][2];
} tmpl_DoubleTwoByTwoMatrix;

typedef struct _tmpl_LDoubleTwoByTwoMatrix {
    long double dat[2][2];
} tmpl_LDoubleTwoByTwoMatrix;

/*  Similarly, typedef TwoByTwoMatrix to double precision for simplicity.     */
typedef tmpl_DoubleTwoByTwoMatrix tmpl_TwoByTwoMatrix;

/*  A line segment is given by the start and end points.                      */
typedef struct _tmpl_FloatLineSegment2D {
    tmpl_FloatTwoVector dat[2];
} tmpl_FloatLineSegment2D;

typedef struct _tmpl_DoubleLineSegment2D {
    tmpl_DoubleTwoVector dat[2];
} tmpl_DoubleLineSegment2D;

typedef struct _tmpl_LDoubleLineSegment2D {
    tmpl_LDoubleTwoVector dat[2];
} tmpl_LDoubleLineSegment2D;

/*  Typedef LineSegment2D to double precision for simplicity.                 */
typedef tmpl_DoubleLineSegment2D tmpl_LineSegment2D;

/*  A line is given by a point on the line, and the direction. That is, we    *
 *  can write a(t) = P + tV.                                                  */
typedef struct tmpl_Line2D {
    tmpl_TwoVector P;
    tmpl_TwoVector V;
} tmpl_Line2D;

/*  Planar circles are represented by a point and a radius. Many functions    *
 *  allow circles to degenerate to straight lines. In this case the radius is *
 *  infinite, and the "center" instead becomes the line. To save memory, a    *
 *  union is used between the center and the line.                            */
typedef struct _tmpl_Circle2D {
    union Data {
        tmpl_TwoVector center;
        tmpl_Line2D line;
    } data;
    double radius;

    /*  Boolean for if the circle degenerated to a line.                      */
    tmpl_Bool is_line;

    /*  Boolean for keeping track of errors in computations. Most functions   *
     *  check this variable before doing anything.                            */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_Circle2D;

/*  A polygon is an array of points which represent the vertices of the       *
 *  polygon. There's no need for simple polygons, so a polygon with two       *
 *  points will be treated as a path from P to Q and then from Q to P.        */
typedef struct _tmpl_Polygon2D {
    tmpl_TwoVector *points;
    unsigned long int number_of_points;

    /*  Boolean for keeping track of errors in various computations.          */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_Polygon2D;

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
extern tmpl_FloatTwoByTwoMatrix
tmpl_Float_Rotation_Matrix2D(float theta);

extern tmpl_DoubleTwoByTwoMatrix
tmpl_Double_Rotation_Matrix2D(double theta);

extern tmpl_LDoubleTwoByTwoMatrix
tmpl_LDouble_Rotation_Matrix2D(long double theta);

#define tmpl_Rotation_Matrix2D tmpl_Double_Rotation_Matrix2D

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
 ******************************************************************************/
extern float
tmpl_FloatTwoByTwoMatrix_Component(tmpl_FloatTwoByTwoMatrix A,
                                   unsigned int m, unsigned int n);

extern double
tmpl_DoubleTwoByTwoMatrix_Component(tmpl_DoubleTwoByTwoMatrix A,
                                    unsigned int m, unsigned int n);

extern long double
tmpl_LDoubleTwoByTwoMatrix_Component(tmpl_LDoubleTwoByTwoMatrix A,
                                     unsigned int m, unsigned int n);

#define tmpl_TwoByTwoMatrix_Component tmpl_DoubleTwoByTwoMatrix_Component

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoByTwoMatrix_Determinant                                       *
 *  Purpose:                                                                  *
 *      Coomputes the determinant of a 2x2 matrix.                            *
 *  Arguments:                                                                *
 *      tmpl_TwoByTwoMatrix A:                                                *
 *          A 2x2 matrix.                                                     *
 *  Outputs:                                                                  *
 *      det (double):                                                         *
 *          The determinant of A.                                             *
 *  NOTE:                                                                     *
 *      Float and Long Double precisions are also provided.                   *
 ******************************************************************************/
extern float
tmpl_FloatTwoByTwoMatrix_Determinant(tmpl_FloatTwoByTwoMatrix A);

extern double
tmpl_DoubleTwoByTwoMatrix_Determinant(tmpl_DoubleTwoByTwoMatrix A);

extern long double
tmpl_LDoubleTwoByTwoMatrix_Determinant(tmpl_LDoubleTwoByTwoMatrix A);

#define tmpl_TwoByTwoMatrix_Determinant tmpl_DoubleTwoByTwoMatrix_Determinant

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
 *      tmpl_TwoByTwoMatrix_Inverse                                           *
 *  Purpose:                                                                  *
 *      Coomputes the inverse of a 2x2 matrix.                                *
 *  Arguments:                                                                *
 *      A (tmpl_TwoByTwoMatrix):                                              *
 *          A 2x2 matrix.                                                     *
 *  Outputs:                                                                  *
 *      inv_A (tmpl_TwoByTwoMatrix):                                          *
 *          The inverse of A.                                                 *
 *  NOTE:                                                                     *
 *      Float and Long Double precisions are also provided.                   *
 *      If A is not invertible (i.e. a singular matrix), the output has all   *
 *      entries set to NaN (Not-A-Number). This appropriate since a           *
 *      divide-by-zero results when one tries to invert a singular matrix.    *
 ******************************************************************************/
extern tmpl_FloatTwoByTwoMatrix
tmpl_FloatTwoByTwoMatrix_Inverse(tmpl_FloatTwoByTwoMatrix A);

extern tmpl_DoubleTwoByTwoMatrix
tmpl_DoubleTwoByTwoMatrix_Inverse(tmpl_DoubleTwoByTwoMatrix A);

extern tmpl_LDoubleTwoByTwoMatrix
tmpl_LDoubleTwoByTwoMatrix_Inverse(tmpl_LDoubleTwoByTwoMatrix A);

#define tmpl_TwoByTwoMatrix_Inverse tmpl_DoubleTwoByTwoMatrix_Inverse

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoByTwoMatrix_New                                               *
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
extern tmpl_FloatTwoByTwoMatrix
tmpl_FloatTwoByTwoMatrix_New(float a, float b, float c, float d);

extern tmpl_DoubleTwoByTwoMatrix
tmpl_DoubleTwoByTwoMatrix_New(double a, double b, double c, double d);

extern tmpl_LDoubleTwoByTwoMatrix
tmpl_LDoubleTwoByTwoMatrix_New(long double a, long double b,
                               long double c, long double d);

#define tmpl_TwoByTwoMatrix_New tmpl_DoubleTwoByTwoMatrix_New

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
extern tmpl_FloatTwoByTwoMatrix
tmpl_FloatTwoByTwoMatrix_Scale(float r, tmpl_FloatTwoByTwoMatrix P);

extern tmpl_DoubleTwoByTwoMatrix
tmpl_DoubleTwoByTwoMatrix_Scale(double r, tmpl_DoubleTwoByTwoMatrix P);

extern tmpl_LDoubleTwoByTwoMatrix
tmpl_LDoubleTwoByTwoMatrix_Scale(long double r, tmpl_LDoubleTwoByTwoMatrix P);

#define tmpl_TwoByTwoMatrix_Scale tmpl_DoubleTwoByTwoMatrix_Scale

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
extern tmpl_FloatTwoVector
tmpl_FloatTwoVector_Add(tmpl_FloatTwoVector P, tmpl_FloatTwoVector Q);

extern tmpl_DoubleTwoVector
tmpl_DoubleTwoVector_Add(tmpl_DoubleTwoVector P, tmpl_DoubleTwoVector Q);

extern tmpl_LDoubleTwoVector
tmpl_LDoubleTwoVector_Add(tmpl_LDoubleTwoVector P, tmpl_LDoubleTwoVector Q);

#define tmpl_TwoVector_Add tmpl_DoubleTwoVector

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
extern float
tmpl_FloatTwoVector_Dot_Product(tmpl_FloatTwoVector P, tmpl_FloatTwoVector Q);

extern double
tmpl_DoubleTwoVector_Dot_Product(tmpl_DoubleTwoVector P,
                                 tmpl_DoubleTwoVector Q);

extern long double
tmpl_LDoubleTwoVector_Dot_Product(tmpl_LDoubleTwoVector P,
                                  tmpl_LDoubleTwoVector Q);

#define tmpl_TwoVector_Dot_Product tmpl_DoubleTwoVector_Dot_Product

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Euclidean_Orthogonal                                   *
 *  Purpose:                                                                  *
 *      Compute a vector which is orthogonal to the input.                    *
 *  Arguments:                                                                *
 *      tmpl_TwoVector v:                                                     *
 *          A 2D vector.                                                      *
 *  Outputs:                                                                  *
 *      tmpl_TwoVector orth:                                                  *
 *          A vector orthogonal to v.                                         *
 *  NOTE:                                                                     *
 *      Float and Long Double precisions are also provided.                   *
 ******************************************************************************/
extern tmpl_FloatTwoVector
tmpl_FloatTwoVector_Euclidean_Orthogonal(tmpl_FloatTwoVector v);

extern tmpl_DoubleTwoVector
tmpl_DoubleTwoVector_Euclidean_Orthogonal(tmpl_DoubleTwoVector v);

extern tmpl_LDoubleTwoVector
tmpl_LDoubleTwoVector_Euclidean_Orthogonal(tmpl_LDoubleTwoVector v);

#define tmpl_TwoVector_Euclidean_Orthogonal \
        tmpl_DoubleTwoVector_Euclidean_Orthogonal


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
extern tmpl_FloatTwoVector
tmpl_FloatTwoVector_Rect(float x, float y);

extern tmpl_DoubleTwoVector
tmpl_DoubleTwoVector_Rect(double x, double y);

extern tmpl_LDoubleTwoVector
tmpl_LDoubleTwoVector_Rect(long double x, long double y);

#define tmpl_TwoVector_Rect tmpl_DoubleTwoVector_Rect

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
extern float tmpl_FloatTwoVector_X(tmpl_FloatTwoVector P);
extern double tmpl_DoubleTwoVector_X(tmpl_DoubleTwoVector P);
extern long double tmpl_LDoubleTwoVector_X(tmpl_LDoubleTwoVector P);
#define tmpl_TwoVector_X tmpl_DoubleTwoVector_X

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
extern float tmpl_FloatTwoVector_Y(tmpl_FloatTwoVector P);
extern double tmpl_DoubleTwoVector_Y(tmpl_DoubleTwoVector P);
extern long double tmpl_LDoubleTwoVector_Y(tmpl_LDoubleTwoVector P);
#define tmpl_TwoVector_Y tmpl_DoubleTwoVector_Y

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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_TwoVector_Euclidean_Is_Collinear                                 *
 *  Purpose:                                                                  *
 *      Determine if three tmpl_TwoVector's are collinear.                    *
 *  Arguments:                                                                *
 *      tmpl_TwoVector A:                                                     *
 *          A kissvg_TwoVector.                                               *
 *      tmpl_TwoVector B:                                                     *
 *          Another vector.                                                   *
 *      tmpl_TwoVector C:                                                     *
 *          A third vector.                                                   *
 *  Outputs:                                                                  *
 *      tmpl_Bool is_collinear:                                               *
 *          A Boolean that is true if A, B, and C are collinear, and false    *
 *          otherwise.                                                        *
 ******************************************************************************/
extern tmpl_Bool
tmpl_TwoVector_Euclidean_Is_Collinear(tmpl_TwoVector A,
                                      tmpl_TwoVector B,
                                      tmpl_TwoVector C);

extern double
tmpl_TwoVector_Euclidean_Distance(tmpl_TwoVector A, tmpl_TwoVector B);


extern tmpl_Bool
tmpl_LineSegment2D_Intersect(tmpl_LineSegment2D L0, tmpl_LineSegment2D L1);

#endif
/*  End of include guard.                                                     */
