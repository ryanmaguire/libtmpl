#ifndef TMPL_SQRT_RAT_REMEZ_LDOUBLE_H
#define TMPL_SQRT_RAT_REMEZ_LDOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+4.9999999972171187639063408002181263732434664512996E-01L)
#define A01 (+5.4973680754825196818973580194887344734892824904921E-01L)
#define A02 (+1.3550478175653948536511272946068367018506089772074E-01L)
#define A03 (+4.0987428303580793473001869062958752663846083667486E-03L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+1.3494735373780380492561725021879188082944219757384E+00L)
#define B02 (+4.8337968576596670256696069488932727631806689766007E-01L)
#define B03 (+3.8468334373058034235686700239840171483686350394335E-02L)

#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*A03))
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*B03))

TMPL_STATIC_INLINE
long double tmpl_LDouble_Sqrt_Rat_Remez(long double x)
{
    const long double xs = x - 1.0L;
    const long double num = TMPL_NUM_EVAL(xs);
    const long double den = TMPL_DEN_EVAL(xs);
    return 1.0L + xs * num / den;
}

#include "tmpl_math_undef.h"

#endif
