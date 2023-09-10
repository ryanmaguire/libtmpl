#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

#define A00 (+3.989422804014250978354994e-01)
#define A01 (+4.986778506049619613671453e-02)
#define A02 (+2.805062339283126079947372e-02)
#define A03 (+2.922112251660478887682615e-02)
#define A04 (+4.442072994936595298209880e-02)
#define A05 (+1.309705746058567321643551e-01)
#define A06 (-3.350522802317270176786224e+00)
#define A07 (+2.330257115835147203597444e+02)
#define A08 (-1.133663506971723472815938e+04)
#define A09 (+4.240576743178673204965889e+05)
#define A10 (-1.231570285956987366080284e+07)
#define A11 (+2.802319381552675366401672e+08)
#define A12 (-5.018839997137779235839844e+09)
#define A13 (+7.080292430151091003417969e+10)
#define A14 (-7.842610821248111572265625e+11)
#define A15 (+6.768257378540965820312500e+12)
#define A16 (-4.490348496961380468750000e+13)
#define A17 (+2.241552399669590000000000e+14)
#define A18 (-8.134264678656593750000000e+14)
#define A19 (+2.023910973916877750000000e+15)
#define A20 (-3.086757152953709000000000e+15)
#define A21 (+2.175875438638190750000000e+15)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
  A01 + z*(\
    A02 + z*(\
      A03 + z*(\
        A04 + z*(\
          A05 + z*(\
            A06 + z*(\
              A07 + z*(\
                A08 + z*(\
                  A09 + z*(\
                    A10 + z*(\
                      A11 + z*(\
                        A12 + z*(\
                          A13 + z*(\
                            A14 + z*(\
                              A15 + z*(\
                                A16 + z*(\
                                  A17 + z*(\
                                    A18 + z*(\
                                      A19 + z*(\
                                        A20 + z*A21\
                                      )\
                                    )\
                                  )\
                                )\
                              )\
                            )\
                          )\
                        )\
                      )\
                    )\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

TMPL_INLINE_DECL
double tmpl_Double_Bessel_I0_Holoborodko(double x)
{
    const double rcpr_x = 1.0 / x;
    const double exp_x = tmpl_Double_Exp_Pos_Kernel(x);
    const double inv_sqrt_x = tmpl_Double_Sqrt(rcpr_x);
    const double poly = TMPL_POLY_EVAL(rcpr_x);
    return exp_x * poly * inv_sqrt_x;
}

#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef A11
#undef A12
#undef A13
#undef A14
#undef A15
#undef A16
#undef A17
#undef A18
#undef A19
#undef A20
#undef A21
#undef TMPL_POLY_EVAL
