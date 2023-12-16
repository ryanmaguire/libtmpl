#include <libtmpl/include/tmpl_color.h>

tmpl_RGBA30
tmpl_RGBA30_Create(unsigned short int red,
                   unsigned short int green,
                   unsigned short int blue,
                   double alpha)
{
    tmpl_RGBA30 c;

    c.red = (red > 0x3FFU ? 0x3FFU : red & 0x3FFU);
    c.green = (green > 0x3FFU ? 0x3FFU : green & 0x3FFU);
    c.blue = (blue > 0x3FFU ? 0x3FFU : blue & 0x3FFU);
    c.alpha = alpha;

    return c;
}
