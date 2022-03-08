#include <libtmpl/include/tmpl_math.h>

/*  PPM color typedef and function prototype found here.                      */
#include <libtmpl/include/tmpl_ppm.h>

tmpl_PPM_Color
tmpl_PPM_Color_Blend(tmpl_PPM_Color C0, tmpl_PPM_Color C1, double t)
{
    tmpl_PPM_Color out;
    const double s = (t > 1.0 ? 1.0 : (t < 0.0 ? 0.0 : t));
    const double r0 = (1.0 - s)*(double)C0.red;
    const double r1 = s*(double)C1.red;
    const double g0 = (1.0 - s)*(double)C0.green;
    const double g1 = s*(double)C1.green;
    const double b0 = (1.0 - s)*(double)C0.blue;
    const double b1 = s*(double)C1.blue;
    const double r = tmpl_Double_Sqrt(r0*r0 + r1*r1);
    const double g = tmpl_Double_Sqrt(g0*g0 + g1*g1);
    const double b = tmpl_Double_Sqrt(b0*b0 + b1*b1);
    out.red = (unsigned char)r;
    out.green = (unsigned char)g;
    out.blue = (unsigned char)b;
    return out;
}
/*  End of tmpl_PPM_Color_Blend.                                              */
