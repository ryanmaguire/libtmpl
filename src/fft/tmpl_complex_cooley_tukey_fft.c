#include <stdlib.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_fft.h>

void
tmpl_CDouble_FFT_Cooley_Tukey(tmpl_ComplexDouble *in, tmpl_ComplexDouble *out,
                              unsigned long N, tmpl_Bool inverse)
{
    /*  We'll need several variables for indexing the pointers.               */
    unsigned long k, m, n, skip;

    /*  Boolean for determining if we're on an even iteration.                */
    tmpl_Bool evenIteration = N & 0x55555555;

    /*  Declare several pointers for performing the Cooley-Tukey algorithm.   */
    tmpl_ComplexDouble *E, *D;
    tmpl_ComplexDouble *twiddles;
    tmpl_ComplexDouble *scratch;
    tmpl_ComplexDouble *Xp;
    tmpl_ComplexDouble *Xp2;
    tmpl_ComplexDouble *Xstart;

    /*  And some variables for actually computing the FFT.                    */
    tmpl_ComplexDouble t, d;
    double factor;

    /*  This method assume N is a power of two. If not, return failure.       */
    if (!((N > 0) && ((N & (N-1)) == 0)))
        return;

    /*  If N is 1, simply return the output. That is, the FFT of a point is   *
     *  just that point.                                                      */
    if (N == 1)
    {
    	out[0] = in[0];
    	return;
    }

    /*  The "twiddle" factors are just the complex exponentials that occur    *
     *  inside the discrete Fourier transform. Allocate memory for this and   *
     *  the "scratch" factor. Per C99 recommendations we do not cast malloc.  */
    twiddles = malloc(sizeof(*twiddles) * N);
    scratch  = malloc(sizeof(*scratch)  * N);

    /*  If we are performing an inverse Fourier transform, the factor inside  *
     *  the exponential is 2 pi / N. Forward transform is minus this.         */
    if (inverse)
        factor = tmpl_Two_Pi/(double)N;
    else
        factor = -tmpl_Two_Pi/(double)N;

    /*  Compute the "twiddle" factors. No idea why it's called this.          */
    for (k = 0; k<N; ++k)
        twiddles[k] = tmpl_CDouble_Polar(1.0, (double)(k) * factor);

    /*  Set "E" pointer to point to the initial address of the "in" pointer.  */
    E = in;

    /*  The actual Cooley-Tukey algorithm is recursive. We can save a lot of  *
     *  overhall, and memory usage, by unraveling this a bit into nested      *
     *  for-loops. This is also significantly faster than pure recursion.     */
    for (n = 1; n < N; n *= 2)
    {
        if (evenIteration)
            Xstart = scratch;
        else
            Xstart = out;

        skip = N/(2 * n);

        /* Each of D and E is of length n, and each element of each D and E   *
         * is separated by 2*skip. The Es begin at E[0] to E[skip - 1] and    *
         * the Ds begin at E[skip] to E[2*skip - 1]                           */
        Xp = Xstart;
        Xp2 = Xstart + N/2;
        for (k=0; k<n; ++k)
        {
        	t = twiddles[k * skip];
            for (m=0; m<skip; ++m)
            {
                /*  Set the D pointer to the desired address.                 */
            	D = E + skip;

            	/* twiddle *D to get dre and dim                              */
            	d    = tmpl_CDouble_Multiply(t, *D);
                *Xp  = tmpl_CDouble_Add(*E, d);
                *Xp2 = tmpl_CDouble_Subtract(*E, d);
                ++Xp;
                ++Xp2;
                ++E;
            }
            E += skip;
        }
        E = Xstart;

        /*  The next iteration is the opposite of what evenIteration is now.  */
        evenIteration = !evenIteration;
    }

    /*  Free your allocated memory!                                           */
    free(twiddles);
    free(scratch);

    /*  The inverse Fourier transform has a 1/N factor in front of the sum.   */
    if (inverse)
    {
        factor = 1.0/(double)N;
        for (k=0; k<N; ++k)
            out[k] = tmpl_CDouble_Multiply_Real(factor, out[k]);
    }

    return;
}
