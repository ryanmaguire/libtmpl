/*  Include guard to prevent including this file twice.                       */
#ifndef _RSS_RINGOCCS_FFT_H_
#define _RSS_RINGOCCS_FFT_H_

/*  Booleans defined here. Needed for the FFT routines.                       */
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_complex.h>

extern rssringoccs_ComplexDouble *
rssringoccs_Complex_FFT_Cooley_Tukey(rssringoccs_ComplexDouble *in,
                                     unsigned long N, tmpl_Bool inverse);

extern rssringoccs_ComplexDouble *
rssringoccs_Complex_FFT_Bluestein_Chirp_Z(rssringoccs_ComplexDouble *in,
                                          unsigned long N,
                                          tmpl_Bool inverse);

extern rssringoccs_ComplexDouble *
tmpl_Complex_FFT(rssringoccs_ComplexDouble *in,
                        unsigned long N, tmpl_Bool inverse);

#endif
