/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_H
#define TMPL_VEC3_H

/*  TMPL_USE_INLINE macro is found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Typedefs for 3D vectors at various precisions.                            */
#include <libtmpl/include/tmpl_vec3_double.h>
#include <libtmpl/include/tmpl_vec3_float.h>
#include <libtmpl/include/tmpl_vec3_ldouble.h>

/*  Functionals f:R^3 -> R at single, double, and long double precision.      */
typedef float
(*tmpl_3DFloat_Functional)(const tmpl_ThreeVectorFloat * const);

typedef double
(*tmpl_3DDouble_Functional)(const tmpl_ThreeVectorDouble * const);

typedef long double
(*tmpl_3DLDouble_Functional)(const tmpl_ThreeVectorLongDouble * const);

/*  Vector fields F:R^3 -> R^3 at single, double, and long double precision.  */
typedef tmpl_ThreeVectorFloat
(*tmpl_3DFloat_VectorField)(const tmpl_ThreeVectorFloat * const);

typedef tmpl_ThreeVectorDouble
(*tmpl_3DDouble_VectorField)(const tmpl_ThreeVectorDouble * const);

typedef tmpl_ThreeVectorLongDouble
(*tmpl_3DLDouble_VectorField)(const tmpl_ThreeVectorLongDouble * const);

/*  Commonly used vectors in R^3.                                             */
extern const tmpl_ThreeVectorFloat tmpl_3DFloat_Zero;
extern const tmpl_ThreeVectorDouble tmpl_3DDouble_Zero;
extern const tmpl_ThreeVectorLongDouble tmpl_3DLDouble_Zero;

extern const tmpl_ThreeVectorFloat tmpl_3DFloat_X_Hat;
extern const tmpl_ThreeVectorDouble tmpl_3DDouble_X_Hat;
extern const tmpl_ThreeVectorLongDouble tmpl_3DLDouble_X_Hat;

extern const tmpl_ThreeVectorFloat tmpl_3DFloat_Y_Hat;
extern const tmpl_ThreeVectorDouble tmpl_3DDouble_Y_Hat;
extern const tmpl_ThreeVectorLongDouble tmpl_3DLDouble_Y_Hat;

extern const tmpl_ThreeVectorFloat tmpl_3DFloat_Z_Hat;
extern const tmpl_ThreeVectorDouble tmpl_3DDouble_Z_Hat;
extern const tmpl_ThreeVectorLongDouble tmpl_3DLDouble_Z_Hat;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Add                                                      *
 *  Purpose:                                                                  *
 *      Computes the vector sum of two vectors in R^3 at single precision.    *
 *      Similar functions are provided for double and long double precisions. *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to a three dimensional vector.                          *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          Another pointer to a three dimensional vector.                    *
 *  Output:                                                                   *
 *      sum (tmpl_ThreeVectorFloat):                                          *
 *          The sum of P and Q, P + Q.                                        *
 *  Source Code:                                                              *
 *      libtmpl/src/vec3/                                                     *
 *          tmpl_vec3_add_no_inline_float.c                                   *
 *          tmpl_vec3_add_no_inline_double.c                                  *
 *          tmpl_vec3_add_no_inline_ldouble.c                                 *
 *      libtmpl/include/vec3/                                                 *
 *          tmpl_vec3_add_float.h                                             *
 *          tmpl_vec3_add_double.h                                            *
 *          tmpl_vec3_add_ldouble.h                                           *
 ******************************************************************************/

/*  Arithmetic functions are very small and can be inlined.                   */
#if TMPL_USE_INLINE == 1

/*  Include versions found here.                                              */
#include <libtmpl/include/vec3/tmpl_vec3_add_float.h>
#include <libtmpl/include/vec3/tmpl_vec3_add_double.h>
#include <libtmpl/include/vec3/tmpl_vec3_add_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise, use the versions found in src/vec3/.                           */
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Add(const tmpl_ThreeVectorFloat * const P,
                 const tmpl_ThreeVectorFloat * const Q);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Add(const tmpl_ThreeVectorDouble * const P,
                  const tmpl_ThreeVectorDouble * const Q);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Add(const tmpl_ThreeVectorLongDouble * const P,
                   const tmpl_ThreeVectorLongDouble * const Q);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_AddTo                                                    *
 *  Purpose:                                                                  *
 *      Adds the source vector to the target vector, the result of which is   *
 *      stored in the target.                                                 *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorFloat *):                                     *
 *          A pointer to the first vector, the sum will be stored here.       *
 *      source (tmpl_ThreeVectorFloat *):                                     *
 *          A pointer to the vector to be added to target.                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/vec3/                                                     *
 *          tmpl_vec3_add_to_no_inline_float.c                                *
 *          tmpl_vec3_add_to_no_inline_double.c                               *
 *          tmpl_vec3_add_to_no_inline_ldouble.c                              *
 *      libtmpl/include/vec3/                                                 *
 *          tmpl_vec3_add_to_float.h                                          *
 *          tmpl_vec3_add_to_double.h                                         *
 *          tmpl_vec3_add_to_ldouble.h                                        *
 ******************************************************************************/

/*  Arithmetic functions are very small and can be inlined.                   */
#if TMPL_USE_INLINE == 1

/*  Include versions found here.                                              */
#include <libtmpl/include/vec3/tmpl_vec3_add_to_float.h>
#include <libtmpl/include/vec3/tmpl_vec3_add_to_double.h>
#include <libtmpl/include/vec3/tmpl_vec3_add_to_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise, use the versions found in src/vec3/.                           */
extern void
tmpl_3DFloat_AddTo(tmpl_ThreeVectorFloat * const target,
                   const tmpl_ThreeVectorFloat * const source);

extern void
tmpl_3DDouble_AddTo(tmpl_ThreeVectorDouble * const target,
                    const tmpl_ThreeVectorDouble * const source);

extern void
tmpl_3DLDouble_AddTo(tmpl_ThreeVectorLongDouble * const target,
                     const tmpl_ThreeVectorLongDouble * const source);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Angle                                                    *
 *  Purpose:                                                                  *
 *      Safely computes the angle between two vectors.                        *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to the first vector.                                    *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          Another pointer to a vector.                                      *
 *  Output:                                                                   *
 *      angle (double):                                                       *
            The angle made between P and Q.                                   *
 *  Source Code:                                                              *
 *      libtmpl/src/vec3/                                                     *
 *          tmpl_vec3_add_to_no_inline_float.c                                *
 *          tmpl_vec3_add_to_no_inline_double.c                               *
 *          tmpl_vec3_add_to_no_inline_ldouble.c                              *
 ******************************************************************************/
extern float
tmpl_3DFloat_Angle(const tmpl_ThreeVectorFloat * const P,
                   const tmpl_ThreeVectorFloat * const Q);

extern double
tmpl_3DDouble_Angle(const tmpl_ThreeVectorDouble * const P,
                    const tmpl_ThreeVectorDouble * const Q);

extern long double
tmpl_3DLDouble_Angle(const tmpl_ThreeVectorLongDouble * const P,
                     const tmpl_ThreeVectorLongDouble * const Q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Cross_Product                                            *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors in R^3 at single precision. *
 *      Similar functions are provided for double and long double precisions. *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to a three dimensional vector.                          *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          Another pointer to a  three dimensional vector.                   *
 *  Output:                                                                   *
 *      cross (tmpl_ThreeVectorFloat):                                        *
 *          The cross product of P and Q, PxQ, in that order.                 *
 *  Notes:                                                                    *
 *      The cross product is anti-commutative. That is, PxQ = -QxP.           *
 *  Source Code:                                                              *
 *      libtmpl/src/vec3/                                                     *
 *          tmpl_vec3_cross_product_no_inline_float.c                         *
 *          tmpl_vec3_cross_product_no_inline_double.c                        *
 *          tmpl_vec3_cross_product_no_inline_ldouble.c                       *
 *      libtmpl/include/vec3/                                                 *
 *          tmpl_vec3_cross_product_float.h                                   *
 *          tmpl_vec3_cross_product_double.h                                  *
 *          tmpl_vec3_cross_product_ldouble.h                                 *
 ******************************************************************************/

/*  The cross product consists of a few lines of arithmetic. We can inline.   */
#if TMPL_USE_INLINE == 1

/*  Include versions found here.                                              */
#include <libtmpl/include/vec3/tmpl_vec3_cross_product_float.h>
#include <libtmpl/include/vec3/tmpl_vec3_cross_product_double.h>
#include <libtmpl/include/vec3/tmpl_vec3_cross_product_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise, use the versions found in src/vec3/.                           */
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Cross_Product(const tmpl_ThreeVectorFloat * const P,
                           const tmpl_ThreeVectorFloat * const Q);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Cross_Product(const tmpl_ThreeVectorDouble * const P,
                            const tmpl_ThreeVectorDouble * const Q);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Cross_Product(const tmpl_ThreeVectorLongDouble * const P,
                             const tmpl_ThreeVectorLongDouble * const Q);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_CrossWith                                                *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors in R^3 at single precision. *
 *      Similar functions are provided for double and long double precisions. *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorFloat * const):                               *
 *          A pointer to a three dimensional vector. The result of the cross  *
 *          product is stored in this variable.                               *
 *      source (const tmpl_ThreeVectorFloat * const):                         *
 *          Another pointer to a  three dimensional vector.                   *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      The cross product is anti-commutative. That is, PxQ = -QxP.           *
 *  Source Code:                                                              *
 *      libtmpl/src/vec3/                                                     *
 *          tmpl_vec3_cross_with_no_inline_float.c                            *
 *          tmpl_vec3_cross_with_no_inline_double.c                           *
 *          tmpl_vec3_cross_with_no_inline_ldouble.c                          *
 *      libtmpl/include/vec3/                                                 *
 *          tmpl_vec3_cross_with_float.h                                      *
 *          tmpl_vec3_cross_with_double.h                                     *
 *          tmpl_vec3_cross_with_ldouble.h                                    *
 ******************************************************************************/

/*  This function is only a few lines. We can inline it.                      */
#if TMPL_USE_INLINE == 1

/*  Include versions found here.                                              */
#include <libtmpl/include/vec3/tmpl_vec3_cross_with_float.h>
#include <libtmpl/include/vec3/tmpl_vec3_cross_with_double.h>
#include <libtmpl/include/vec3/tmpl_vec3_cross_with_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

extern void
tmpl_3DFloat_CrossWith(tmpl_ThreeVectorFloat * const target,
                       const tmpl_ThreeVectorFloat * const source);

extern void
tmpl_3DDouble_CrossWith(tmpl_ThreeVectorDouble * const target,
                        const tmpl_ThreeVectorDouble * const source);

extern void
tmpl_3DLDouble_CrossWith(tmpl_ThreeVectorLongDouble * const target,
                         const tmpl_ThreeVectorLongDouble * const source);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Dot_Product                                              *
 *  Purpose:                                                                  *
 *      Computes the Euclidean dot product of two vector in R^3 at single     *
 *      precision. Similar functions are provided for double and long double. *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to a three dimensional vector.                          *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          Another pointer to a three dimensional vector.                    *
 *  Output:                                                                   *
 *      dot (float):                                                          *
 *          The dot product of P and Q, P . Q.                                *
 *  Source Code:                                                              *
 *      libtmpl/src/vec3/                                                     *
 *          tmpl_vec3_dot_product_no_inline_float.c                           *
 *          tmpl_vec3_dot_product_no_inline_double.c                          *
 *          tmpl_vec3_dot_product_no_inline_ldouble.c                         *
 *      libtmpl/include/vec3/                                                 *
 *          tmpl_vec3_dot_product_float.h                                     *
 *          tmpl_vec3_dot_product_double.h                                    *
 *          tmpl_vec3_dot_product_ldouble.h                                   *
 ******************************************************************************/

/*  The dot product is a one-line. Definitely worth inlining.                 */
#if TMPL_USE_INLINE == 1

/*  Include versions found here.                                              */
#include <libtmpl/include/vec3/tmpl_vec3_dot_product_float.h>
#include <libtmpl/include/vec3/tmpl_vec3_dot_product_double.h>
#include <libtmpl/include/vec3/tmpl_vec3_dot_product_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */
extern float
tmpl_3DFloat_Dot_Product(const tmpl_ThreeVectorFloat * const P,
                         const tmpl_ThreeVectorFloat * const Q);

extern double
tmpl_3DDouble_Dot_Product(const tmpl_ThreeVectorDouble * const P,
                          const tmpl_ThreeVectorDouble * const Q);

extern long double
tmpl_3DLDouble_Dot_Product(const tmpl_ThreeVectorLongDouble * const P,
                           const tmpl_ThreeVectorLongDouble * const Q);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_L1_Norm                                                  *
 *  Purpose:                                                                  *
 *      Computes the L1 norm of a vector in R^3 at single precision. This is  *
 *      defined as follows. If P = (x, y, z), we have:                        *
 *          ||P||_1 = |x| + |y| + |z|                                         *
 *      Functions for double and long double precision are also provided.     *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          A three dimensional vector.                                       *
 *  Output:                                                                   *
 *      norm (float):                                                         *
 *          The L1 norm of P.                                                 *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_l1_norm_float.c                                 *
 *          tmpl_three_vector_l1_norm_double.c                                *
 *          tmpl_three_vector_l1_norm_ldouble.c                               *
 ******************************************************************************/
extern float tmpl_3DFloat_L1_Norm(tmpl_ThreeVectorFloat P);
extern double tmpl_3DDouble_L1_Norm(tmpl_ThreeVectorDouble P);
extern long double tmpl_3DLDouble_L1_Norm(tmpl_ThreeVectorLongDouble P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_L2_Norm                                                  *
 *  Purpose:                                                                  *
 *      Computes the Euclidean L2 norm of a vector in R^3. This is defined by *
 *      the Pythagorean theorem as follows. If P = (x, y, z), we have:        *
 *          ||P|| = sqrt(x^2 + y^2 + z^2)                                     *
 *      Functions for single, double, and long double precision are provided. *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          A three dimensional vector.                                       *
 *  Output:                                                                   *
 *      norm (float):                                                         *
 *          The Euclidean norm of P.                                          *
 *  Notes:                                                                    *
 *      If P is the zero vector, the vector (NaN, NaN, NaN) is returned.      *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_norm_float.c                                    *
 *          tmpl_three_vector_norm_double.c                                   *
 *          tmpl_three_vector_norm_ldouble.c                                  *
 ******************************************************************************/
extern float tmpl_3DFloat_L2_Norm(const tmpl_ThreeVectorFloat *P);
extern double tmpl_3DDouble_L2_Norm(const tmpl_ThreeVectorDouble *P);
extern long double tmpl_3DLDouble_L2_Norm(const tmpl_ThreeVectorLongDouble *P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_LInf_Norm                                                *
 *  Purpose:                                                                  *
 *      Computes the L-Infinity norm of a vector in R^3 at single precision.  *
 *      This is defined as follows. If P = (x, y, z), we have:                *
 *          ||P||_infinity = max(|x|, |y|, |z|)                               *
 *      Functions for double and long double precision are also provided.     *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          A three dimensional vector.                                       *
 *  Output:                                                                   *
 *      norm (float):                                                         *
 *          The L1 norm of P.                                                 *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_linf_norm_float.c                               *
 *          tmpl_three_vector_linf_norm_double.c                              *
 *          tmpl_three_vector_linf_norm_ldouble.c                             *
 ******************************************************************************/
extern float tmpl_3DFloat_LInf_Norm(tmpl_ThreeVectorFloat P);
extern double tmpl_3DDouble_LInf_Norm(tmpl_ThreeVectorDouble P);
extern long double tmpl_3DLDouble_LInf_Norm(tmpl_ThreeVectorLongDouble P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Normalize                                                *
 *  Purpose:                                                                  *
 *      Computes the unit normal of a given non-zero vector at single         *
 *      precision. Similar functions are provided for double and long double. *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          A three dimensional non-zero vector.                              *
 *  Output:                                                                   *
 *      P_hat (tmpl_ThreeVectorFloat):                                        *
 *          The unit-normal of P.                                             *
 *  Notes:                                                                    *
 *      If P is the zero vector, the vector (NaN, NaN, NaN) is returned.      *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_normalize_float.c                               *
 *          tmpl_three_vector_normalize_double.c                              *
 *          tmpl_three_vector_normalize_ldouble.c                             *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Normalize(tmpl_ThreeVectorFloat P);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Normalize(const tmpl_ThreeVectorDouble *P);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Normalize(tmpl_ThreeVectorLongDouble P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Orthogonal                                               *
 *  Purpose:                                                                  *
 *      Returns a non-zero vector orthogonal to the input.                    *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          A 3D vector.                                                      *
 *  Output:                                                                   *
 *      orth (tmpl_ThreeVectorFloat):                                         *
 *          A non-zero vector orthogonal to the input.                        *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_orthogonal_float.c                              *
 *          tmpl_three_vector_orthogonal_double.c                             *
 *          tmpl_three_vector_orthogonal_ldouble.c                            *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Orthogonal(tmpl_ThreeVectorFloat P);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Orthogonal(tmpl_ThreeVectorDouble P);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Orthogonal(tmpl_ThreeVectorLongDouble P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Rect                                                     *
 *  Purpose:                                                                  *
 *      Creates a 3D vector from three real numbers.                          *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          The x-component of the vector.                                    *
 *      y (float):                                                            *
 *          The y-component of the vector.                                    *
 *      z (float):                                                            *
 *          The z-component of the vector.                                    *
 *  Output:                                                                   *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          The vector (x, y, z).                                             *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_rect_float.c                                    *
 *          tmpl_three_vector_rect_double.c                                   *
 *          tmpl_three_vector_rect_ldouble.c                                  *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Rect(float x, float y, float z);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Rect(double x, double y, double z);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Rect(long double x, long double y, long double z);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Scale                                                    *
 *  Purpose:                                                                  *
 *      Multiply a 3D vector by a real number.                                *
 *  Arguments:                                                                *
 *      a (float):                                                            *
 *          A real number.                                                    *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          A 3D vector.                                                      *
 *  Output:                                                                   *
 *      scaled (tmpl_ThreeVectorFloat):                                       *
 *          The product a*P = a*(x, y, z) = (ax, ay, az).                     *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_scale_float.c                                   *
 *          tmpl_three_vector_scale_double.c                                  *
 *          tmpl_three_vector_scale_ldouble.c                                 *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Scale(float a, tmpl_ThreeVectorFloat P);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Scale(double a, tmpl_ThreeVectorDouble P);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Scale(long double a, tmpl_ThreeVectorLongDouble P);

extern float tmpl_3DFloat_X(const tmpl_ThreeVectorFloat *P);
extern double tmpl_3DDouble_X(const tmpl_ThreeVectorDouble *P);
extern long double tmpl_3DLDouble_X(const tmpl_ThreeVectorLongDouble *P);

extern float tmpl_3DFloat_Y(const tmpl_ThreeVectorFloat *P);
extern double tmpl_3DDouble_Y(const tmpl_ThreeVectorDouble *P);
extern long double tmpl_3DLDouble_Y(const tmpl_ThreeVectorLongDouble *P);

extern float tmpl_3DFloat_Z(const tmpl_ThreeVectorFloat *P);
extern double tmpl_3DDouble_Z(const tmpl_ThreeVectorDouble *P);
extern long double tmpl_3DLDouble_Z(const tmpl_ThreeVectorLongDouble *P);

#endif
/*  End of include guard.                                                     */
