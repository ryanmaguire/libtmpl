
/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_EUCLIDEAN_PLANAR_GEOMETRY_H__
#define __TMPL_EUCLIDEAN_PLANAR_GEOMETRY_H__

/*  Data types for two dimensional points and transformations, respectively.  */
typedef struct tmpl_TwoVector {
    double dat[2];
} tmpl_TwoVector;

typedef struct tmpl_TwoByTwoMatrix {
    double dat[2][2];
} tmpl_TwoByTwoMatrix;

extern double tmpl_TwoVector_X(tmpl_TwoVector P);

extern double tmpl_TwoVector_Y(tmpl_TwoVector P);

extern tmpl_TwoVector tmpl_TwoVector_Rect(double x, double y);

extern tmpl_TwoVector
tmpl_TwoVector_Polar(double r, double theta);

extern double
tmpl_TwoByTwoMatrix_Component(tmpl_TwoByTwoMatrix A,
                                     unsigned int m, unsigned int n);
extern double
tmpl_TwoVector_Euclidean_Norm(tmpl_TwoVector P);
extern double
tmpl_TwoVector_Euclidean_Norm_Squared(tmpl_TwoVector P);
extern double
tmpl_TwoVector_Dot_Product(tmpl_TwoVector P,
                                  tmpl_TwoVector Q);
extern tmpl_TwoVector
tmpl_TwoVector_Normalize(tmpl_TwoVector P);

extern tmpl_TwoVector
tmpl_TwoVector_Add(tmpl_TwoVector P, tmpl_TwoVector Q);

extern tmpl_TwoVector
tmpl_TwoVector_Scale(double a, tmpl_TwoVector P);

#endif
/*  End of include guard.                                                     */

