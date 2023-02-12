#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_fft.h>
#include <stddef.h>

void
tmpl_CDouble_FFT(tmpl_ComplexDouble *in, tmpl_ComplexDouble *out, size_t N)
{
    if ((N > 0) && ((N & (N-1)) == 0))
        tmpl_CDouble_FFT_Cooley_Tukey(in, out, N);
    else
        tmpl_CDouble_FFT_Bluestein_Chirp_Z(in, out, N);
}
