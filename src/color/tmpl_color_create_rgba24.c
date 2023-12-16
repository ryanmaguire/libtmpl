#include <libtmpl/include/tmpl_color.h>

tmpl_RGBA24
tmpl_RGBA24_Create(unsigned char red,
                   unsigned char green,
                   unsigned char blue,
                   double alpha)
{
    tmpl_RGBA24 c;

    c.dat[0] = red;
    c.dat[1] = green;
    c.dat[2] = blue;
    c.alpha = alpha;

    return c;
}
