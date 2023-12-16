#include <libtmpl/include/tmpl_color.h>

tmpl_RGB24
tmpl_RGB24_Create(unsigned char red, unsigned char green, unsigned char blue)
{
    tmpl_RGB24 c;

    c.dat[0] = red;
    c.dat[1] = green;
    c.dat[2] = blue;

    return c;
}
