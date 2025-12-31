/*  Function prototype is found here.                                         */
#include <libtmpl/include/tmpl_integer.h>

/*  TMPL_MIN macro is provided here.                                          */
#include <libtmpl/include/helper/tmpl_min.h>

#include <libtmpl/include/helper/tmpl_swap.h>


/*  Function for computing the GCD of two unsigned integers.                  */
unsigned int tmpl_UInt_GCD_Mixed_Binary(unsigned int m, unsigned int n)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    int m_zeros, n_zeros, shift;

    /*  Special cases. GCD(m, 0) = m and GCD(0, n) = n. Use this.             */
    if (m == 0U)
        return n;

    if (n == 0U)
        return m;

    /*  Swap m and n, if necessary, so that m is the larger one.              */
    if (m < n)
        TMPL_SWAP(unsigned int, m, n);

    /*  Use the fact that GCD(2m, 2n) = 2 GCD(m, n) to reduce the arguments.  */
    m_zeros = TMPL_UINT_TRAILING_ZEROS(m);
    n_zeros = TMPL_UINT_TRAILING_ZEROS(n);
    m = m >> m_zeros;
    n = n >> n_zeros;

    /*  Save the smaller of n_zeros and m_zeros for later. Before returning   *
     *  the output we need to bit shift to the left by this value.            */
    shift = TMPL_MIN(m_zeros, n_zeros);

    /*  Apply the Euclidean and Binary reductions repeatedly, decreasing m    *
     *  and n at each step, until one of the values is zero or one.           */
    while (1U < n)
    {
        /*  Apply the Euclidean reduction.                                    */
        m %= n;
        n -= m;

        /*  If m is zero, we are done. Note that n can't be zero since        *
         *  m mod n is less than n, hence n - m is positive.                  */
        if (m == 0U)
            return n << shift;

        /*  Apply the binary (i.e. Stein GCD) reduction step.                 */
        m = m >> TMPL_UINT_TRAILING_ZEROS(m);
        n = n >> TMPL_UINT_TRAILING_ZEROS(n);

        /*  Swap m and n, if necessary, so that m is larger.                  */
        if (m < n)
            TMPL_SWAP(unsigned int, m, n);
    }

    if (n == 1U)
        return 1U << shift;

    return m << shift;
}
/*  End of tmpl_UInt_GCD.                                                     */
