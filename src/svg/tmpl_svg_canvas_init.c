#include <libtmpl/include/types/tmpl_svg_canvas.h>
#include <libtmpl/include/tmpl_svg.h>
#include <libtmpl/include/constants/tmpl_svg_canvas_default_constants.h>
#include <libtmpl/include/compat/tmpl_cast.h>

void
tmpl_SVGCanvas_Init(tmpl_SVGCanvas *canvas,
                    unsigned int width, unsigned int height,
                    double x_min, double x_max,
                    double y_min, double y_max,
                    const tmpl_RGB24 * const background,
                    const tmpl_Pen * const outline)
{
    const double real_width = TMPL_CAST(width, double);
    const double real_height = TMPL_CAST(height, double);

    if (!canvas)
        return;

    canvas->width = width;
    canvas->height = height;

    canvas->x_scale = real_width / (x_max - x_min);
    canvas->y_scale = real_height / (y_max - y_min);

    canvas->x_shift = 0.5 * (real_width - (x_min + x_max) * canvas->x_scale);
    canvas->y_shift = 0.5 * (real_height - (y_min + y_max) * canvas->y_scale);

    canvas->background = background;
    canvas->outline = outline;
}
