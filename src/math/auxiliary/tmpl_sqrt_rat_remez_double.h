#ifndef TMPL_SQRT_RAT_REMEZ_DOUBLE_H
#define TMPL_SQRT_RAT_REMEZ_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+4.9999999135932342965008719639229401192423314723211E-01)
#define A01 (+4.0047259742433107254992740156123933557947772960884E-01)
#define A02 (+4.2935693755004066160135867810482987316775873928292E-02)
#define A03 (-1.2469189116106209582848200509612878094785273388241E-03)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+1.0509434502787837280709762967975270156636490918206E+00)
#define B02 (+2.2363533959632528049519179229108484874160340880609E-01)

#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*A03))
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*B02)

TMPL_STATIC_INLINE
double tmpl_Double_Sqrt_Rat_Remez(double x)
{
    const double xs = x - 1.0;
    const double num = TMPL_NUM_EVAL(xs);
    const double den = TMPL_DEN_EVAL(xs);
    return 1.0 + xs * num / den;
}

#include "tmpl_math_undef.h"

#endif
