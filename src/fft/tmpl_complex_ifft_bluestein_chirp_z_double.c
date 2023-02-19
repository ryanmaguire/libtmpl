#include <stdlib.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_fft.h>

void
tmpl_CDouble_IFFT_Bluestein_Chirp_Z(tmpl_ComplexDouble *in,
                                    tmpl_ComplexDouble *out,
                                    size_t N)
{
    /*  The chirp factors range from -(N-1) to N-1, inclusive.                */
    unsigned long chirp_size;

    /*  We're going to use the radix-2 FFT to compute the FFT of an arbitrary *
     *  array. We'll need the next highest power of 2 greater than N. Use     *
     *  bitwise operations to do this.                                        */
    unsigned long N_pow_2;

    /*  Variables for indexing.                                               */
    unsigned long n, m;

    /*  We'll need some variables declared. These will be our arrays.         */
    tmpl_ComplexDouble *chirp;
    tmpl_ComplexDouble *rcpr_chirp;
    tmpl_ComplexDouble *x_in;
    tmpl_ComplexDouble *temp;

    /*  And scale factors for the exponential.                                */
    const double chirp_factor = 1.0 / (double)N;
    double m2_chirp_factor;

    chirp_size = N+N-1;

    /*  Now, to get the highest power of two greater than N, think of how you *
     *  would do it for the highest power of 10. You would simply count off   *
     *  the number of digits. For example, if N = 1436, then there are four   *
     *  digits and the next highest power of 10 larger than N is 10^4 = 10000.*
     *  Do the same thing, but in binary! We do this as follows:              */

    /*  First, set N_pow_2 to zero so it has been given a starting value.     */
    N_pow_2 = 1;

    /*  Now we count the number of digits in the binary representation of N.  */
    while(N_pow_2 < chirp_size)
        N_pow_2 = N_pow_2 << 1;
    /*  TODO: Create a better way of getting next power of two up.            */

    /*  Allocate memory for x_in and chirp, which will be a power of two in   *
     *  size. Per C90 guidelines, we do not cast malloc since void pointers   *
     *  safely promoted without the need for type casting.                    */
    chirp      = malloc(sizeof(*chirp)      * chirp_size);
    rcpr_chirp = malloc(sizeof(*rcpr_chirp) * N_pow_2);
    x_in       = malloc(sizeof(*x_in)       * N_pow_2);
    temp       = malloc(sizeof(*temp)       * N_pow_2);

    /*  Set the values for the "chirp" factor, which is simply the complex    *
     *  exponential of (k^2 / 2) * (+/- 2 pi i / N). The +/- depends on       *
     *  whether or not an inverse computation is being performed.             */
    for (n=0; n<chirp_size; ++n)
    {
        m = n+1-N;
        m2_chirp_factor = (double)(m*m)*chirp_factor;
        chirp[n] = tmpl_CDouble_ExpiPi(m2_chirp_factor);
        rcpr_chirp[n] = tmpl_CDouble_Conjugate(chirp[n]);
    }

    /*  Now pad the rest of chirp with zeros so that it is a power of two.    */
    for (n=chirp_size; n<N_pow_2; ++n)
        rcpr_chirp[n] = tmpl_CDouble_Zero;

    /*  Set the x_in array to in times chirp, and then pad with zero.         */
    for (n=0; n<N; ++n)
        x_in[n] = tmpl_CDouble_Multiply(chirp[n+N-1], in[n]);

    /*  Now pad the rest with zeros.                                          */
    for (n=N; n<N_pow_2; ++n)
        x_in[n] = tmpl_CDouble_Zero;

    /*  Lastly, we need to compute the forward FFTs of x_in and chirp, and    *
     *  then compute the inverse fourier transform of the product. We'll need *
     *  to allocate memory for these two.                                     */
    tmpl_CDouble_FFT_Cooley_Tukey(x_in, x_in, N_pow_2);
    tmpl_CDouble_FFT_Cooley_Tukey(rcpr_chirp, temp, N_pow_2);

    for (n=0; n<N_pow_2; ++n)
        x_in[n] = tmpl_CDouble_Multiply(x_in[n], temp[n]);

    tmpl_CDouble_IFFT_Cooley_Tukey(x_in, temp, N_pow_2);

    for(n=0; n<N; ++n)
    {
        m = n + N - 1;
        out[n] = tmpl_CDouble_Multiply(temp[m], chirp[m]);
    }

    for (n=0; n<N; ++n)
        out[n] = tmpl_CDouble_Multiply_Real(chirp_factor, out[n]);

    /*  Don't forget to free everything!!!                                    */
    free(x_in);
    free(chirp);
    free(rcpr_chirp);
    free(temp);
}
