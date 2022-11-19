#ifndef TMPL_INVERSIVE_H
#define TMPL_INVERSIVE_H

#include "tmpl_exports.h"

#include <libtmpl/include/tmpl_vec2.h>

extern tmpl_TwoVector
kissvg_InversiveGeometry_Point_Inverse(tmpl_Circle2D *C, tmpl_TwoVector P);

extern tmpl_Circle2D *
kissvg_InversiveGeometry_Circle_Inverse(tmpl_Circle2D *C0, tmpl_Circle2D *C1);

extern tmpl_Circle2D *
kissvg_InversiveGeometry_Line_Inverse(tmpl_Circle2D *C, tmpl_Line2D *L);
#endif
