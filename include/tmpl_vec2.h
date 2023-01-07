/******************************************************************************
 *                                  LICENSE                                   *
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
 *                                 tmpl_vec2                                  *
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
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/09/20: Ryan Maguire                                                  *
 *      Created file (KissVG).                                                *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2021/09/15: Ryan Maguire                                                  *
 *      Adding tools for working with planar polygons.                        *
 *  2022/12/30: Ryan Maguire                                                  *
 *      Changed naming convention to match vec3 and complex. Changed          *
 *      functions to pass by address instead of value. More reorganizing.     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_H
#define TMPL_VEC2_H

/*  size_t type given here.                                                   */
#include <stddef.h>

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

#include <libtmpl/include/tmpl_config.h>

/*  Data types for two dimensional points at various precisions.              */
typedef struct tmpl_TwoVectorFloat_Def {
    float dat[2];
} tmpl_TwoVectorFloat;

typedef struct tmpl_TwoVectorDouble_Def {
    double dat[2];
} tmpl_TwoVectorDouble;

typedef struct tmpl_TwoVectorLongDouble_Def {
    long double dat[2];
} tmpl_TwoVectorLongDouble;

/*  For simplicity, TwoVector is typedef'd to double precision.               */
typedef tmpl_TwoVectorDouble tmpl_TwoVector;

/*  Data types for linear transformations of the plane.                       */
typedef struct tmpl_TwoByTwoMatrixFloat_Def {
    float dat[2][2];
} tmpl_TwoByTwoMatrixFloat;

typedef struct tmpl_TwoByTwoMatrixDouble_Def {
    double dat[2][2];
} tmpl_TwoByTwoMatrixDouble;

typedef struct tmpl_TwoByTwoMatrixLongDouble_Def {
    long double dat[2][2];
} tmpl_TwoByTwoMatrixLongDouble;

typedef tmpl_TwoByTwoMatrixDouble tmpl_TwoByTwoMatrix;

/*  A line segment is given by the start and end points.                      */
typedef struct tmpl_2DLineSegmentFloat_Def {
    tmpl_TwoVectorFloat dat[2];
} tmpl_2DLineSegmentFloat;

typedef struct tmpl_2DLineSegmentDouble_Def {
    tmpl_TwoVectorDouble dat[2];
} tmpl_2DLineSegmentDouble;

typedef struct tmpl_2DLineSegmentLongDouble_Def {
    tmpl_TwoVectorLongDouble dat[2];
} tmpl_2DLineSegmentLongDouble;

typedef tmpl_2DLineSegmentDouble tmpl_2DLineSegment;

/*  A line is given by a point on the line, and the direction. That is, we    *
 *  can write a(t) = P + tV.                                                  */
typedef struct tmpl_2DLineFloat_Def {
    tmpl_TwoVectorFloat P;
    tmpl_TwoVectorFloat V;
} tmpl_2DLineFloat;

typedef struct tmpl_2DLineDouble_Def {
    tmpl_TwoVectorDouble P;
    tmpl_TwoVectorDouble V;
} tmpl_2DLineDouble;

typedef struct tmpl_2DLineLongDouble_Def {
    tmpl_TwoVectorLongDouble P;
    tmpl_TwoVectorLongDouble V;
} tmpl_2DLineLongDouble;

typedef tmpl_2DLineDouble tmpl_2DLine;

/*  Planar circles are represented by a point and a radius. Many functions    *
 *  allow circles to degenerate to straight lines. In this case the radius is *
 *  infinite, and the "center" instead becomes the line. To save memory, a    *
 *  union is used between the center and the line.                            */
typedef struct tmpl_2DCircleFloat_Def {
    union tmpl_2DCircleFloat_Data {
        tmpl_TwoVectorFloat center;
        tmpl_TwoVectorFloat line;
    } data;
    float radius;

    /*  Boolean for if the circle degenerated to a line.                      */
    tmpl_Bool is_line;
} tmpl_2DCircleFloat;

typedef struct tmpl_2DCircleDouble_Def {
    union tmpl_2DCircleDouble_Data {
        tmpl_TwoVectorDouble center;
        tmpl_2DLineDouble line;
    } data;
    double radius;
    tmpl_Bool is_line;
} tmpl_2DCircleDouble;

typedef struct tmpl_2DCircleLongDouble_Def {
    union tmpl_2DCircleLongDouble_Data {
        tmpl_TwoVectorLongDouble center;
        tmpl_2DLineLongDouble line;
    } data;
    long double radius;
    tmpl_Bool is_line;
} tmpl_2DCircleLongDouble;

typedef tmpl_2DCircleDouble tmpl_2DCircle;

/*  A polygon is an array of points which represent the vertices of the       *
 *  polygon. There's no need for simple polygons, so a polygon with two       *
 *  points will be treated as a path from P to Q and then from Q to P.        */
typedef struct tmpl_2DPolygonFloat_Def {
    tmpl_TwoVectorFloat *points;
    size_t number_of_points;
} tmpl_2DPolygonFloat;

typedef struct tmpl_2DPolygonDouble_Def {
    tmpl_TwoVectorDouble *points;
    size_t number_of_points;
} tmpl_2DPolygonDouble;

typedef struct tmpl_2DPolygonLongDouble_Def {
    tmpl_TwoVectorLongDouble *points;
    size_t number_of_points;
} tmpl_2DPolygonLongDouble;

typedef tmpl_2DPolygonDouble tmpl_2DPolygon;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2x2Double_Component                                              *
 *  Purpose:                                                                  *
 *      Returns the (m, n) element of a 2x2 matrix.                           *
 *  Arguments:                                                                *
 *      const tmpl_TwoByTwoMatrixDouble *A:                                   *
 *          A pointer to a 2x2 matrix.                                        *
 *      size_t m:                                                             *
 *          The first index of the element.                                   *
 *      size_t n:                                                             *
 *          The second index of the element.                                  *
 *  Outputs:                                                                  *
 *      double out:                                                           *
 *          The (m, n) component of the tmpl_TwoByTwoMatrixDouble A.          *
 *  Notes:                                                                    *
 *      If m or n are larger than 2, the index is computed mod 2, so no       *
 *      undefined behavior can occur.                                         *
 ******************************************************************************/
TMPL_EXPORT extern float
tmpl_2x2Float_Component(const tmpl_TwoByTwoMatrixFloat *A, size_t m, size_t n);

TMPL_EXPORT extern double
tmpl_2x2Double_Component(const tmpl_TwoByTwoMatrixDouble *A,
                         size_t m, size_t n);

TMPL_EXPORT extern long double
tmpl_2x2LDouble_Component(const tmpl_TwoByTwoMatrixLongDouble *A,
                          size_t m, size_t n);

#define tmpl_2x2_Component tmpl_2x2Double_Component

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2x2Double_Determinant                                            *
 *  Purpose:                                                                  *
 *      Coomputes the determinant of a 2x2 matrix.                            *
 *  Arguments:                                                                *
 *      const tmpl_TwoByTwoMatrixDouble *A:                                   *
 *          A pointer to a 2x2 matrix.                                        *
 *  Outputs:                                                                  *
 *      det (double):                                                         *
 *          The determinant of A.                                             *
 *  Notes:                                                                    *
 *      Float and Long Double precisions are also provided.                   *
 ******************************************************************************/
TMPL_EXPORT extern float tmpl_2x2Float_Determinant(const tmpl_TwoByTwoMatrixFloat *A);
TMPL_EXPORT extern double tmpl_2x2Double_Determinant(const tmpl_TwoByTwoMatrixDouble *A);

TMPL_EXPORT extern long double
tmpl_2x2LDouble_Determinant(const tmpl_TwoByTwoMatrixLongDouble *A);

#define tmpl_2x2_Determinant tmpl_2x2Double_Determinant

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2x2Double_Inverse                                                *
 *  Purpose:                                                                  *
 *      Coomputes the inverse of a 2x2 matrix.                                *
 *  Arguments:                                                                *
 *      const tmpl_TwoByTwoMatrixDouble *A:                                   *
 *          A pointer to a 2x2 matrix.                                        *
 *  Outputs:                                                                  *
 *      inv_A (tmpl_TwoByTwoMatrix):                                          *
 *          The inverse of A.                                                 *
 *  Notes:                                                                    *
 *      Float and Long Double precisions are also provided.                   *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_TwoByTwoMatrixFloat
tmpl_2x2Float_Inverse(const tmpl_TwoByTwoMatrixFloat *A);

TMPL_EXPORT extern tmpl_TwoByTwoMatrixDouble
tmpl_2x2Double_Inverse(const tmpl_TwoByTwoMatrixDouble *A);

TMPL_EXPORT extern tmpl_TwoByTwoMatrixLongDouble
tmpl_2x2LDouble_Inverse(const tmpl_TwoByTwoMatrixLongDouble *A);

#define tmpl_2x2_Inverse tmpl_2x2Double_Inverse

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2x2Double_New                                                    *
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
 ******************************************************************************/
TMPL_EXPORT extern tmpl_TwoByTwoMatrixFloat
tmpl_2x2Float_New(float a, float b, float c, float d);

TMPL_EXPORT extern tmpl_TwoByTwoMatrixDouble
tmpl_2x2Double_New(double a, double b, double c, double d);

TMPL_EXPORT extern tmpl_TwoByTwoMatrixLongDouble
tmpl_2x2LDouble_New(long double a, long double b, long double c, long double d);

#define tmpl_2x2_New tmpl_2x2Double_New

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2x2Double_Rotation                                               *
 *  Purpose:                                                                  *
 *      Returns the rotation matrix corresponding to the angle theta.         *
 *  Arguments:                                                                *
 *      double theta:                                                         *
 *          A real number, the angle to rotate by.                            *
 *  Outputs:                                                                  *
 *      tmpl_TwoByTwoMatrixDouble R:                                          *
 *          The rotation matrix.                                              *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_TwoByTwoMatrixFloat tmpl_2x2Float_Rotation(float theta);
TMPL_EXPORT extern tmpl_TwoByTwoMatrixDouble tmpl_2x2Double_Rotation(double theta);

TMPL_EXPORT extern tmpl_TwoByTwoMatrixLongDouble
tmpl_2x2LDouble_Rotation(long double theta);

#define tmpl_2x2_Rotation tmpl_2x2Double_Rotation

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2x2Double_Scale                                                  *
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
TMPL_EXPORT extern tmpl_TwoByTwoMatrixFloat
tmpl_2x2Float_Scale(float r, const tmpl_TwoByTwoMatrixFloat *P);

TMPL_EXPORT extern tmpl_TwoByTwoMatrixDouble
tmpl_2x2Double_Scale(double r, const tmpl_TwoByTwoMatrixDouble *P);

TMPL_EXPORT extern tmpl_TwoByTwoMatrixLongDouble
tmpl_2x2LDouble_Scale(long double r, const tmpl_TwoByTwoMatrixLongDouble *P);

#define tmpl_2x2_Scale tmpl_2x2Double_Scale

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_GET_2x2_MATRIX_COMPONENT                                         *
 *  Purpose:                                                                  *
 *      Returns the (m, n) element of a 2x2 matrix.                           *
 *  Arguments:                                                                *
 *      tmpl_TwoByTwoMatrix A:                                                *
 *          A 2x2 matrix.                                                     *
 *      int m:                                                                *
 *          The first index of the element.                                   *
 *      int n:                                                                *
 *          The second index of the element.                                  *
 *  Outputs:                                                                  *
 *      float/double/long double out:                                         *
 *          The (m, n) component of the tmpl_TwoByTwoMatrix                   *
 ******************************************************************************/
#define TMPL_GET_2x2_MATRIX_COMPONENT(A, m, n) ((A).dat[(m)][(n)])

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Add                                                     *
 *  Purpose:                                                                  *
 *      Given two tmpl_TwoVector's, compute the vector sum of them.           *
 *  Arguments:                                                                *
 *      const tmpl_TwoVectorDouble *P:                                        *
 *          A pointer to an arbitrary vector.                                 *
 *      const tmpl_TwoVectorDouble *Q:                                        *
 *          Another pointer to an arbitrary vector.                           *
 *  Outputs:                                                                  *
 *      tmpl_TwoVectorDouble sum:                                             *
 *          The vector sum P+Q.                                               *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_TwoVectorFloat
tmpl_2DFloat_Add(const tmpl_TwoVectorFloat *P, const tmpl_TwoVectorFloat *Q);

TMPL_EXPORT extern tmpl_TwoVectorDouble
tmpl_2DDouble_Add(const tmpl_TwoVectorDouble *P, const tmpl_TwoVectorDouble *Q);

TMPL_EXPORT extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Add(const tmpl_TwoVectorLongDouble *P,
                   const tmpl_TwoVectorLongDouble *Q);

#define tmpl_2D_Add tmpl_2DDouble_Add

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2D_Dot_Product                                                   *
 *  Purpose:                                                                  *
 *      Compute the Euclidean dot product of two 2D vectors.                  *
 *  Arguments:                                                                *
 *      const tmpl_TwoVectorDouble *P:                                        *
 *          A pointer to an arbitrary vector.                                 *
 *      const tmpl_TwoVectorDouble *Q:                                        *
 *          Another pointer to an arbitrary vector.                           *
 *  Outputs:                                                                  *
 *      double dot_prod:                                                      *
 *          The dot product of P and Q.                                       *
 ******************************************************************************/
TMPL_EXPORT extern float
tmpl_2DFloat_Dot_Product(const tmpl_TwoVectorFloat *P,
                         const tmpl_TwoVectorFloat *Q);

TMPL_EXPORT extern double
tmpl_2DDouble_Dot_Product(const tmpl_TwoVectorDouble *P,
                          const tmpl_TwoVectorDouble *Q);

TMPL_EXPORT extern long double
tmpl_2DLDouble_Dot_Product(const tmpl_TwoVectorLongDouble *P,
                           const tmpl_TwoVectorLongDouble *Q);

#define tmpl_2D_Dot_Product tmpl_2DDouble_Dot_Product

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
TMPL_EXPORT extern tmpl_TwoVectorFloat
tmpl_2DFloat_Orthogonal(const tmpl_TwoVectorFloat *V);

TMPL_EXPORT extern tmpl_TwoVectorDouble
tmpl_2DDouble_Orthogonal(const tmpl_TwoVectorDouble *V);

TMPL_EXPORT extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Orthogonal(const tmpl_TwoVectorLongDouble *V);

#define tmpl_2D_Orthogonal tmpl_2DDouble_Orthogonal

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Matrix_Product                                          *
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
TMPL_EXPORT extern tmpl_TwoVectorFloat
tmpl_2DFloat_Matrix_Product(const tmpl_TwoByTwoMatrixFloat *A,
                            const tmpl_TwoVectorFloat *P);

TMPL_EXPORT extern tmpl_TwoVectorDouble
tmpl_2DDouble_Matrix_Product(const tmpl_TwoByTwoMatrixDouble *A,
                             const tmpl_TwoVectorDouble *P);

TMPL_EXPORT extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Matrix_Product(const tmpl_TwoByTwoMatrixLongDouble *A,
                              const tmpl_TwoVectorLongDouble *P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Midpoint                                                *
 *  Purpose:                                                                  *
 *      Compute the midpoint of two tmpl_TwoVectorDouble's.                   *
 *  Arguments:                                                                *
 *      const tmpl_TwoVectorDouble *P:                                        *
 *          A pointer to an arbitrary tmpl_TwoVectorDouble.                   *
 *      const tmpl_TwoVectorDouble *Q:                                        *
 *          Another pointer to an arbitrary tmpl_TwoVectorDouble.             *
 *  Outputs:                                                                  *
 *      tmpl_TwoVector mid:                                                   *
 *          The midpoint of P and Q, defined to be (P + Q) / 2.               *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_TwoVectorFloat
tmpl_2DFloat_Midpoint(const tmpl_TwoVectorFloat *P,
                      const tmpl_TwoVectorFloat *Q);

TMPL_EXPORT extern tmpl_TwoVectorDouble
tmpl_2DDouble_Midpoint(const tmpl_TwoVectorDouble *P,
                       const tmpl_TwoVectorDouble *Q);

TMPL_EXPORT extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Midpoint(const tmpl_TwoVectorLongDouble *P,
                        const tmpl_TwoVectorLongDouble *Q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Rect                                                    *
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
TMPL_EXPORT extern tmpl_TwoVectorFloat tmpl_2DFloat_Rect(float x, float y);
TMPL_EXPORT extern tmpl_TwoVectorDouble tmpl_2DDouble_Rect(double x, double y);

TMPL_EXPORT extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Rect(long double x, long double y);

#define tmpl_TwoVector_Rect tmpl_DoubleTwoVector_Rect

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_X                                                       *
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
TMPL_EXPORT extern float tmpl_2DFloat_X(const tmpl_TwoVectorFloat *P);
TMPL_EXPORT extern double tmpl_2DDouble_X(const tmpl_TwoVectorDouble *P);
TMPL_EXPORT extern long double tmpl_2DLDouble_X(const tmpl_TwoVectorLongDouble *P);

#define tmpl_2D_X tmpl_2DDouble_X

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Y                                                       *
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
TMPL_EXPORT extern float tmpl_2DFloat_Y(const tmpl_TwoVectorFloat *P);
TMPL_EXPORT extern double tmpl_2DDouble_Y(const tmpl_TwoVectorDouble *P);
TMPL_EXPORT extern long double tmpl_2DLDouble_Y(const tmpl_TwoVectorLongDouble *P);

#define tmpl_2D_Y tmpl_2DDouble_Y

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
TMPL_EXPORT extern tmpl_TwoVectorFloat
tmpl_2DFloat_Subtract(const tmpl_TwoVectorFloat *P,
                      const tmpl_TwoVectorFloat *Q);

TMPL_EXPORT extern tmpl_TwoVectorDouble
tmpl_2DDouble_Subtract(const tmpl_TwoVectorDouble *P,
                       const tmpl_TwoVectorDouble *Q);

TMPL_EXPORT extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Subtract(const tmpl_TwoVectorLongDouble *P,
                        const tmpl_TwoVectorLongDouble *Q);

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
TMPL_EXPORT extern tmpl_TwoVectorFloat
tmpl_2DFloat_Scale(float r, const tmpl_TwoVectorFloat *P);

TMPL_EXPORT extern tmpl_TwoVectorDouble
tmpl_2DDouble_Scale(double r, const tmpl_TwoVectorDouble *P);

TMPL_EXPORT extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Scale(long double r, const tmpl_TwoVectorLongDouble *P);

TMPL_EXPORT extern tmpl_TwoVectorFloat tmpl_2DFloat_Polar(float r, float theta);
TMPL_EXPORT extern tmpl_TwoVectorDouble tmpl_2DDouble_Polar(double r, double theta);

TMPL_EXPORT extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Polar(long double r, long double theta);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_L2_Norm                                                 *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm of a tmpl_TwoVectorDouble.                *
 *  Arguments:                                                                *
 *      const tmpl_TwoVectorDouble *P:                                        *
 *          An arbitrary tmpl_TwoVector.                                      *
 *  Outputs:                                                                  *
 *      double norm:                                                          *
 *          The Euclidean norm of P. If we represent P by (x, y), norm is     *
 *          defined by norm = sqrt(x^2 + y^2).                                *
 ******************************************************************************/

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/tmpl_math.h>
TMPL_INLINE_DECL
float tmpl_2DFloat_L2_Norm(const tmpl_TwoVectorFloat *P)
{
    return tmpl_Float_Hypot(P->dat[0], P->dat[1]);
}

TMPL_INLINE_DECL
double tmpl_2DDouble_L2_Norm(const tmpl_TwoVectorDouble *P)
{
    return tmpl_Double_Hypot(P->dat[0], P->dat[1]);
}

TMPL_INLINE_DECL
long double tmpl_2DLDouble_L2_Norm(const tmpl_TwoVectorLongDouble *P)
{
    return tmpl_LDouble_Hypot(P->dat[0], P->dat[1]);
}
#else
TMPL_EXPORT extern float tmpl_2DFloat_L2_Norm(const tmpl_TwoVectorFloat *P);
TMPL_EXPORT extern double tmpl_2DDouble_L2_Norm(const tmpl_TwoVectorDouble *P);
TMPL_EXPORT extern long double tmpl_2DLDouble_L2_Norm(const tmpl_TwoVectorLongDouble *P);
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_L2_Norm_Squared                                         *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean norm of a tmpl_TwoVectorDouble.  *
 *  Arguments:                                                                *
 *      const tmpl_TwoVectorDouble *P:                                        *
 *          An arbitrary tmpl_TwoVector.                                      *
 *  Outputs:                                                                  *
 *      double norm_sq:                                                       *
 *          The value ||P||_2^2 = x^2 + y^2.                                  *
 ******************************************************************************/
TMPL_EXPORT extern float tmpl_2DFloat_L2_Norm_Squared(const tmpl_TwoVectorFloat *P);
TMPL_EXPORT extern double tmpl_2DDouble_L2_Norm_Squared(const tmpl_TwoVectorDouble *P);

TMPL_EXPORT extern long double
tmpl_2DLDouble_L2_Norm_Squared(const tmpl_TwoVectorLongDouble *P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Normalize                                               *
 *  Purpose:                                                                  *
 *      Compute the Euclidean dot product of two 2D vectors.                  *
 *  Arguments:                                                                *
 *      const tmpl_TwoVectorDouble *P:                                        *
 *          A 2D vector.                                                      *
 *  Outputs:                                                                  *
 *      tmpl_TwoVector P_hat:                                                 *
 *          A vector of length 1 in the same direction of P.                  *
 *  NOTES:                                                                    *
 *      If P is the zero vector P = (0, 0), this function returns (NaN, NaN). *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_TwoVectorFloat
tmpl_2DFloat_Normalize(const tmpl_TwoVectorFloat *P);

TMPL_EXPORT extern tmpl_TwoVectorDouble
tmpl_2DDouble_Normalize(const tmpl_TwoVectorDouble *P);

TMPL_EXPORT extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Normalize(const tmpl_TwoVectorLongDouble *P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Rel_Angle                                               *
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
TMPL_EXPORT extern float
tmpl_2DFloat_Rel_Angle(const tmpl_TwoVectorFloat *O,
                       const tmpl_TwoVectorFloat *P,
                       const tmpl_TwoVectorFloat *Q);

TMPL_EXPORT extern double
tmpl_2DDouble_Rel_Angle(const tmpl_TwoVectorDouble *O,
                        const tmpl_TwoVectorDouble *P,
                        const tmpl_TwoVectorDouble *Q);

TMPL_EXPORT extern long double
tmpl_2DLDouble_Rel_Angle(const tmpl_TwoVectorLongDouble *O,
                         const tmpl_TwoVectorLongDouble *P,
                         const tmpl_TwoVectorLongDouble *Q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Are_Collinear                                           *
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
TMPL_EXPORT extern tmpl_Bool
tmpl_2DFloat_Are_Collinear(const tmpl_TwoVectorFloat *A,
                           const tmpl_TwoVectorFloat *B,
                           const tmpl_TwoVectorFloat *C);

TMPL_EXPORT extern tmpl_Bool
tmpl_2DDouble_Are_Collinear(const tmpl_TwoVectorDouble *A,
                            const tmpl_TwoVectorDouble *B,
                            const tmpl_TwoVectorDouble *C);

TMPL_EXPORT extern tmpl_Bool
tmpl_2DLDouble_Are_Collinear(const tmpl_TwoVectorLongDouble *A,
                             const tmpl_TwoVectorLongDouble *B,
                             const tmpl_TwoVectorLongDouble *C);

TMPL_EXPORT extern float
tmpl_2DFloat_L2_Dist(const tmpl_TwoVectorFloat *P,
                     const tmpl_TwoVectorFloat *Q);

TMPL_EXPORT extern double
tmpl_2DDouble_L2_Dist(const tmpl_TwoVectorDouble *P,
                      const tmpl_TwoVectorDouble *Q);

TMPL_EXPORT extern long double
tmpl_2DLDouble_L2_Dist(const tmpl_TwoVectorLongDouble *P,
                       const tmpl_TwoVectorLongDouble *Q);

TMPL_EXPORT extern tmpl_Bool
tmpl_LineSegment2D_Intersect(tmpl_2DLineSegment L0, tmpl_2DLineSegment L1);

TMPL_EXPORT extern tmpl_TwoVectorDouble
tmpl_2DDouble_Point_Inverse(const tmpl_2DCircleDouble *C,
                            const tmpl_TwoVectorDouble *P);

TMPL_EXPORT extern tmpl_2DCircleDouble
tmpl_2DDouble_Circle_Inverse(const tmpl_2DCircleDouble *C0,
                             const tmpl_2DCircleDouble *C1);

TMPL_EXPORT extern tmpl_2DCircleDouble
tmpl_2DDouble_Line_Inverse(const tmpl_2DCircleDouble *C,
                           const tmpl_2DLineDouble *L);

TMPL_EXPORT extern void
tmpl_2DDouble_Circle_As_Line(tmpl_2DCircleDouble *circle,
                             const tmpl_TwoVectorDouble *P,
                             const tmpl_TwoVectorDouble *V);

TMPL_EXPORT extern void
tmpl_2DDouble_Reset_Circle(const tmpl_2DCircleDouble *circle,
                           const tmpl_TwoVector *P, double r);

#endif
/*  End of include guard.                                                     */
