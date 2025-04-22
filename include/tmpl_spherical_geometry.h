
#ifndef TMPL_SPHERICAL_GEOMETRY_H
#define TMPL_SPHERICAL_GEOMETRY_H

#include <libtmpl/include/tmpl_vec2.h>
#include <libtmpl/include/tmpl_vec3.h>

extern tmpl_ThreeVectorDouble
tmpl_Inverse_Orthographic_Projection(tmpl_TwoVector P,
                                     tmpl_ThreeVectorDouble u);

extern tmpl_ThreeVectorDouble
tmpl_Inverse_Orthographic_Projection_Torus(tmpl_TwoVector P,
                                           double r, double R);

extern tmpl_TwoVector
tmpl_Stereographic_Projection(tmpl_ThreeVectorDouble P);

extern tmpl_TwoVector
tmpl_Stereographic_Projection_Torus(double u, double v, double r, double R);

#endif
