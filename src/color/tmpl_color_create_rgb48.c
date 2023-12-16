#include <libtmpl/include/tmpl_color.h>

tmpl_RGB48
tmpl_RGB48_Create(unsigned short int red,
                  unsigned short int green,
                  unsigned short int blue)
{
    tmpl_RGB48 c;

    c.dat[0] = red;
    c.dat[1] = green;
    c.dat[2] = blue;

    return c;
}
