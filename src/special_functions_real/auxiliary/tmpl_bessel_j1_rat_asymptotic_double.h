#ifndef TMPL_BESSEL_J1_RATIONAL_ASYMPTOTIC_DOUBLE_H
#define TMPL_BESSEL_J1_RATIONAL_ASYMPTOTIC_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.0000903369118070925682540408661107782291898172763E+00)
#define A01 (+9.6810871468625799621712802481413946637566376853067E-02)
#define A02 (+1.1223973811607436928891209924348791615110615790198E-02)
#define A03 (+3.1907162895550348394795719354415913229407437934781E-04)
#define A04 (+7.5234969464253410162028124399865536954514337052821E-06)
#define A05 (+1.9068969407873243031790523970784688558298595246312E-08)

#define TMPL_POLYA_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+9.6621639616189968904884522241501427459306904480463E-02)
#define B02 (+1.1115617183963265332541727739020962005525925317070E-02)
#define B03 (+3.0868721477803514914254121468839063525093853610034E-04)
#define B04 (+6.5817008149941737155917998212103241457811040411659E-06)

#define TMPL_POLYB_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define C00 (+1.0414473464126115195558058661473666680010975676973E-02)
#define C01 (+1.0802097861029771195730923322477548987553073581634E-02)
#define C02 (+4.9448250157968884666078040058839965176142987014876E-04)
#define C03 (+1.0753561130082597736142169096940977360385587556523E-04)
#define C04 (+7.6326366758135956064046868923840312388305557606204E-07)
#define C05 (+8.5757042774561847364687084900753074402343508624473E-08)

#define TMPL_POLYC_EVAL(z) C00 + z*(C01 + z*(C02 + z*(C03 + z*(C04 + z*C05))))

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define D01 (+3.7640090236365078347815097503234395261646653345706E-02)
#define D02 (+1.0484780294533464236657897835836154901871234985427E-02)
#define D03 (+7.5590503648458262101957380729972554388147997760836E-05)
#define D04 (+9.9809879877385570938058520785315247723118951329465E-06)

#define TMPL_POLYD_EVAL(z) D00 + z*(D01 + z*(D02 + z*(D03 + z*D04)))

extern const double tmpl_Double_Rcpr_Sqrt_Pi;
extern double tmpl_Double_Sqrt(double x);
extern void tmpl_Double_SinCos(double x, double *sin_x, double *cos_x);

TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J1_Rational_Asymptotic(double x)
{
    double sin_x, cos_x;
    const double rcpr_x = 1.0 / x;
    const double arg = 36.0 * rcpr_x - 1.0;

    const double pone_num = TMPL_POLYA_EVAL(arg);
    const double pone_den = TMPL_POLYB_EVAL(arg);

    const double qone_num = TMPL_POLYC_EVAL(arg);
    const double qone_den = TMPL_POLYD_EVAL(arg);

    const double pone = pone_num / pone_den;
    const double qone = qone_num / qone_den;

    const double scale = tmpl_Double_Rcpr_Sqrt_Pi * tmpl_Double_Sqrt(rcpr_x);

    tmpl_Double_SinCos(x, &sin_x, &cos_x);

    return scale * (pone*(sin_x - cos_x) + qone*(sin_x + cos_x));
}

#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
