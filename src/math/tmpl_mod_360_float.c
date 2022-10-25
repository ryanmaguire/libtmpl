#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Mod_360(float x)
{
    if (x < 0.0F)
        return x + 360.0F*tmpl_Float_Floor(-x/360.0F);
    else
        return x - 360.0F*tmpl_Float_Floor(x/360.0F);
}
