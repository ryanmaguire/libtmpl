/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EUCLIDEAN_SPATIAL_GEOMETRY_H
#define TMPL_EUCLIDEAN_SPATIAL_GEOMETRY_H

/*  Data types for three dimensional points and transformations, respectively.*/
typedef struct tmpl_ThreeVector {
    double dat[3];
} tmpl_ThreeVector;

typedef struct tmpl_ThreeByThreeMatrix {
    double dat[3][3];
} tmpl_ThreeByThreeMatrix;

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
tmpl_Cross_Product(tmpl_ThreeVector P, tmpl_ThreeVector Q);

extern tmpl_ThreeVector
tmpl_ThreeVector_Add(tmpl_ThreeVector P, tmpl_ThreeVector Q);

extern tmpl_ThreeVector
tmpl_ThreeVector_Scale(double a, tmpl_ThreeVector P);

extern tmpl_ThreeVector
tmpl_Orthogonal_ThreeVector(tmpl_ThreeVector P);

#endif
/*  End of include guard: #ifndef __TMPL_EUCLIDEAN_SPATIAL_GEOMETRY_H__       */
