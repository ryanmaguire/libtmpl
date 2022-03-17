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

typedef struct tmpl_ThreeByThreeMatrixFloat_Def {
    float dat[3][3];
} tmpl_ThreeByThreeMatrixFloat;

typedef struct tmpl_ThreeByThreeMatrixDouble_Def {
    double dat[3][3];
} tmpl_ThreeByThreeMatrixDouble;

typedef struct tmpl_ThreeByThreeMatrixLongDouble_Def {
    long double dat[3][3];
} tmpl_ThreeByThreeMatrixLongDouble;

typedef tmpl_ThreeByThreeMatrixDouble tmpl_ThreeByThreeMatrix;

/*  Commonly used types of functions.                                         */
typedef float (*tmpl_3DFloat_Functional)(tmpl_ThreeVectorFloat);
typedef double (*tmpl_3DDouble_Functional)(tmpl_ThreeVectorDouble);
typedef long double (*tmpl_3DLDouble_Functional)(tmpl_ThreeVectorLongDouble);

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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Add                                                      *
 *  Purpose:                                                                  *
 *      Computes the vector sum of two vectors in R^3 at single precision.    *
 *      Similar functions are provided for double and long double precisions. *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          A three dimensional vector.                                       *
 *      Q (tmpl_ThreeVectorFloat):                                            *
 *          Another three dimensional vector.                                 *
 *  Output:                                                                   *
 *      sum (tmpl_ThreeVectorFloat):                                          *
 *          The sum of P and Q, P + Q.                                        *
 *  Source Code:                                                              *
 *      libtmpl/src/euclidean_spatial_geometry/                               *
 *          tmpl_three_vector_add_float.c                                     *
 *          tmpl_three_vector_add_double.c                                    *
 *          tmpl_three_vector_add_ldouble.c                                   *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Add(tmpl_ThreeVectorFloat P, tmpl_ThreeVectorFloat Q);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Add(tmpl_ThreeVectorDouble P, tmpl_ThreeVectorDouble Q);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Add(tmpl_ThreeVectorLongDouble P, tmpl_ThreeVectorLongDouble Q);

/*  Less verbose macros for vector addition.                                  */
#define tmpl_3D_Addf tmpl_3DFloat_Add
#define tmpl_3D_Add tmpl_3DDouble_Add
#define tmpl_3D_Addl tmpl_3DLDouble_Add

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Ptr_Add_To                                               *
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
 *          tmpl_three_vector_norm_float.c                                    *
 *          tmpl_three_vector_norm_double.c                                   *
 *          tmpl_three_vector_norm_ldouble.c                                  *
 ******************************************************************************/
extern void
tmpl_3DFloat_AddTo(tmpl_ThreeVectorFloat *target,
                   tmpl_ThreeVectorFloat *source);

extern void
tmpl_3DDouble_AddTo(tmpl_ThreeVectorDouble *target,
                    tmpl_ThreeVectorDouble *source);

extern void
tmpl_3DLDouble_AddTo(tmpl_ThreeVectorLongDouble *target,
                     tmpl_ThreeVectorLongDouble *source);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Cross_Product                                            *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors in R^3 at single precision. *
 *      Similar functions are provided for double and long double precisions. *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          A three dimensional vector.                                       *
 *      Q (tmpl_ThreeVectorFloat):                                            *
 *          Another three dimensional vector.                                 *
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
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Cross_Product(tmpl_ThreeVectorFloat P, tmpl_ThreeVectorFloat Q);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Cross_Product(tmpl_ThreeVectorDouble P, tmpl_ThreeVectorDouble Q);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Cross_Product(tmpl_ThreeVectorLongDouble P,
                             tmpl_ThreeVectorLongDouble Q);

/*  Less verbose macros for the cross product.                                */
#define tmpl_Cross_Productf tmpl_3DFloat_Cross_Product
#define tmpl_Cross_Product tmpl_3DDouble_Cross_Product
#define tmpl_Cross_Productl tmpl_3DLDouble_Cross_Product

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Dot_Product                                              *
 *  Purpose:                                                                  *
 *      Computes the Euclidean dot product of two vector in R^3 at single     *
 *      precision. Similar functions are provided for double and long double. *
 *  Arguments:                                                                *
 *      P (tmpl_ThreeVectorFloat):                                            *
 *          A three dimensional vector.                                       *
 *      Q (tmpl_ThreeVectorFloat):                                            *
 *          Another three dimensional vector.                                 *
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
tmpl_3DFloat_Dot_Product(tmpl_ThreeVectorFloat P, tmpl_ThreeVectorFloat Q);

extern double
tmpl_3DDouble_Dot_Product(tmpl_ThreeVectorDouble P, tmpl_ThreeVectorDouble Q);

extern long double
tmpl_3DLDouble_Dot_Product(tmpl_ThreeVectorLongDouble P,
                           tmpl_ThreeVectorLongDouble Q);

/*  Less verbose macros for the Euclidean dot product.                        */
#define tmpl_3D_Dot_Productf tmpl_3DDFloat_Dot_Product
#define tmpl_3D_Dot_Product tmpl_3DDouble_Dot_Product
#define tmpl_3D_Dot_Productl tmpl_3DLDoubble_Dot_Product

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Fast_Normalize                                           *
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
 *          tmpl_three_vector_Fast_normalize_float.c                          *
 *          tmpl_three_vector_Fast_normalize_double.c                         *
 *          tmpl_three_vector_Fast_normalize_ldouble.c                        *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Fast_Normalize(tmpl_ThreeVectorFloat P);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Fast_Normalize(tmpl_ThreeVectorDouble P);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Fast_Normalize(tmpl_ThreeVectorLongDouble P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Fast_Norm                                                *
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
extern float tmpl_3DFloat_Fast_Norm(tmpl_ThreeVectorFloat P);
extern double tmpl_3DDouble_Fast_Norm(tmpl_ThreeVectorDouble P);
extern long double tmpl_3DLDouble_Fast_Norm(tmpl_ThreeVectorLongDouble P);

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
 *          tmpl_three_vector_norm_float.c                                    *
 *          tmpl_three_vector_norm_double.c                                   *
 *          tmpl_three_vector_norm_ldouble.c                                  *
 ******************************************************************************/
extern float tmpl_3DFloat_L1_Norm(tmpl_ThreeVectorFloat P);
extern double tmpl_3DDouble_L1_Norm(tmpl_ThreeVectorDouble P);
extern long double tmpl_3DLDouble_L1_Norm(tmpl_ThreeVectorLongDouble P);

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
tmpl_3DDouble_Normalize(tmpl_ThreeVectorDouble P);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Normalize(tmpl_ThreeVectorLongDouble P);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DFloat_Norm                                                     *
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
extern float tmpl_3DFloat_Norm(tmpl_ThreeVectorFloat P);
extern double tmpl_3DDouble_Norm(tmpl_ThreeVectorDouble P);
extern long double tmpl_3DLDouble_Norm(tmpl_ThreeVectorLongDouble P);

#define tmpl_3D_Norm tmpl_3DDouble_Norm
#define tmpl_3DFloat_L2_Norm tmpl_3DFloat_Norm
#define tmpl_3DDouble_L2_Norm tmpl_3DDouble_Norm
#define tmpl_3DLDouble_L2_Norm tmpl_3DLDouble_Norm
#define tmpl_3D_L2_Norm tmpl_3DDouble_Norm

extern double tmpl_ThreeVector_X(tmpl_ThreeVector P);

extern double tmpl_ThreeVector_Y(tmpl_ThreeVector P);

extern double tmpl_ThreeVector_Z(tmpl_ThreeVector P);

extern double
tmpl_ThreeByThreeMatrix_Component(tmpl_ThreeByThreeMatrix A,
                                  unsigned int m, unsigned int n);

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
 *          tmpl_three_vector_norm_float.c                                    *
 *          tmpl_three_vector_norm_double.c                                   *
 *          tmpl_three_vector_norm_ldouble.c                                  *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat tmpl_3DFloat_Rect(float x, float y, float z);
extern tmpl_ThreeVectorDouble tmpl_3DDouble_Rect(double x, double y, double z);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Rect(long double x, long double y, long double z);

extern tmpl_ThreeVector
tmpl_ThreeVector_Scale(double a, tmpl_ThreeVector P);

extern tmpl_ThreeVector
tmpl_Orthogonal_ThreeVector(tmpl_ThreeVector P);

#endif
/*  End of include guard.                                                     */
