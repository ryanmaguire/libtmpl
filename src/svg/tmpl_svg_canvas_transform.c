#include <libtmpl/include/types/tmpl_vec2_double.h>
#include <libtmpl/include/types/tmpl_svg_canvas.h>
#include <libtmpl/include/tmpl_svg.h>

tmpl_TwoVectorDouble
tmpl_SVGCanvas_Transform(const tmpl_SVGCanvas * const canvas,
                         const tmpl_TwoVectorDouble point)
{
    tmpl_TwoVectorDouble out;

    out.dat[0] = canvas->x_shift + canvas->x_scale * point.dat[0];
    out.dat[1] = canvas->y_shift - canvas->y_scale * point.dat[1];
    return out;
}
