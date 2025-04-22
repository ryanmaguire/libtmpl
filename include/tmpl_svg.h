#ifndef TMPL_SVG_H
#define TMPL_SVG_H

#include <libtmpl/include/types/tmpl_vec2_double.h>
#include <libtmpl/include/types/tmpl_pen_type.h>
#include <libtmpl/include/types/tmpl_svg_canvas.h>
#include <libtmpl/include/types/tmpl_svg_type.h>

extern void
tmpl_SVGCanvas_Init(tmpl_SVGCanvas *canvas,
                    unsigned int width, unsigned int height,
                    double x_min, double x_max,
                    double y_min, double y_max,
                    const tmpl_RGB24 * const background,
                    const tmpl_Pen * const outline);

extern void
tmpl_SVGCanvas_Init_Default(tmpl_SVGCanvas *canvas);

extern tmpl_TwoVectorDouble
tmpl_SVGCanvas_Transform(const tmpl_SVGCanvas * const canvas,
                         const tmpl_TwoVectorDouble point);

extern void
tmpl_SVG_Init_Default(tmpl_SVG *svg, const char * const filename);

extern void
tmpl_SVG_Init(tmpl_SVG *svg,
              const char * const filename,
              const tmpl_SVGCanvas * const canvas);

#endif
