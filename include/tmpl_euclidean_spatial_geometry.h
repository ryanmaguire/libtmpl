/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EUCLIDEAN_SPATIAL_GEOMETRY_H
#define TMPL_EUCLIDEAN_SPATIAL_GEOMETRY_H

/*  3D Vectors with single precision components.                              */
typedef struct tmpl_ThreeVectorFloat_Def {
    float dat[3];
} tmpl_ThreeVectorFloat;

/*  3D Vectors with double precision components.                              */
typedef struct tmpl_ThreeVectorDouble_Def {
    double dat[3];
} tmpl_ThreeVectorDouble;

/*  3D Vectors with long double precision components.                         */
typedef struct tmpl_ThreeVectorLongDouble_Def {
    long double dat[3];
} tmpl_ThreeVectorLongDouble;

/*  Most users will be fine with double precision. To make code look cleaner, *
 *  tmpl_ThreeVector is typedef'd to tmpl_ThreeVectorDouble.                  */
typedef tmpl_ThreeVectorDouble tmpl_ThreeVector;

/*  Single precision 3x3 matrix for linear transformations in R^3.            */
typedef struct tmpl_ThreeByThreeMatrixFloat_Def {
    float dat[3][3];
} tmpl_ThreeByThreeMatrixFloat;

/*  Double precision 3x3 matrix for linear transformations in R^3.            */
typedef struct tmpl_ThreeByThreeMatrixDouble_Def {
    double dat[3][3];
} tmpl_ThreeByThreeMatrixDouble;

/*  Long double precision 3x3 matrix for linear transformations in R^3.       */
typedef struct tmpl_ThreeByThreeMatrixLongDouble_Def {
    long double dat[3][3];
} tmpl_ThreeByThreeMatrixLongDouble;

/*  Again, for clean code the double precision 3x3 matrix type is typedef'd   *
 *  as tmpl_ThreeByThreeMatrix.                                               */
typedef tmpl_ThreeByThreeMatrixDouble tmpl_ThreeByThreeMatrix;

/*  Functionals f:R^3 -> R at single, double, and long double precision.      */
typedef float (*tmpl_3DFloat_Functional)(tmpl_ThreeVectorFloat);
typedef double (*tmpl_3DDouble_Functional)(tmpl_ThreeVectorDouble);
typedef long double (*tmpl_3DLDouble_Functional)(tmpl_ThreeVectorLongDouble);

/*  Vector fields F:R^3 -> R^3 at single, double, and long double precision.  */
typedef tmpl_ThreeVectorFloat
(*tmpl_3DFloat_VectorField)(tmpl_ThreeVectorFloat);

typedef tmpl_ThreeVectorDouble
(*tmpl_3DDouble_VectorField)(tmpl_ThreeVectorDouble);

typedef tmpl_ThreeVectorLongDouble
(*tmpl_3DLDouble_VectorField)(tmpl_ThreeVectorLongDouble);

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
 *      P (const tmpl_ThreeVectorFloat *):                                    *
 *          A pointer to a three dimensional vector.                          *
 *      Q (const tmpl_ThreeVectorFloat *):                                    *
 *          Another pointer to a three dimensional vector.                    *
 *  Output:                                                                   *
 *      sum (tmpl_ThreeVectorFloat):                                          *
 *          The sum of P and Q, P + Q.                                        *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_add_float.c                                     *
 *          tmpl_three_vector_add_double.c                                    *
 *          tmpl_three_vector_add_ldouble.c                                   *
 *  Examples:                                                                 *
 *      libtmpl/examples/euclidean_spatial_geometry/                          *
 *          tmpl_three_vector_add_double_example.c                            *
 *          tmpl_three_vector_add_float_example.c                             *
 *          tmpl_three_vector_add_ldouble_example.c                           *
 *  Tests:                                                                    *
 *      libtmpl/tests/euclidean_spatial_geometry/time_tests/                  *
 *          tmpl_three_vector_add_double_huge_time_test_vs_linasm.c           *
 *          tmpl_three_vector_add_double_small_time_test_vs_linasm.c          *
 *          tmpl_three_vector_add_float_huge_time_test_vs_linasm.c            *
 *          tmpl_three_vector_add_float_small_time_test_vs_linasm.c           *
 *          tmpl_three_vector_add_ldouble_huge_time_test.c                    *
 *          tmpl_three_vector_add_ldouble_small_time_test.c                   *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Add(const tmpl_ThreeVectorFloat *P,
                 const tmpl_ThreeVectorFloat *Q);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Add(const tmpl_ThreeVectorDouble *P,
                  const tmpl_ThreeVectorDouble *Q);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Add(const tmpl_ThreeVectorLongDouble *P,
                   const tmpl_ThreeVectorLongDouble *Q);

/*  Less verbose macros for vector addition.                                  */
#define tmpl_3D_Addf tmpl_3DFloat_Add
#define tmpl_3D_Add tmpl_3DDouble_Add
#define tmpl_3D_Addl tmpl_3DLDouble_Add

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
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_add_to_float.c                                  *
 *          tmpl_three_vector_add_to_double.c                                 *
 *          tmpl_three_vector_add_to_ldouble.c                                *
 *  Examples:                                                                 *
 *      libtmpl/examples/euclidean_spatial_geometry/                          *
 *          tmpl_three_vector_add_to_double_example.c                         *
 *          tmpl_three_vector_add_to_float_example.c                          *
 *          tmpl_three_vector_add_to_ldouble_example.c                        *
 *  Tests:                                                                    *
 *      libtmpl/tests/euclidean_spatial_geometry/time_tests/                  *
 *          tmpl_three_vector_add_to_double_huge_time_test_vs_linasm.c        *
 *          tmpl_three_vector_add_to_double_small_time_test_vs_linasm.c       *
 *          tmpl_three_vector_add_to_float_huge_time_test_vs_linasm.c         *
 *          tmpl_three_vector_add_to_float_small_time_test_vs_linasm.c        *
 *          tmpl_three_vector_add_to_ldouble_huge_time_test.c                 *
 *          tmpl_three_vector_add_to_ldouble_small_time_test.c                *
 ******************************************************************************/
extern void
tmpl_3DFloat_AddTo(tmpl_ThreeVectorFloat *target,
                   const tmpl_ThreeVectorFloat *source);

extern void
tmpl_3DDouble_AddTo(tmpl_ThreeVectorDouble *target,
                    const tmpl_ThreeVectorDouble *source);

extern void
tmpl_3DLDouble_AddTo(tmpl_ThreeVectorLongDouble *target,
                     const tmpl_ThreeVectorLongDouble *source);

/*  Less verbose macros for vector addition.                                  */
#define tmpl_3D_AddTof tmpl_3DFloat_AddTo
#define tmpl_3D_AddTo tmpl_3DDouble_AddTo
#define tmpl_3D_AddTol tmpl_3DLDouble_AddTo

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Cross_Product                                            *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors in R^3 at single precision. *
 *      Similar functions are provided for double and long double precisions. *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat *):                                    *
 *          A pointer to a three dimensional vector.                          *
 *      Q (const tmpl_ThreeVectorFloat *):                                    *
 *          Another pointer to a  three dimensional vector.                   *
 *  Output:                                                                   *
 *      cross (tmpl_ThreeVectorFloat):                                        *
 *          The cross product of P and Q, PxQ, in that order.                 *
 *  Notes:                                                                    *
 *      The cross product is anti-commutative. That is, PxQ = -QxP.           *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_cross_product_float.c                           *
 *          tmpl_three_vector_cross_product_double.c                          *
 *          tmpl_three_vector_cross_product_ldouble.c                         *
 *  Examples:                                                                 *
 *      libtmpl/examples/euclidean_spatial_geometry/                          *
 *          tmpl_three_vector_cross_product_double_example.c                  *
 *          tmpl_three_vector_cross_product_float_example.c                   *
 *          tmpl_three_vector_cross_product_ldouble_example.c                 *
 *  Tests:                                                                    *
 *      libtmpl/tests/euclidean_spatial_geometry/time_tests/                  *
 *          tmpl_three_vector_cross_product_double_huge_time_test_vs_linasm.c *
 *          tmpl_three_vector_cross_product_double_small_time_test_vs_linasm.c*
 *          tmpl_three_vector_cross_product_float_huge_time_test_vs_linasm.c  *
 *          tmpl_three_vector_cross_product_float_small_time_test_vs_linasm.c *
 *          tmpl_three_vector_cross_product_ldouble_huge_time_test.c          *
 *          tmpl_three_vector_cross_product_ldouble_small_time_test.c         *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Cross_Product(const tmpl_ThreeVectorFloat *P,
                           const tmpl_ThreeVectorFloat *Q);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Cross_Product(const tmpl_ThreeVectorDouble *P,
                            const tmpl_ThreeVectorDouble *Q);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Cross_Product(const tmpl_ThreeVectorLongDouble *P,
                             const tmpl_ThreeVectorLongDouble *Q);

/*  Less verbose macros for the cross product.                                */
#define tmpl_Cross_Productf tmpl_3DFloat_Cross_Product
#define tmpl_Cross_Product tmpl_3DDouble_Cross_Product
#define tmpl_Cross_Productl tmpl_3DLDouble_Cross_Product

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_CrossWith                                                *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors in R^3 at single precision. *
 *      Similar functions are provided for double and long double precisions. *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorFloat *):                                     *
 *          A pointer to a three dimensional vector. The result of the cross  *
 *          product is stored in this variable.                               *
 *      source (const tmpl_ThreeVectorFloat *):                               *
 *          Another pointer to a  three dimensional vector.                   *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      The cross product is anti-commutative. That is, PxQ = -QxP.           *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_cross_with_float.c                              *
 *          tmpl_three_vector_cross_with_double.c                             *
 *          tmpl_three_vector_cross_with_ldouble.c                            *
 *  Examples:                                                                 *
 *      libtmpl/examples/euclidean_spatial_geometry/                          *
 *          tmpl_three_vector_cross_with_double_example.c                     *
 *          tmpl_three_vector_cross_with_float_example.c                      *
 *          tmpl_three_vector_cross_with_ldouble_example.c                    *
 *  Tests:                                                                    *
 *      libtmpl/tests/euclidean_spatial_geometry/time_tests/                  *
 *          tmpl_three_vector_cross_with_double_huge_time_test_vs_linasm.c    *
 *          tmpl_three_vector_cross_with_double_small_time_test_vs_linasm.c   *
 *          tmpl_three_vector_cross_with_float_huge_time_test_vs_linasm.c     *
 *          tmpl_three_vector_cross_with_float_small_time_test_vs_linasm.c    *
 *          tmpl_three_vector_cross_with_ldouble_huge_time_test.c             *
 *          tmpl_three_vector_cross_with_ldouble_small_time_test.c            *
 ******************************************************************************/
extern void
tmpl_3DFloat_CrossWith(tmpl_ThreeVectorFloat *target,
                       const tmpl_ThreeVectorFloat *source);

extern void
tmpl_3DDouble_CrossWith(tmpl_ThreeVectorDouble *target,
                        const tmpl_ThreeVectorDouble *source);

extern void
tmpl_3DLDouble_CrossWith(tmpl_ThreeVectorLongDouble *target,
                         const tmpl_ThreeVectorLongDouble *source);

/*  Less verbose macros for the cross product.                                */
#define tmpl_CrossWithf tmpl_3DFloat_CrossWith
#define tmpl_CrossWith tmpl_3DDouble_CrossWith
#define tmpl_CrossWithl tmpl_3DLDouble_CrossWith

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Dot_Product                                              *
 *  Purpose:                                                                  *
 *      Computes the Euclidean dot product of two vector in R^3 at single     *
 *      precision. Similar functions are provided for double and long double. *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat *):                                    *
 *          A pointer to a three dimensional vector.                          *
 *      Q (const tmpl_ThreeVectorFloat *):                                    *
 *          Another pointer to a three dimensional vector.                    *
 *  Output:                                                                   *
 *      dot (float):                                                          *
 *          The dot product of P and Q, P . Q.                                *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_dot_product_float.c                             *
 *          tmpl_three_vector_dot_product_double.c                            *
 *          tmpl_three_vector_dot_product_ldouble.c                           *
 ******************************************************************************/
extern float
tmpl_3DFloat_Dot_Product(const tmpl_ThreeVectorFloat *P,
                         const tmpl_ThreeVectorFloat *Q);

extern double
tmpl_3DDouble_Dot_Product(const tmpl_ThreeVectorDouble *P,
                          const tmpl_ThreeVectorDouble *Q);

extern long double
tmpl_3DLDouble_Dot_Product(const tmpl_ThreeVectorLongDouble *P,
                           const tmpl_ThreeVectorLongDouble *Q);

/*  Less verbose macros for the Euclidean dot product.                        */
#define tmpl_3D_Dot_Productf tmpl_3DFloat_Dot_Product
#define tmpl_3D_Dot_Product tmpl_3DDouble_Dot_Product
#define tmpl_3D_Dot_Productl tmpl_3DLDoubble_Dot_Product

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Fast_L2_Normalize                                        *
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
 *      Depending on hardware and compiler used, this function is 5% to 60%   *
 *      faster than tmpl_3DFloat_Normalize.                                   *
 *                                                                            *
 *      This function can not be used with vectors P such that                *
 *      ||P|| > sqrt(FLT_MAX). On IEEE-754 compliant systems, this is about   *
 *      sqrt(10^38) = 10^19. The intermediate computation of ||P||^2 will     *
 *      overflow resulting in infinity.                                       *
 *                                                                            *
 *      No checks for NaN or Inf are performed.                               *
 *                                                                            *
 *      Most applications can use this instead of tmpl_3DFloat_Normalize and  *
 *      enjoy a decent performance boost. If unsure, or if you know you will  *
 *      be working with large vectors, use tmpl_3DFloat_Normalize.            *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_fast_normalize_float.c                          *
 *          tmpl_three_vector_fast_normalize_double.c                         *
 *          tmpl_three_vector_fast_normalize_ldouble.c                        *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Fast_Normalize(const tmpl_ThreeVectorFloat *P);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Fast_Normalize(const tmpl_ThreeVectorDouble *P);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Fast_Normalize(tmpl_ThreeVectorLongDouble *P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Fast_L2_Norm                                             *
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
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_fast_norm_float.c                               *
 *          tmpl_three_vector_fast_norm_double.c                              *
 *          tmpl_three_vector_fast_norm_ldouble.c                             *
 ******************************************************************************/
extern float tmpl_3DFloat_Fast_L2_Norm(tmpl_ThreeVectorFloat *P);
extern double tmpl_3DDouble_Fast_L2_Norm(tmpl_ThreeVectorDouble *P);
extern long double tmpl_3DLDouble_Fast_L2_Norm(tmpl_ThreeVectorLongDouble *P);

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
tmpl_3DDouble_Normalize(tmpl_ThreeVectorDouble *P);

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

extern double
tmpl_ThreeByThreeMatrix_Component(tmpl_ThreeByThreeMatrix A,
                                  unsigned int m, unsigned int n);

#endif
/*  End of include guard.                                                     */
