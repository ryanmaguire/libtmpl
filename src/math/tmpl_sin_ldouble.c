#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *  Implement actual algorithm for 64-bit, 80-bit, and 128-bit long double.
 */

long double tmpl_LDouble_Sin(long double x)
{
    const double x_double = (double)x;
    const double sin_x_double = tmpl_Double_Sin(x_double);
    return (long double)sin_x_double;
}
