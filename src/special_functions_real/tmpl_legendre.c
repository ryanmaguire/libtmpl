/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_special_functions_real.h>

void tmpl_Legendre_Polynomials(double *legendre_p, double x, unsigned int order)
{
    unsigned int i;
    legendre_p[0] = 1.0;
    legendre_p[1] = x;
    for (i = 2U; i < order; ++i){
        legendre_p[i] = ((2.0*i-1.0)*x*legendre_p[i-1] -
                         (i-1.0) * legendre_p[i-2]) / i;
    }
}

void
tmpl_Alt_Legendre_Polynomials(double *poly, double *legendre_p,
                              unsigned int order)
{
    unsigned int i;
    for (i = 0U; i < order; ++i){
        poly[i] = (legendre_p[i]-legendre_p[1]*legendre_p[i+1])/(i+2.0);
    }
}

void
tmpl_Fresnel_Kernel_Coefficients(double *fresnel_ker_coeffs, double *legendre_p,
                                 double *alt_legendre_p, double Legendre_Coeff,
                                 unsigned int order)
{
    unsigned int i, j;
    unsigned int order_by_2 = (order + 1) / 2;

    for (i=1; i<=order_by_2; ++i)
    {
        fresnel_ker_coeffs[i-1] = 0.0;
        for (j=0; j<i; ++j)
            fresnel_ker_coeffs[i-1] += legendre_p[j+1]*legendre_p[i-j];

        fresnel_ker_coeffs[i-1] = alt_legendre_p[i-1] -
                                  Legendre_Coeff*fresnel_ker_coeffs[i-1];
    }

    /*  Compute along the upper triangle of the square.                   */
    for (i = order_by_2+1; i < order; ++i)
    {
        fresnel_ker_coeffs[i-1] = 0.0;
        for (j=i-order_by_2; j<order_by_2; ++j){
            fresnel_ker_coeffs[i-1] += legendre_p[j+1]*legendre_p[i-j];
        }
        fresnel_ker_coeffs[i-1] = alt_legendre_p[i-1] -
                                  Legendre_Coeff*fresnel_ker_coeffs[i-1];
    }

    /* Compute the last coefficient.                                      */
    fresnel_ker_coeffs[i-1] = legendre_p[order_by_2]*legendre_p[order_by_2];
    fresnel_ker_coeffs[i-1] = alt_legendre_p[order-1] -
                              Legendre_Coeff*fresnel_ker_coeffs[i-1];
}
