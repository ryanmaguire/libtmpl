/*  PPM color typedef and function prototype found here.                      */
#include <libtmpl/include/tmpl_ppm.h>

#include <limits.h>

tmpl_PPM_Color
tmpl_PPM_Color_Addition(tmpl_PPM_Color C0, tmpl_PPM_Color C1)
{
    tmpl_PPM_Color out;

    if (UCHAR_MAX - C0.red > C1.red)
        out.red = C0.red + C1.red;
    else
        out.red = UCHAR_MAX;

    if (UCHAR_MAX - C0.green > C1.green)
        out.green = C0.green + C1.green;
    else
        out.green = UCHAR_MAX;

    if (UCHAR_MAX - C0.blue > C1.blue)
        out.blue = C0.blue + C1.blue;
    else
        out.blue = UCHAR_MAX;

    return out;
}
/*  End of tmpl_PPM_Color_Addition.                                           */
