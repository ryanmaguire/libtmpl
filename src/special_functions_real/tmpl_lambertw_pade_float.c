#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Add comments and doc-string.
 *      Inline this function.
 */

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P1 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define P2 (+5.1492819469015868522245605700214485337691621631491E+00F)
#define P3 (+8.3703236433728308188112166458094526823526240246972E+00F)
#define P4 (+4.4380650195560477860676338747707776047872383835041E+00F)
#define P5 (+3.2358570732152883273070562868849767408226822688136E-01F)
#define P6 (-2.5160102861106943485069147235281059433424284718032E-02F)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q0 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define Q1 (+6.1492819469015868522245605700214485337691621631491E+00F)
#define Q2 (+1.3019605590274417671035777215830901216121786187846E+01F)
#define Q3 (+1.0900414356144751845433236902236172686921947993293E+01F)
#define Q4 (+2.8843435364588857775424382272355146268726360401363E+00F)

/*  Helper macros for evaluating the polynomials via Horner's method.         */
#define TMPL_NUM_EVAL(z) z*(P1 + z*(P2 + z*(P3 + z*(P4 + z*(P5 + z*P6)))))
#define TMPL_DEN_EVAL(z) Q0 + z*(Q1 + z*(Q2 + z*(Q3 + z*Q4)))

/*  Function for computing the Lambert W function via a Pade approximant.     */
float tmpl_Float_LambertW_Pade(float x)
{
    /*  Use the helper functions to evaluate the numerator and denominator.   */
    const float p = TMPL_NUM_EVAL(x);
    const float q = TMPL_DEN_EVAL(x);
    return p/q;
}
/*  End of tmpl_Float_LambertW_Pade.                                          */

/*  Undefine everything in case someone wants to #include this file.          */
#undef P1
#undef P2
#undef P3
#undef P4
#undef P5
#undef P6
#undef Q0
#undef Q1
#undef Q2
#undef Q3
#undef Q4
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL
