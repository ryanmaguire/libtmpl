
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_ppm.h>

tmpl_PPM_Color tmpl_PPM_Linear_Color_Wheel(double val, double min, double max)
{
    double scaled, temp;
    tmpl_PPM_Color out;

    if (tmpl_Double_Is_NaN(val) ||
        tmpl_Double_Is_NaN(min) ||
        tmpl_Double_Is_NaN(max))
        return tmpl_PPM_Black;

    if (max < min)
    {
        temp = max;
        max = min;
        min = temp;
    }

    if (val <= min)
        return tmpl_PPM_Blue;
    else if (val >= max)
        return tmpl_PPM_Red;

    scaled = 255.0*(val - min)/(max-min);

    if (scaled < 64.0)
    {
        out.red = 0x00U;
        out.green = (unsigned char)(4.0*scaled);
        out.blue = 0xFFU;
    }
    else if (scaled < 128.0)
    {
        out.red = 0x00U;
        out.green = 0xFFU;
        out.blue = (unsigned char)(255 - 4*(scaled - 64));
    }
    else if (scaled < 192.0)
    {
        out.red = (unsigned char)(4.0*(scaled-128.0));
        out.green = 0xFFU;
        out.blue = 0x00U;
    }
    else if (scaled < 255.0)
    {
        out.red = 0xFFU;
        out.green = (unsigned char)(255 - 4*(scaled-192));
        out.blue = 0x00U;
    }
    else
    {
        out.red = 0xFFU;
        out.green = 0x00U;
        out.blue = 0x00U;
    }

    return out;
}
