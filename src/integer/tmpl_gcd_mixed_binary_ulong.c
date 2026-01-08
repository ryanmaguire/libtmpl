/*  Function prototype and TMPL_ULONG_TRAILING_ZEROS found here.              */
#include <libtmpl/include/tmpl_integer.h>

/*  TMPL_MIN macro is provided here.                                          */
#include <libtmpl/include/helper/tmpl_min.h>
#include <libtmpl/include/helper/tmpl_swap.h>

/*  Function for computing the GCD of two unsigned integers.                  */
unsigned long int
tmpl_ULong_GCD_Mixed_Binary(const unsigned long int m,
                            const unsigned long int n)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    unsigned long int u, v;
    int m_zeros, n_zeros, shift;

    /*  Special cases. GCD(m, 0) = m and GCD(0, n) = n. Use this.             */
    if (m == 0UL)
        return n;

    if (n == 0UL)
        return m;

    /*  Use the fact that GCD(2m, 2n) = 2 GCD(m, n) to reduce the arguments.  */
    m_zeros = TMPL_ULONG_TRAILING_ZEROS(m);
    n_zeros = TMPL_ULONG_TRAILING_ZEROS(n);
    u = m >> m_zeros;
    v = n >> n_zeros;

    /*  Swap u and v, if necessary, so that u is the larger one.              */
    if (u < v)
        TMPL_SWAP(unsigned long int, u, v);

    /*  Save the smaller of n_zeros and m_zeros for later. Before returning   *
     *  the output we need to bit shift to the left by this value.            */
    shift = TMPL_MIN(m_zeros, n_zeros);

    /*  Apply the Euclidean and Binary reductions repeatedly, decreasing u    *
     *  and v at each step, until one of the values is zero or one.           */
    while (1UL < v)
    {
        /*  Apply the Euclidean reduction.                                    */
        u %= v;
        v -= u;

        /*  If u is zero, we are done. Note that v can't be zero since        *
         *  u mod v is less than v, hence v - u is positive.                  */
        if (u == 0UL)
            return v << shift;

        /*  Apply the binary (i.e. Stein GCD) reduction step.                 */
        u >>= TMPL_ULONG_TRAILING_ZEROS(u);
        v >>= TMPL_ULONG_TRAILING_ZEROS(v);

        /*  Swap u and v, if necessary, so that m is larger.                  */
        if (u < v)
            TMPL_SWAP(unsigned long int, u, v);
    }

    if (v == 1U)
        return 1UL << shift;

    return u << shift;
}
/*  End of tmpl_ULong_GCD_Mixed_Binary.                                       */
