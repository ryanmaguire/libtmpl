#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Add comments and doc-string.
 *      Inline this function.
 */

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P01 (+1.0000000000000000000000000000000000000000000000000E+00)
#define P02 (+1.0682502565416050016723105546359160380709861862124E+01)
#define P03 (+4.6571964665591139713188203885880491905853395796878E+01)
#define P04 (+1.0645221196874087589402765839192190487117781040351E+02)
#define P05 (+1.3621315458647873063125988415924999885445238071605E+02)
#define P06 (+9.6194426795076224947202936312211557831255938423266E+01)
#define P07 (+3.4212690660831692810057957056825594180703795525921E+01)
#define P08 (+4.7902915867548580879769213470489619147298431970733E+00)
#define P09 (+8.7004781328169727922261553430157539405962610146625E-02)
#define P10 (-2.3526462504008900307253829870553999017908603231409E-03)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q01 (+1.1682502565416050016723105546359160380709861862124E+01)
#define Q02 (+5.6754467231007189729911309432239652286563257659002E+01)
#define Q03 (+1.4834959201829065726552097617128948325334294193599E+02)
#define Q04 (+2.2537605259936807001317551097247109802651006779587E+02)
#define Q05 (+2.0034496978815222117142763345976687675905641654059E+02)
#define Q06 (+9.9324282254815566451544174900199633472503607783434E+01)
#define Q07 (+2.4201439090875344909012382876194017492323387287572E+01)
#define Q08 (+2.0878375944665185359069024322498319401797520687138E+00)

/*  Helper macros for evaluating the polynomials via Horner's method.         */
#define TMPL_NUM_EVAL(z) \
z*(\
  P01 + z*(\
    P02 + z*(\
      P03 + z*(\
        P04 + z*(\
          P05 + z*(\
            P06 + z*(\
              P07 + z*(\
                P08 + z*(\
                  P09 + z*P10\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

#define TMPL_DEN_EVAL(z) \
Q00 + z*(\
  Q01 + z*(\
    Q02 + z*(\
      Q03 + z*(\
        Q04 + z*(\
          Q05 + z*(\
            Q06 + z*(\
              Q07 + z*Q08\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Function for computing the Lambert W function via a Pade approximant.     */
double tmpl_Double_LambertW_Pade(double x)
{
    /*  Use the helper functions to evaluate the numerator and denominator.   */
    const double p = TMPL_NUM_EVAL(x);
    const double q = TMPL_DEN_EVAL(x);
    return p/q;
}
/*  End of tmpl_Double_LambertW_Pade.                                         */

/*  Undefine everything in case someone wants to #include this file.          */
#undef P00
#undef P01
#undef P02
#undef P03
#undef P04
#undef P05
#undef P06
#undef P07
#undef P08
#undef P09
#undef P10
#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04
#undef Q05
#undef Q06
#undef Q07
#undef Q08
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL
