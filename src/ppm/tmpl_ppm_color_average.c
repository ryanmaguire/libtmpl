/*  PPM color typedef and function prototype found here.                      */
#include <libtmpl/include/tmpl_ppm.h>

tmpl_PPM_Color
tmpl_PPM_Color_Average(tmpl_PPM_Color C0, tmpl_PPM_Color C1)
{
    tmpl_PPM_Color out;
    double r, g, b;

    r = 0.5*((double)C0.red + (double)C1.red);
    g = 0.5*((double)C0.green + (double)C1.green);
    b = 0.5*((double)C0.blue + (double)C1.blue);
    out.red = (unsigned char)r;
    out.green = (unsigned char)g;
    out.blue = (unsigned char)b;
    return out;
}
/*  End of tmpl_PPM_Color_Average.                                            */
