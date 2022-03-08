#include <libtmpl/include/tmpl_ppm.h>

tmpl_PPM_Color
tmpl_PPM_Create_Color(unsigned char r, unsigned char g, unsigned char b)
{
    tmpl_PPM_Color out;
    out.red = r;
    out.green = g;
    out.blue = b;
    return out;
}
/*  End of tmpl_PPM_Create_Color.                                             */
