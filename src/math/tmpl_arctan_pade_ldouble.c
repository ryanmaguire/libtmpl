/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if !defined(TMPL_USE_INLINE) || TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

#define P4 -6.786553005040399998383191660502584872333E-03L
#define P3 -1.073552227908707342586157269925514065275E-01L
#define P2 -4.461152882205513784461152882205513784461E-01L
#define P1 -6.730158730158730158730158730158730158730E-01L
#define P0 -3.333333333333333333333333333333333333333E-01L
#define Q5 7.859014050964515360800190521552750654918E-03L
#define Q4 1.702786377708978328173374613003095975232E-01L
#define Q3 1.021671826625386996904024767801857585139E00L
#define Q2 2.481203007518796992481203007518796992481E00L
#define Q1 2.619047619047619047619047619047619047619E00L
#define Q0 1.000000000000000000000000000000000000000E00L

long double tmpl_LDouble_Arctan_Pade(long double x)
{
    const long double x2 = x*x;
    const long double p = x2*(P0 + x2*(P1 + x2*(P2 + x2*(P3 + x2*P4))));
    const long double q = Q0 + x2*(Q1 + x2*(Q2 + x2*(Q3 + x2*(Q4 + x2*Q5))));
    return x*(1.0L + p/q);
}

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
/*  #if !defined(TMPL_USE_INLINE) || TMPL_USE_INLINE != 1.                    */
