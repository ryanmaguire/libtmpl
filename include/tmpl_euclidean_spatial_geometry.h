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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Cross_Product                                                    *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors in R^3.                     *
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
 *          tmpl_cross_product_float.c                                        *
 *          tmpl_cross_product_double.c                                       *
 *          tmpl_cross_product_ldouble.c                                      *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes_examples/tmpl_determine_endianness_example.c   *
 ******************************************************************************/
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Cross_Product(tmpl_ThreeVectorFloat P, tmpl_ThreeVectorFloat Q);

extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Cross_Product(tmpl_ThreeVectorDouble P, tmpl_ThreeVectorDouble Q);

extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Cross_Product(tmpl_ThreeVectorLongDouble P,
                             tmpl_ThreeVectorLongDouble Q);

#define tmpl_Cross_Product tmpl_3DDouble_Cross_Product

extern double tmpl_ThreeVector_X(tmpl_ThreeVector P);

extern double tmpl_ThreeVector_Y(tmpl_ThreeVector P);

extern double tmpl_ThreeVector_Z(tmpl_ThreeVector P);

extern double
tmpl_ThreeByThreeMatrix_Component(tmpl_ThreeByThreeMatrix A,
                                  unsigned int m, unsigned int n);

extern tmpl_ThreeVector
tmpl_ThreeVector_Rect(double x, double y, double z);

extern double tmpl_ThreeVector_Euclidean_Norm(tmpl_ThreeVector P);

extern double
tmpl_ThreeVector_Dot_Product(tmpl_ThreeVector P, tmpl_ThreeVector Q);

extern tmpl_ThreeVector
tmpl_ThreeVector_Normalize(tmpl_ThreeVector P);

extern tmpl_ThreeVector
tmpl_ThreeVector_Add(tmpl_ThreeVector P, tmpl_ThreeVector Q);

extern tmpl_ThreeVector
tmpl_ThreeVector_Scale(double a, tmpl_ThreeVector P);

extern tmpl_ThreeVector
tmpl_Orthogonal_ThreeVector(tmpl_ThreeVector P);

#endif
/*  End of include guard: #ifndef __TMPL_EUCLIDEAN_SPATIAL_GEOMETRY_H__       */
