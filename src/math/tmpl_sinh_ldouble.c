#include <libtmpl/include/tmpl_math.h>

long double tmpl_LDouble_Sinh(long double x)
{
    /*  The definition of sinh(x) is [exp(x) - exp(-x)]/2, so return this. It *
     *  is computationally faster to compute exp(x) and then exp(-x) via the  *
     *  formula exp(-x) = 1/exp(x). This saves us from computing two          *
     *  exponentials at the cost of an extra division.                        */
    const long double exp_x = tmpl_LDouble_Exp(x);
    const long double exp_minus_x = 1.0L / exp_x;

    /*  Compute sinh from the two exponentials and return.                    */
    return 0.5L*(exp_x - exp_minus_x);
}
