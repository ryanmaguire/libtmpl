#include <libtmpl/include/tmpl_color.h>

tmpl_RGBA48
tmpl_RGBA48_Create(unsigned short int red,
                   unsigned short int green,
                   unsigned short int blue,
                   double alpha)
{
    tmpl_RGBA48 c;

    c.dat[0] = red;
    c.dat[1] = green;
    c.dat[2] = blue;
    c.alpha = alpha;

    return c;
}
