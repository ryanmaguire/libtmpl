#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_fft.h>
#include <stdlib.h>

tmpl_ComplexDouble *
tmpl_CDouble_FFT(tmpl_ComplexDouble *in, unsigned long N, tmpl_Bool inverse)
{
    tmpl_ComplexDouble *out;
    out = malloc(sizeof(*out) * N);
    if ((N > 0) && ((N & (N-1)) == 0))
        tmpl_CDouble_FFT_Cooley_Tukey(in, out, N, inverse);
    else
        tmpl_CDouble_FFT_Bluestein_Chirp_Z(in, out, N, inverse);

    return out;
}
