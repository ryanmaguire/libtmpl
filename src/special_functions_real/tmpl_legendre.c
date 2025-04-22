/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_special_functions_real.h>

void
tmpl_Double_Fresnel_Legendre(double * TMPL_RESTRICT const fresnel_ker_coeffs,
                             const double * TMPL_RESTRICT const legendre,
                             const double * TMPL_RESTRICT const mod_legendre,
                             double beta, size_t order)
{
    size_t i, j;
    size_t order_by_2 = (order + 1) >> 1;

    for (i = 1; i <= order_by_2; ++i)
    {
        fresnel_ker_coeffs[i-1] = 0.0;
        for (j = 0; j < i; ++j)
            fresnel_ker_coeffs[i-1] += legendre[j+1]*legendre[i-j];

        fresnel_ker_coeffs[i-1] = mod_legendre[i-1] -
                                  beta*fresnel_ker_coeffs[i-1];
    }

    /*  Compute along the upper triangle of the square.                   */
    for (i = order_by_2+1; i < order; ++i)
    {
        fresnel_ker_coeffs[i-1] = 0.0;

        for (j=i-order_by_2; j<order_by_2; ++j)
            fresnel_ker_coeffs[i-1] += legendre[j+1]*legendre[i-j];

        fresnel_ker_coeffs[i-1] = mod_legendre[i-1] -
                                  beta*fresnel_ker_coeffs[i-1];
    }

    /* Compute the last coefficient.                                      */
    fresnel_ker_coeffs[i-1] = legendre[order_by_2]*legendre[order_by_2];
    fresnel_ker_coeffs[i-1] = mod_legendre[order-1] -
                              beta*fresnel_ker_coeffs[i-1];
}
