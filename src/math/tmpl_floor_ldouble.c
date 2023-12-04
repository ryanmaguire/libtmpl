#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *  Implement actual algorithm for 64-bit, 80-bit, and 128-bit long double.
 */

long double tmpl_LDouble_Floor(long double x)
{
    const double x_double = (double)x;
    const double floor_x_double = tmpl_Double_Floor(x_double);
    return (long double)floor_x_double;
}
