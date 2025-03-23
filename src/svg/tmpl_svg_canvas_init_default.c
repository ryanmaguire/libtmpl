#include <libtmpl/include/types/tmpl_svg_canvas.h>

extern const tmpl_SVGCanvas tmpl_SVGCanvas_Default;
extern void tmpl_SVGCanvas_Init_Default(tmpl_SVGCanvas *canvas);

void tmpl_SVGCanvas_Init_Default(tmpl_SVGCanvas *canvas)
{
    if (!canvas)
        return;

    *canvas = tmpl_SVGCanvas_Default;
}
