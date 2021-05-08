
#include <libtmpl/include/tmpl_math.h>
#include <math.h>

float tmpl_Float_Mod_2(float x)

{
    float abs_x, sgn_x, factor;

    if (x < 0.0F)
    {
        sgn_x = -1.0F;
        abs_x = -x;
    }
    else
    {
        sgn_x = 1.0F;
        abs_x = x;
    }

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    factor = floorf(abs_x * 0.5F);
#else
    factor = (float)floor((double)(abs_x * 0.5F));
#endif
    abs_x -= factor * 2.0F;

    return sgn_x * abs_x;
}

