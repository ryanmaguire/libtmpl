
#include <libtmpl/include/tmpl_math.h>
#include <math.h>

long double tmpl_LDouble_Mod_2(long double x)

{
    long double abs_x, sgn_x, factor;

    if (x < 0.0L)
    {
        sgn_x = -1.0L;
        abs_x = -x;
    }
    else
    {
        sgn_x = 1.0L;
        abs_x = x;
    }

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    factor = floorl(abs_x * 0.5L);
#else
    factor = (long double)floor((double)(abs_x * 0.5L));
#endif
    abs_x -= factor * 2.0L;

    return sgn_x * abs_x;
}

