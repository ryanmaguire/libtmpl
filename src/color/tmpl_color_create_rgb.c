#include <libtmpl/include/tmpl_color.h>

tmpl_RGB
tmpl_RGB_Create(double red, double green, double blue)
{
    tmpl_RGB c;

    c.dat[0] = red;
    c.dat[1] = green;
    c.dat[2] = blue;

    return c;
}
