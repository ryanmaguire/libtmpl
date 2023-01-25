#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Inline this function.
 *      Add comments and doc-string.
 */

#define A1 (+1.000000000000000000E+00F)
#define A2 (-1.000000000000000000E+00F)
#define A3 (+1.500000000000000000E+00F)
#define A4 (-2.666666666666666519E+00F)

#define TMPL_POLY_EVAL(z) x*(A1 + x*(A2 + x*(A3 + x*A4)))

float tmpl_Float_LambertW_Maclaurin(float x)
{
    return TMPL_POLY_EVAL(x);
}

#undef A1
#undef A2
#undef A3
#undef A4
#undef TMPL_POLY_EVAL

