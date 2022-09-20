#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE != 1

#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the computation of the polynomial approximation. The     *
 *  coefficients for the Taylor series are 1 / (1 + 2n).                      */
#define A0 (1.0)
#define A1 (-3.33333333333329318027E-01)
#define A2 (1.99999999998764832476E-01)
#define A3 (-1.42857142725034663711E-01)
#define A4 (1.11111104054623557880E-01)
#define A5 (-9.09088713343650656196E-02)

double tmpl_Double_Arctan_Very_Small(double x)
{
      const double x2 = x*x;
      return x*(A0 + x2*(A1 + x2*(A2 + x2*(A3 + x2*(A4 + x2*A5)))));
}

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#endif
