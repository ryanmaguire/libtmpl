
#include <libtmpl/include/tmpl_math.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

TMPL_CONST_FUNC
long double tmpl_LDouble_Mod_2(const long double x) TMPL_UNSEQUENCED
{
    return x - 2.0L * tmpl_LDouble_Truncate(0.5L * x);
}
