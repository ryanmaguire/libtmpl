
#ifndef TMPL_SPHERICAL_GEOMETRY_H
#define TMPL_SPHERICAL_GEOMETRY_H

#include <libtmpl/include/tmpl_vec2.h>
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>


TMPL_EXPORT extern tmpl_ThreeVector
tmpl_Inverse_Orthographic_Projection(tmpl_TwoVector P, tmpl_ThreeVector u);

TMPL_EXPORT extern tmpl_ThreeVector
tmpl_Inverse_Orthographic_Projection_Torus(tmpl_TwoVector P,
                                           double r, double R);

TMPL_EXPORT extern tmpl_TwoVector
tmpl_Stereographic_Projection(tmpl_ThreeVector P);

TMPL_EXPORT extern tmpl_TwoVector
tmpl_Stereographic_Projection_Torus(double u, double v, double r, double R);

#endif
