#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *  Implement actual algorithm for 64-bit, 80-bit, and 128-bit long double.
 */

long double tmpl_LDouble_Cos(long double x)
{
    const double x_double = (double)x;
    const double cos_x_double = tmpl_Double_Cos(x_double);
    return (long double)cos_x_double;
}
