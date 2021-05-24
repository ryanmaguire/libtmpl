
#ifndef TMPL_SPHERICAL_GEOMETRY_H
#define TMPL_SPHERICAL_GEOMETRY_H

#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>


extern tmpl_ThreeVector
tmpl_Inverse_Orthographic_Projection(tmpl_TwoVector P, tmpl_ThreeVector u);

extern tmpl_ThreeVector
tmpl_Inverse_Orthographic_Projection_Torus(tmpl_TwoVector P,
                                           double r, double R);

extern tmpl_TwoVector
tmpl_Stereographic_Projection(tmpl_ThreeVector P);

extern tmpl_TwoVector
tmpl_Stereographic_Projection_Torus(double u, double v, double r, double R);

#endif

