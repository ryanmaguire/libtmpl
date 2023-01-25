#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Inline this function.
 *      Add comments and doc-string.
 */

#define A1 (+1.000000000000000000E+00)
#define A2 (-1.000000000000000000E+00)
#define A3 (+1.500000000000000000E+00)
#define A4 (-2.666666666666666519E+00)
#define A5 (+5.208333333333333037E+00)
#define A6 (-1.080000000000000071E+01)
#define A7 (+2.334305555555555500E+01)
#define A8 (-5.201269841269841265E+01)
#define A9 (+1.186252232142857110E+02)

#define TMPL_POLY_EVAL(z) x * (\
    A1 + x*(\
        A2 + x*(\
            A3 + x*(\
                A4 + x*(\
                    A5 + x*(\
                        A6 + x*(\
                            A7 + x*(\
                                A8 + x*A9\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

double tmpl_Double_LambertW_Maclaurin(double x)
{
    return TMPL_POLY_EVAL(x);
}

#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7
#undef A8
#undef A9
#undef TMPL_POLY_EVAL

