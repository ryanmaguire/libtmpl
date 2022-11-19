#ifndef TMPL_MATH_SIN_PADE_PI_INLINE_H
#define TMPL_MATH_SIN_PADE_PI_INLINE_H

#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/tmpl_math.h>

#define P5 (-1.326704727342721470669055072831298848429E-09)
#define P4 (5.598649443506351144049005322725000700547E-07)
#define P3 (-8.729668102813383765882747644727845428251E-05)
#define P2 (5.837572014686924154215552897431476591273E-03)
#define P1 (-1.509578793694727814326849370942536167352E-01)
#define P0 (1.0)

#define Q5 (3.387582241998014353822768271665615717203E-12)
#define Q4 (1.946668781997946805314637818154451688036E-09)
#define Q3 (6.044395000441469584887798898086945171697E-07)
#define Q2 (1.223698975525716932125078261669849131795E-04)
#define Q1 (1.570878729719388523398172957241304993144E-02)
#define Q0 (1.0)

static inline double tmpl_Double_Sin_Pade_Pi(double x)
{
    const double y = tmpl_One_Pi - x;
    const double y2 = y*y;
    const double p = y*(P0 + y2*(P1 + y2*(P2 + y2*(P3 + y2*(P4 + y2*P5)))));
    const double q =    Q0 + y2*(Q1 + y2*(Q2 + y2*(Q3 + y2*(Q4 + y2*Q5))));
    return p/q;
}

#undef P5
#undef P4
#undef P3
#undef P2
#undef P1
#undef P0
#undef Q5
#undef Q4
#undef Q3
#undef Q2
#undef Q1
#undef Q0

#endif
#endif
