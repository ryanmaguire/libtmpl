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

/*  Typedefs for 2D vectors at various precisions.                            */
#include <libtmpl/include/types/tmpl_vec2_double.h>
#include <libtmpl/include/types/tmpl_vec2_float.h>
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

#if TMPL_USE_INLINE == 1

#ifdef TMPL_INLINE_FILE
#undef TMPL_INLINE_FILE
#endif

#define TMPL_INLINE_FILE(file) <libtmpl/include/inline/vec2/file>

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Add                                                     *
 *  Purpose:                                                                  *
 *      Computes the sum of two vectors in the plane.                         *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      sum (tmpl_TwoVectorDouble):                                           *
 *          The vector sum P + Q.                                             *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_add_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_add_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_add_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_Add(const tmpl_TwoVectorFloat * const P,
                 const tmpl_TwoVectorFloat * const Q);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Add(const tmpl_TwoVectorDouble * const P,
                  const tmpl_TwoVectorDouble * const Q);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Add(const tmpl_TwoVectorLongDouble * const P,
                   const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_AddTo                                                   *
 *  Purpose:                                                                  *
 *      Performs vector addition in-place, providing "+=" for 2D vectors.     *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorDouble * const):                                     *
 *          A pointer to a vector in the plane. The sum is stored here.       *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_addto_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_addto_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_addto_ldouble.h)

#else

extern void
tmpl_2DFloat_AddTo(tmpl_TwoVectorFloat * const P,
                   const tmpl_TwoVectorFloat * const Q);

extern void
tmpl_2DDouble_AddTo(tmpl_TwoVectorDouble * const P,
                    const tmpl_TwoVectorDouble * const Q);

extern void
tmpl_2DLDouble_AddTo(tmpl_TwoVectorLongDouble * const P,
                     const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Cross_Product                                           *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors in the plane.               *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      cross (double):                                                       *
 *          The cross product P x Q.                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_cross_product_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_cross_product_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_cross_product_ldouble.h)

#else

extern float
tmpl_2DFloat_Cross_Product(const tmpl_TwoVectorFloat * const P,
                           const tmpl_TwoVectorFloat * const Q);

extern double
tmpl_2DDouble_Cross_Product(const tmpl_TwoVectorDouble * const P,
                            const tmpl_TwoVectorDouble * const Q);

extern long double
tmpl_2DLDouble_Cross_Product(const tmpl_TwoVectorLongDouble * const P,
                             const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Dot_Product                                             *
 *  Purpose:                                                                  *
 *      Computes the Euclidean dot product of two 2D vectors.                 *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      dot (double):                                                         *
 *          The dot product of P and Q.                                       *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_dot_product_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_dot_product_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_dot_product_ldouble.h)

#else

extern float
tmpl_2DFloat_Dot_Product(const tmpl_TwoVectorFloat * const P,
                         const tmpl_TwoVectorFloat * const Q);

extern double
tmpl_2DDouble_Dot_Product(const tmpl_TwoVectorDouble * const P,
                          const tmpl_TwoVectorDouble * const Q);

extern long double
tmpl_2DLDouble_Dot_Product(const tmpl_TwoVectorLongDouble * const P,
                           const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Hadamard_Divide                                         *
 *  Purpose:                                                                  *
 *      Computes the component-wise division of two vectors in the plane.     *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      quot (tmpl_TwoVectorDouble):                                          *
 *          The component-wise vector quotient P / Q.                         *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_divide_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_divide_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_divide_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_Hadamard_Divide(const tmpl_TwoVectorFloat * const P,
                             const tmpl_TwoVectorFloat * const Q);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Hadamard_Divide(const tmpl_TwoVectorDouble * const P,
                              const tmpl_TwoVectorDouble * const Q);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Hadamard_Divide(const tmpl_TwoVectorLongDouble * const P,
                               const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Hadamard_DivideBy                                       *
 *  Purpose:                                                                  *
 *      Computes the component-wise quotient of two vectors in-place.         *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorDouble * const):                                     *
 *          A pointer to a vector in the plane, the quotient is stored here.  *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_divideby_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_divideby_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_divideby_ldouble.h)

#else

extern void
tmpl_2DFloat_Hadamard_DivideBy(tmpl_TwoVectorFloat * const P,
                               const tmpl_TwoVectorFloat * const Q);

extern void
tmpl_2DDouble_Hadamard_DivideBy(tmpl_TwoVectorDouble * const P,
                                const tmpl_TwoVectorDouble * const Q);

extern void
tmpl_2DLDouble_Hadamard_DivideBy(tmpl_TwoVectorLongDouble * const P,
                                 const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Hadamard_Product                                        *
 *  Purpose:                                                                  *
 *      Computes the component-wise product of two vectors in the plane.      *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      product (tmpl_TwoVectorDouble):                                       *
 *          The component-wise vector product P * Q.                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_product_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_product_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_product_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_Hadamard_Product(const tmpl_TwoVectorFloat * const P,
                              const tmpl_TwoVectorFloat * const Q);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Hadamard_Product(const tmpl_TwoVectorDouble * const P,
                               const tmpl_TwoVectorDouble * const Q);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Hadamard_Product(const tmpl_TwoVectorLongDouble * const P,
                                const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Hadamard_ProductWith                                    *
 *  Purpose:                                                                  *
 *      Computes the component-wise product of two vectors in-place.          *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorDouble * const):                                     *
 *          A pointer to a vector in the plane, the product is stored here.   *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_productwith_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_productwith_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_hadamard_productwith_ldouble.h)

#else

extern void
tmpl_2DFloat_Hadamard_ProductWith(tmpl_TwoVectorFloat * const P,
                                  const tmpl_TwoVectorFloat * const Q);

extern void
tmpl_2DDouble_Hadamard_ProductWith(tmpl_TwoVectorDouble * const P,
                                   const tmpl_TwoVectorDouble * const Q);

extern void
tmpl_2DLDouble_Hadamard_ProductWith(tmpl_TwoVectorLongDouble * const P,
                                    const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_L2_Dist                                                 *
 *  Purpose:                                                                  *
 *      Computes the Euclidean distance between two points in the plane.      *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      dist (double):                                                        *
 *          The distance between P and Q.                                     *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_l2_dist_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_l2_dist_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_l2_dist_ldouble.h)

#else

extern float
tmpl_2DFloat_L2_Dist(const tmpl_TwoVectorFloat * const P,
                     const tmpl_TwoVectorFloat * const Q);

extern double
tmpl_2DDouble_L2_Dist(const tmpl_TwoVectorDouble * const P,
                      const tmpl_TwoVectorDouble * const Q);

extern long double
tmpl_2DLDouble_L2_Dist(const tmpl_TwoVectorLongDouble * const P,
                       const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_L2_Dist_Squared                                         *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean distance between two points.     *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      dist_squared (double):                                                *
 *          The square of the distance between P and Q.                       *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_l2_dist_squared_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_l2_dist_squared_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_l2_dist_squared_ldouble.h)

#else

extern float
tmpl_2DFloat_L2_Dist_Squared(const tmpl_TwoVectorFloat * const P,
                             const tmpl_TwoVectorFloat * const Q);

extern double
tmpl_2DDouble_L2_Dist_Squared(const tmpl_TwoVectorDouble * const P,
                              const tmpl_TwoVectorDouble * const Q);

extern long double
tmpl_2DLDouble_L2_Dist_Squared(const tmpl_TwoVectorLongDouble * const P,
                               const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_L2_Norm                                                 *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm of a point in the plane.                  *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      norm (double):                                                        *
 *          The Euclidean norm of P.                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_l2_norm_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_l2_norm_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_l2_norm_ldouble.h)

#else

extern float
tmpl_2DFloat_L2_Norm(const tmpl_TwoVectorFloat * const P);

extern double
tmpl_2DDouble_L2_Norm(const tmpl_TwoVectorDouble * const P);

extern long double
tmpl_2DLDouble_L2_Norm(const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_L2_Norm_Squared                                         *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean norm of a point in the plane.    *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      norm_squared (double):                                                *
 *          The square of the Euclidean norm of P.                            *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_l2_norm_squared_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_l2_norm_squared_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_l2_norm_squared_ldouble.h)

#else

extern float
tmpl_2DFloat_L2_Norm_Squared(const tmpl_TwoVectorFloat * const P);

extern double
tmpl_2DDouble_L2_Norm_Squared(const tmpl_TwoVectorDouble * const P);

extern long double
tmpl_2DLDouble_L2_Norm_Squared(const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Midpoint                                                *
 *  Purpose:                                                                  *
 *      Computes the midpoint of two points in the plane.                     *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      mid (tmpl_TwoVector):                                                 *
 *          The midpoint of P and Q.                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_midpoint_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_midpoint_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_midpoint_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_Midpoint(const tmpl_TwoVectorFloat * const P,
                      const tmpl_TwoVectorFloat * const Q);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Midpoint(const tmpl_TwoVectorDouble * const P,
                       const tmpl_TwoVectorDouble * const Q);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Midpoint(const tmpl_TwoVectorLongDouble * const P,
                        const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Orthogonal                                              *
 *  Purpose:                                                                  *
 *      Computes a vector orthogonal to the input.                            *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      orth (tmpl_TwoVectorDouble):                                          *
 *          A vector orthogonal to P with the same magnitude.                 *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_orthogonal_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_orthogonal_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_orthogonal_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_Orthogonal(const tmpl_TwoVectorFloat * const P);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Orthogonal(const tmpl_TwoVectorDouble * const P);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Orthogonal(const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Polar                                                   *
 *  Purpose:                                                                  *
 *      Creates a vector from its polar coordinates.                          *
 *  Arguments:                                                                *
 *      r (double):                                                           *
 *          The radius of the point.                                          *
 *      theta (double):                                                       *
 *          The angle the point makes with the x axis, in radians.            *
 *  Outputs:                                                                  *
 *      point (tmpl_TwoVectorDouble):                                         *
 *          The point (r cos(theta), r sin(theta)).                           *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_polar_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_polar_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_polar_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_Polar(float r, float theta);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Polar(double r, double theta);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Polar(long double r, long double theta);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Polard                                                  *
 *  Purpose:                                                                  *
 *      Creates a vector from its polar coordinates.                          *
 *  Arguments:                                                                *
 *      r (double):                                                           *
 *          The radius of the point.                                          *
 *      theta (double):                                                       *
 *          The angle the point makes with the x axis, in degrees.            *
 *  Outputs:                                                                  *
 *      point (tmpl_TwoVectorDouble):                                         *
 *          The point (r cos(theta), r sin(theta)).                           *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_polard_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_polard_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_polard_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_Polard(float r, float theta);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Polard(double r, double theta);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Polard(long double r, long double theta);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Polar_Angle                                             *
 *  Purpose:                                                                  *
 *      Computes the angle a vector makes with the positive x axis, radians.  *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      angle (double):                                                       *
 *          The angle made by P and the x axis.                               *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_polar_angle_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_polar_angle_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_polar_angle_ldouble.h)

#else

extern float
tmpl_2DFloat_Polar_Angle(const tmpl_TwoVectorFloat * const P);

extern double
tmpl_2DDouble_Polar_Angle(const tmpl_TwoVectorDouble * const P);

extern long double
tmpl_2DLDouble_Polar_Angle(const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Positive_Polar_Angle                                    *
 *  Purpose:                                                                  *
 *      Computes the positive angle a point makes with the x axis in radians. *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      angle (double):                                                       *
 *          The positive angle made by P and the x axis.                      *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_positive_polar_angle_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_positive_polar_angle_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_positive_polar_angle_ldouble.h)

#else

extern float
tmpl_2DFloat_Positive_Polar_Angle(const tmpl_TwoVectorFloat * const P);

extern double
tmpl_2DDouble_Positive_Polar_Angle(const tmpl_TwoVectorDouble * const P);

extern long double
tmpl_2DLDouble_Positive_Polar_Angle(const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Scale                                                   *
 *  Purpose:                                                                  *
 *      Computes the scalar product of a vector and a real number.            *
 *  Arguments:                                                                *
 *      r (double):                                                           *
 *          A real number, the scalar multiplier.                             *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      prod (tmpl_TwoVectorDouble):                                          *
 *          The scalar product r * P.                                         *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_scale_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_scale_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_scale_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_Scale(float r, const tmpl_TwoVectorFloat * const P);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Scale(double r, const tmpl_TwoVectorDouble * const P);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Scale(long double r, const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_ScaleBy                                                 *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication in-place providing "*=" for 2D vectors.*
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorDouble * const):                                     *
 *          A pointer to a vector in the plane. The product is stored here.   *
 *      r (double):                                                           *
 *          A real number, the scalar multiplier.                             *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_scaleby_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_scaleby_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_scaleby_ldouble.h)

#else

extern void
tmpl_2DFloat_ScaleBy(tmpl_TwoVectorFloat * const P, float r);

extern void
tmpl_2DDouble_ScaleBy(tmpl_TwoVectorDouble * const P, double r);

extern void
tmpl_2DLDouble_ScaleBy(tmpl_TwoVectorLongDouble * const P, long double r);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Subtract                                                *
 *  Purpose:                                                                  *
 *      Computes the difference of two vectors in the plane.                  *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      diff (tmpl_TwoVectorDouble):                                          *
 *          The vector difference P - Q.                                      *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_subtract_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_subtract_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_subtract_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_Subtract(const tmpl_TwoVectorFloat * const P,
                      const tmpl_TwoVectorFloat * const Q);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Subtract(const tmpl_TwoVectorDouble * const P,
                       const tmpl_TwoVectorDouble * const Q);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Subtract(const tmpl_TwoVectorLongDouble * const P,
                        const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_SubtractFrom                                            *
 *  Purpose:                                                                  *
 *      Performs vector subtraction in-place, providing "-=" for 2D vectors.  *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorDouble * const):                                     *
 *          A pointer to a vector in the plane. The difference is stored here.*
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another pointer to a vector in the plane.                         *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_subtractfrom_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_subtractfrom_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_subtractfrom_ldouble.h)

#else

extern void
tmpl_2DFloat_SubtractFrom(tmpl_TwoVectorFloat * const P,
                          const tmpl_TwoVectorFloat * const Q);

extern void
tmpl_2DDouble_SubtractFrom(tmpl_TwoVectorDouble * const P,
                           const tmpl_TwoVectorDouble * const Q);

extern void
tmpl_2DLDouble_SubtractFrom(tmpl_TwoVectorLongDouble * const P,
                            const tmpl_TwoVectorLongDouble * const Q);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Normalize                                               *
 *  Purpose:                                                                  *
 *      Computes the unit vector in the direction of P.                       *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      u (tmpl_TwoVectorDouble):                                             *
 *          A unit vector parallel to P.                                      *
 ******************************************************************************/
extern tmpl_TwoVectorFloat
tmpl_2DFloat_Normalize(const tmpl_TwoVectorFloat * const P);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Normalize(const tmpl_TwoVectorDouble * const P);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Normalize(const tmpl_TwoVectorLongDouble * const P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_X                                                       *
 *  Purpose:                                                                  *
 *      Returns the x coordinate of a 2D vector.                              *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      x_val (double):                                                       *
 *          The x coordinate of P.                                            *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_x_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_x_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_x_ldouble.h)

#else

extern float tmpl_2DFloat_X(const tmpl_TwoVectorFloat * const P);
extern double tmpl_2DDouble_X(const tmpl_TwoVectorDouble * const P);
extern long double tmpl_2DLDouble_X(const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_X_Project                                               *
 *  Purpose:                                                                  *
 *      Projects a vector onto the x axis.                                    *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      x_projection (tmpl_TwoVectorDouble):                                  *
 *          The projection of P onto the x axis.                              *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_x_project_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_x_project_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_x_project_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_X_Project(const tmpl_TwoVectorFloat * const P);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_X_Project(const tmpl_TwoVectorDouble * const P);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_X_Project(const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_X_ProjectSelf                                           *
 *  Purpose:                                                                  *
 *      Projects a vector onto the x axis.                                    *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorDouble * const):                                     *
 *          A vector in the plane. The projection is stored here.             *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_x_projectself_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_x_projectself_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_x_projectself_ldouble.h)

#else

extern void tmpl_2DFloat_X_ProjectSelf(tmpl_TwoVectorFloat * const P);
extern void tmpl_2DDouble_X_ProjectSelf(tmpl_TwoVectorDouble * const P);
extern void tmpl_2DLDouble_X_ProjectSelf(tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Y                                                       *
 *  Purpose:                                                                  *
 *      Returns the y coordinate of a 2D vector.                              *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      y_val (double):                                                       *
 *          The y coordinate of P.                                            *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_y_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_y_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_y_ldouble.h)

#else

extern float tmpl_2DFloat_Y(const tmpl_TwoVectorFloat * const P);
extern double tmpl_2DDouble_Y(const tmpl_TwoVectorDouble * const P);
extern long double tmpl_2DLDouble_Y(const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Y_Project                                               *
 *  Purpose:                                                                  *
 *      Projects a vector onto the y axis.                                    *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      y_projection (tmpl_TwoVectorDouble):                                  *
 *          The projection of P onto the y axis.                              *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_y_project_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_y_project_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_y_project_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_Y_Project(const tmpl_TwoVectorFloat * const P);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Y_Project(const tmpl_TwoVectorDouble * const P);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Y_Project(const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_Y_ProjectSelf                                           *
 *  Purpose:                                                                  *
 *      Projects a vector onto the y axis.                                    *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorDouble * const):                                     *
 *          A vector in the plane. The projection is stored here.             *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_y_projectself_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_y_projectself_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_y_projectself_ldouble.h)

#else

extern void tmpl_2DFloat_Y_ProjectSelf(tmpl_TwoVectorFloat * const P);
extern void tmpl_2DDouble_Y_ProjectSelf(tmpl_TwoVectorDouble * const P);
extern void tmpl_2DLDouble_Y_ProjectSelf(tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_X_Reflect                                               *
 *  Purpose:                                                                  *
 *      Reflect a vector across the x axis.                                   *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a vector in the plane.                               *
 *  Outputs:                                                                  *
 *      x_reflection (tmpl_TwoVectorDouble):                                  *
 *          The reflection of P across the x axis.                            *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_x_reflect_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_x_reflect_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_x_reflect_ldouble.h)

#else

extern tmpl_TwoVectorFloat
tmpl_2DFloat_X_Reflect(const tmpl_TwoVectorFloat * const P);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_X_Reflect(const tmpl_TwoVectorDouble * const P);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_X_Reflect(const tmpl_TwoVectorLongDouble * const P);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_2DDouble_X_ReflectSelf                                           *
 *  Purpose:                                                                  *
 *      Reflect a vector across the x axis.                                   *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorDouble * const):                                     *
 *          A vector in the plane. The reflection is stored here.             *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include TMPL_INLINE_FILE(tmpl_vec2_x_reflectself_double.h)
#include TMPL_INLINE_FILE(tmpl_vec2_x_reflectself_float.h)
#include TMPL_INLINE_FILE(tmpl_vec2_x_reflectself_ldouble.h)

#else

extern void tmpl_2DFloat_X_ReflectSelf(tmpl_TwoVectorFloat * const P);
extern void tmpl_2DDouble_X_ReflectSelf(tmpl_TwoVectorDouble * const P);
extern void tmpl_2DLDouble_X_ReflectSelf(tmpl_TwoVectorLongDouble * const P);

#endif

/*  Typedefs for 2D lines at various precisions.                              */
#include <libtmpl/include/types/tmpl_line2_double.h>
#include <libtmpl/include/types/tmpl_line2_float.h>
#include <libtmpl/include/types/tmpl_line2_ldouble.h>

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
typedef struct tmpl_TwoLineSegmentFloat_Def {
    tmpl_TwoVectorFloat dat[2];
} tmpl_TwoLineSegmentFloat;

typedef struct tmpl_TwoLineSegmentDouble_Def {
    tmpl_TwoVectorDouble dat[2];
} tmpl_TwoLineSegmentDouble;

typedef struct tmpl_TwoLineSegmentLongDouble_Def {
    tmpl_TwoVectorLongDouble dat[2];
} tmpl_TwoLineSegmentLongDouble;

/*  Planar circles are represented by a point and a radius. Many functions    *
 *  allow circles to degenerate to straight lines. In this case the radius is *
 *  infinite, and the "center" instead becomes the line. To save memory, a    *
 *  union is used between the center and the line.                            */
typedef struct tmpl_2DCircleFloat_Def {
    union tmpl_2DCircleFloat_Data {
        tmpl_TwoVectorFloat center;
        tmpl_TwoLineFloat line;
    } data;
    float radius;

    /*  Boolean for if the circle degenerated to a line.                      */
    tmpl_Bool is_line;
} tmpl_2DCircleFloat;

typedef struct tmpl_2DCircleDouble_Def {
    union tmpl_2DCircleDouble_Data {
        tmpl_TwoVectorDouble center;
        tmpl_TwoLineDouble line;
    } data;
    double radius;
    tmpl_Bool is_line;
} tmpl_2DCircleDouble;

typedef struct tmpl_2DCircleLongDouble_Def {
    union tmpl_2DCircleLongDouble_Data {
        tmpl_TwoVectorLongDouble center;
        tmpl_TwoLineLongDouble line;
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
extern float
tmpl_2x2Float_Component(const tmpl_TwoByTwoMatrixFloat *A, size_t m, size_t n);

extern double
tmpl_2x2Double_Component(const tmpl_TwoByTwoMatrixDouble *A,
                         size_t m, size_t n);

extern long double
tmpl_2x2LDouble_Component(const tmpl_TwoByTwoMatrixLongDouble *A,
                          size_t m, size_t n);

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
extern float tmpl_2x2Float_Determinant(const tmpl_TwoByTwoMatrixFloat *A);
extern double tmpl_2x2Double_Determinant(const tmpl_TwoByTwoMatrixDouble *A);

extern long double
tmpl_2x2LDouble_Determinant(const tmpl_TwoByTwoMatrixLongDouble *A);

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
extern tmpl_TwoByTwoMatrixFloat
tmpl_2x2Float_Inverse(const tmpl_TwoByTwoMatrixFloat *A);

extern tmpl_TwoByTwoMatrixDouble
tmpl_2x2Double_Inverse(const tmpl_TwoByTwoMatrixDouble *A);

extern tmpl_TwoByTwoMatrixLongDouble
tmpl_2x2LDouble_Inverse(const tmpl_TwoByTwoMatrixLongDouble *A);

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
extern tmpl_TwoByTwoMatrixFloat
tmpl_2x2Float_New(float a, float b, float c, float d);

extern tmpl_TwoByTwoMatrixDouble
tmpl_2x2Double_New(double a, double b, double c, double d);

extern tmpl_TwoByTwoMatrixLongDouble
tmpl_2x2LDouble_New(long double a, long double b, long double c, long double d);

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
extern tmpl_TwoByTwoMatrixFloat tmpl_2x2Float_Rotation(float theta);
extern tmpl_TwoByTwoMatrixDouble tmpl_2x2Double_Rotation(double theta);

extern tmpl_TwoByTwoMatrixLongDouble
tmpl_2x2LDouble_Rotation(long double theta);

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
extern tmpl_TwoByTwoMatrixFloat
tmpl_2x2Float_Scale(float r, const tmpl_TwoByTwoMatrixFloat *P);

extern tmpl_TwoByTwoMatrixDouble
tmpl_2x2Double_Scale(double r, const tmpl_TwoByTwoMatrixDouble *P);

extern tmpl_TwoByTwoMatrixLongDouble
tmpl_2x2LDouble_Scale(long double r, const tmpl_TwoByTwoMatrixLongDouble *P);

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
extern tmpl_TwoVectorFloat
tmpl_2DFloat_Matrix_Product(const tmpl_TwoByTwoMatrixFloat *A,
                            const tmpl_TwoVectorFloat *P);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Matrix_Product(const tmpl_TwoByTwoMatrixDouble *A,
                             const tmpl_TwoVectorDouble *P);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Matrix_Product(const tmpl_TwoByTwoMatrixLongDouble *A,
                              const tmpl_TwoVectorLongDouble *P);

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
extern tmpl_TwoVectorFloat tmpl_2DFloat_Rect(float x, float y);
extern tmpl_TwoVectorDouble tmpl_2DDouble_Rect(double x, double y);

extern tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Rect(long double x, long double y);

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
extern float
tmpl_2DFloat_Rel_Angle(const tmpl_TwoVectorFloat *O,
                       const tmpl_TwoVectorFloat *P,
                       const tmpl_TwoVectorFloat *Q);

extern double
tmpl_2DDouble_Rel_Angle(const tmpl_TwoVectorDouble *O,
                        const tmpl_TwoVectorDouble *P,
                        const tmpl_TwoVectorDouble *Q);

extern long double
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
extern tmpl_Bool
tmpl_2DFloat_Are_Collinear(const tmpl_TwoVectorFloat *A,
                           const tmpl_TwoVectorFloat *B,
                           const tmpl_TwoVectorFloat *C);

extern tmpl_Bool
tmpl_2DDouble_Are_Collinear(const tmpl_TwoVectorDouble *A,
                            const tmpl_TwoVectorDouble *B,
                            const tmpl_TwoVectorDouble *C);

extern tmpl_Bool
tmpl_2DLDouble_Are_Collinear(const tmpl_TwoVectorLongDouble *A,
                             const tmpl_TwoVectorLongDouble *B,
                             const tmpl_TwoVectorLongDouble *C);



extern tmpl_Bool
tmpl_LineSegment2D_Intersect(tmpl_TwoLineDouble L0,
                             tmpl_TwoLineDouble L1);

extern tmpl_TwoVectorDouble
tmpl_2DDouble_Point_Inverse(const tmpl_2DCircleDouble *C,
                            const tmpl_TwoVectorDouble *P);

extern tmpl_2DCircleDouble
tmpl_2DDouble_Circle_Inverse(const tmpl_2DCircleDouble *C0,
                             const tmpl_2DCircleDouble *C1);

extern tmpl_2DCircleDouble
tmpl_2DDouble_Line_Inverse(const tmpl_2DCircleDouble *C,
                           const tmpl_TwoLineDouble *L);

extern void
tmpl_2DDouble_Circle_As_Line(tmpl_2DCircleDouble *circle,
                             const tmpl_TwoVectorDouble *P,
                             const tmpl_TwoVectorDouble *V);

extern void
tmpl_2DDouble_Reset_Circle(const tmpl_2DCircleDouble *circle,
                           const tmpl_TwoVector *P, double r);

#ifdef TMPL_INLINE_FILE
#undef TMPL_INLINE_FILE
#endif

#endif
/*  End of include guard.                                                     */
