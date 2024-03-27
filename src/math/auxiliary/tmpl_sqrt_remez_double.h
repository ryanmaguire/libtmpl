
/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SQRT_REMEZ_DOUBLE_H
#define TMPL_SQRT_REMEZ_DOUBLE_H

/*  Coefficients for the Remez polynomial.                                    */
#define A0 (+1.0000000009213793132422080333230191911611046603122E+00)
#define A1 (+4.9999787298570402278901738280028337776415357546897E-01)
#define A2 (-1.2427211443985097757833168706757977964507907886005E-01)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A0 + z*(A1 + z*A2)

TMPL_STATIC_INLINE
double tmpl_Double_Sqrt_Remez(double x)
{
    /*  The series is computed at x = 1. Shift the input.                     */
    const double xs = x - 1.0;

    /*  Use Horner's method to evaluate the polynomial.                       */
    return TMPL_POLY_EVAL(xs);
}
/*  End of tmpl_Double_Sqrt_Remez.                                            */

#undef A0
#undef A1
#undef A2
#undef TMPL_POLY_EVAL

#endif
