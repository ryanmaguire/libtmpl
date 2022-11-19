#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_Mod_360(long double x)
{
    if (x < 0.0L)
        return x + 360.0L*tmpl_LDouble_Floor(-x/360.0L);
    else
        return x - 360.0L*tmpl_LDouble_Floor(x/360.0L);
}
