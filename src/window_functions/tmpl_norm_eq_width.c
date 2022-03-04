/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_window_functions.h>

float tmpl_Normeq_Float(float *w_func, long N_elements)
{
    float out;
    float tot_sq = 0.0F;
    float sq_tot = 0.0F;
    long n;

    /* Compute both the sum and the sum of the squares.                       */
    for (n = 0; n < N_elements; n++)
    {
        tot_sq += w_func[n];
        sq_tot += w_func[n]*w_func[n];
    }

    /*  Square the sum.                                                       */
    tot_sq *= tot_sq;

    /*  Compute the normalized equivalent width and return.                   */
    out =  (float)N_elements * sq_tot / tot_sq;
    return out;
}
