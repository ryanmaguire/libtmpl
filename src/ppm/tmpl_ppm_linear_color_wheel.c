#include <libtmpl/include/helper/tmpl_swap.h>
#include <libtmpl/include/constants/tmpl_rgb24_constants.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_ppm.h>

tmpl_PPM_Color tmpl_PPM_Linear_Color_Wheel(double val, double min, double max)
{
    double scaled;
    tmpl_RGB24 out;

    if (tmpl_Double_Is_NaN(val) ||
        tmpl_Double_Is_NaN(min) ||
        tmpl_Double_Is_NaN(max))
        return tmpl_RGB24_Black;

    if (max < min)
        TMPL_SWAP(double, min, max);

    if (val <= min)
        return tmpl_RGB24_Blue;

    if (val >= max)
        return tmpl_RGB24_Red;

    scaled = 255.0 * (val - min) / (max - min);

    if (scaled < 64.0)
    {
        out.dat[0] = 0x00U;
        out.dat[1] = (unsigned char)(4.0 * scaled);
        out.dat[2] = 0xFFU;
    }
    else if (scaled < 128.0)
    {
        out.dat[0] = 0x00U;
        out.dat[1] = 0xFFU;
        out.dat[2] = (unsigned char)(255 - 4 * (scaled - 64));
    }
    else if (scaled < 192.0)
    {
        out.dat[0] = (unsigned char)(4.0 * (scaled - 128.0));
        out.dat[1] = 0xFFU;
        out.dat[2] = 0x00U;
    }
    else if (scaled < 255.0)
    {
        out.dat[0] = 0xFFU;
        out.dat[1] = (unsigned char)(255 - 4 * (scaled - 192));
        out.dat[2] = 0x00U;
    }
    else
    {
        out.dat[0] = 0xFFU;
        out.dat[1] = 0x00U;
        out.dat[2] = 0x00U;
    }

    return out;
}
