#ifndef TMPL_BESSEL_J0_RATIONAL_ASYMPTOTIC_DOUBLE_H
#define TMPL_BESSEL_J0_RATIONAL_ASYMPTOTIC_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define PA0 (+9.9993144187804128825450648496298618347721049576026E-01)
#define PA1 (+1.1837723706679330420432693013503515999567231849302E-01)
#define PA2 (+1.5492984928075949111746525243664172554489838400038E-02)
#define PA3 (+5.1250961298196858455794807766211701507776806368359E-04)
#define PA4 (+1.4059226306527380925924233220666136663066277104562E-05)
#define PA5 (-2.2230205391109275785982338865737000460182217803329E-08)

#define TMPL_POLYPA_EVAL(z) PA0 + z*(PA1 + z*(PA2 + z*(PA3 + z*(PA4 + z*PA5))))

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define PB0 (+1.0000000000000000000000000000000000000000000000000E+00)
#define PB1 (+1.1852226716194827598005030927049363352829092992204E-01)
#define PB2 (+1.5578309829922621488177562781490297547403164947630E-02)
#define PB3 (+5.2232384924805994662829700291291929382291656522061E-04)
#define PB4 (+1.5042764127572313568627083049722883578986306608824E-05)

#define TMPL_POLYPB_EVAL(z) PB0 + z*(PB1 + z*(PB2 + z*(PB3 + z*PB4)))

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define QA0 (-3.9040215445613895349655651318185406081680144570912E-03)
#define QA1 (-4.1018706858060595604029110278659745425640029468230E-03)
#define QA2 (-2.4826131257143120712344542780937877466394152652983E-04)
#define QA3 (-5.0839180716529344749465166056491974743271020721853E-05)
#define QA4 (-4.7231404741002575444248464526504316674970464320366E-07)
#define QA5 (-4.5304657606460114620055758915430807114569891056011E-08)

#define TMPL_POLYQA_EVAL(z) QA0 + z*(QA1 + z*(QA2 + z*(QA3 + z*(QA4 + z*QA5))))

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define QB0 (+1.0000000000000000000000000000000000000000000000000E+00)
#define QB1 (+5.1816494918126075830857006860784898299782728333972E-02)
#define QB2 (+1.3534177673515040574254456396167577257219987625209E-02)
#define QB3 (+1.4723213402022308372445399604909203786388855416363E-04)
#define QB4 (+1.7484076814147054839726350609422365786104465155894E-05)

#define TMPL_POLYQB_EVAL(z) QB0 + z*(QB1 + z*(QB2 + z*(QB3 + z*QB4)))

#define TMPL_SQRT_ONE_BY_PI (+5.6418958354775628694807945156077258584405062E-01)

extern double tmpl_Double_Sqrt(double x);
extern void tmpl_Double_SinCos(double x, double *sin_x, double *cos_x);

TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J0_Rational_Asymptotic(double x)
{
    double sin_x, cos_x;
    const double rcpr_x = 1.0 / x;
    const double arg = 32.0 * rcpr_x - 1.0;

    const double pzero_num = TMPL_POLYPA_EVAL(arg);
    const double pzero_den = TMPL_POLYPB_EVAL(arg);

    const double qzero_num = TMPL_POLYQA_EVAL(arg);
    const double qzero_den = TMPL_POLYQB_EVAL(arg);

    const double pzero = pzero_num / pzero_den;
    const double qzero = qzero_num / qzero_den;

    const double scale = TMPL_SQRT_ONE_BY_PI * tmpl_Double_Sqrt(rcpr_x);

    tmpl_Double_SinCos(x, &sin_x, &cos_x);

    return scale * (pzero*(sin_x + cos_x) - qzero*(sin_x - cos_x));
}

#endif
