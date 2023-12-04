#include <libtmpl/include/tmpl_math.h>

/*  TODO:
 *  Implement actual algorithm.
 */

double tmpl_Double_Tan(double x)
{
    double cos_x, sin_x;
    tmpl_Double_SinCos(x, &sin_x, &cos_x);
    return sin_x / cos_x;
}
