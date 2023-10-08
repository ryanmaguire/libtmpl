#ifndef TMPL_LAMBERTW_NEGATIVE_LARGE_DOUBLE_H
#define TMPL_LAMBERTW_NEGATIVE_LARGE_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  TODO:
 *      Add float and long double versions.
 *      Rewrite this using coefficients that are more easily reproducible.
 *      Add programs to the data/ directory to compute these coefficients.
 *      Add license and doc-string.
 *      Add comments and explain everything.
 *      Inline this function, or split it into several inlined functions that
 *      are smaller.
 */

/*  TODO:
 *      Rewrite this.
 *      The expansions used are slight modifications of the rational
 *      approximations found in the boost library. I'd rather implement
 *      something more concrete with a simpler way of reproducing the
 *      approximation. Shifted Pade approximants or rational
 *      Remez approximations.
 */

#define P00 (-5.00173570682372162E-02)
#define P01 (-4.44242461870072044E+01)
#define P02 (-9.51185533619946042E+03)
#define P03 (-5.88605699015429386E+05)
#define P04 (-1.90760843597427751E+06)
#define P05 (+5.79797663818311404E+08)
#define P06 (+1.11383352508459134E+10)
#define P07 (+5.67791253678716467E+10)
#define P08 (+6.32694500716584572E+10)

#define Q00 (+1.00000000000000000E+00)
#define Q01 (+9.08910517489981551E+02)
#define Q02 (+2.10170163753340133E+05)
#define Q03 (+1.67858612416470327E+07)
#define Q04 (+4.90435561733227953E+08)
#define Q05 (+4.54978142622939917E+09)
#define Q06 (+2.87716585708739168E+09)
#define Q07 (-4.59414247951143131E+10)
#define Q08 (-1.72845216404874299E+10)

#define TMPL_OFFSET (+5.00126481056213379E-02)

#define TMPL_NUM_EVAL(x) \
P00+x*(P01+x*(P02+x*(P03+x*(P04+x*(P05+x*(P06+x*(P07+x*P08)))))))

#define TMPL_DEN_EVAL(x) \
Q00+x*(Q01+x*(Q02+x*(Q03+x*(Q04+x*(Q05+x*(Q06+x*(Q07+x*Q08)))))))

TMPL_STATIC_INLINE
double tmpl_Double_LambertW_Negative_Large(double z)
{
    const double p = TMPL_NUM_EVAL(z);
    const double q = TMPL_DEN_EVAL(z);
    return -z / (TMPL_OFFSET + p/q);
}

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
#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04
#undef Q05
#undef Q06
#undef Q07
#undef Q08
#undef TMPL_OFFSET
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
