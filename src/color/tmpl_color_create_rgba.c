#include <libtmpl/include/tmpl_color.h>

tmpl_RGBA
tmpl_RGBA_Create(double red, double green, double blue, double alpha)
{
    tmpl_RGBA c;

    c.dat[0] = red;
    c.dat[1] = green;
    c.dat[2] = blue;
    c.dat[3] = alpha;

    return c;
}
