#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *  Implement actual algorithm.
 */

long double tmpl_LDouble_Tan(long double x)
{
    long double cos_x, sin_x;
    tmpl_LDouble_SinCos(x, &sin_x, &cos_x);
    return sin_x / cos_x;
}
