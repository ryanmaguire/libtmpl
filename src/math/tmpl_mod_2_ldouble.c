
#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_Mod_2(long double x)
{
    if (x < 0.0L)
        return x + 2.0L * tmpl_LDouble_Floor(-0.5L * x);
    else
        return x - 2.0L * tmpl_LDouble_Floor(0.5L * x);
}
