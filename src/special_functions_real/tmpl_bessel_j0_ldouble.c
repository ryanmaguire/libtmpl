#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

static long double tmpl_LDouble_Bessel_J0_Taylor[31] = {
     1.0L,
    -0.25L,
     1.56250e-2L,
    -4.34027777777777777777777777778e-4L,
     6.78168402777777777777777777778e-6L,
    -6.78168402777777777777777777778e-8L,
     4.70950279706790123456790123457e-10L,
    -2.40280754952443940539178634417e-12L,
     9.38596699032984142731166540690e-15L,
    -2.89690339207711155163940290337e-17L,
     7.24225848019277887909850725841e-20L,
    -1.49633439673404522295423703686e-22L,
     2.59780277210771740096221707789e-25L,
    -3.84290350903508491266600159451e-28L,
     4.90166263907536340901275713585e-31L,
    -5.44629182119484823223639681761e-34L,
     5.31864435663559397679335626720e-37L,
    -4.60090342269515049895619054256e-40L,
     3.55007980146230748376249270259e-43L,
    -2.45850401763317692781336059736e-46L,
     1.53656501102073557988335037335e-49L,
    -8.71068600351890918301219032512e-53L,
     4.49932128280935391684513963074e-56L,
    -2.12633330945621640682662553438e-59L,
     9.22887721118149482129611777074e-63L,
    -3.69155088447259792851844710830e-66L,
     1.36521852236412645285445529153e-69L,
    -4.68181934967121554476836519729e-73L,
     1.49292708854311720177562665730e-76L,
    -4.43795210625183472584906854132e-80L,
     1.23276447395884297940251903925e-83L
};

static long double tmpl_LDouble_Bessel_J0_Asym[9] = {
     1.0L,
     0.1250L,
    -0.07031250L,
    -0.07324218750L,
    0.1121520996093750L,
     0.2271080017089843750L,
    -0.57250142097473144531250L,
    -1.72772750258445739746093750L,
     6.07404200127348303794860839844L
};

/*  Compute the Bessel I_0 function for a long double precision number x.     */
long double tmpl_LDouble_Bessel_J0(long double x)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    long double J0_x, arg;
    long double sinarg, cosarg;

    /*  Bessel J0 is even and in terms of the square of x, so compute this.   */
    arg = x*x;

    /*  For small arguments, use the Taylor series of J_0.                    */
    if (arg < 4.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 12U, arg);
    else if (arg < 16.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 16U, arg);
    else if (arg < 25.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 18U, arg);
    else if (arg < 36.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 19U, arg);
    else if (arg < 49.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 21U, arg);
    else if (arg < 64.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 23U, arg);
    else if (arg < 81.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 24U, arg);
    else if (arg < 100.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 26U, arg);
    else if (arg < 121.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 27U, arg);
    else if (arg < 144.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 29U, arg);
    else if (arg < 196.0L)
        J0_x = tmpl_LDouble_Poly_Eval(tmpl_LDouble_Bessel_J0_Taylor, 30U, arg);

    /*  For large arguments use the asymptotic expansion.                     */
    else if (arg < 1.0e32L)
    {
        /*  J_0 is an even function so use the absolute value of x.           */
        x = tmpl_LDouble_Abs(x);

        /*  The argument for the asymptotic expansion is 1/x^2.               */
        arg = 1.0L/arg;

        /*  Use Horner's method to compute the polynomial part.               */
        sinarg  = arg * tmpl_LDouble_Bessel_J0_Asym[7] +
                        tmpl_LDouble_Bessel_J0_Asym[5];
        sinarg  = arg * sinarg + tmpl_LDouble_Bessel_J0_Asym[3];
        sinarg  = arg * sinarg + tmpl_LDouble_Bessel_J0_Asym[1];

        /*  Multiply the output by the coefficient factor.                    */
        sinarg *= tmpl_LDouble_Sin(x - tmpl_Pi_By_Four_L)/x;

        /*  Do the same as above for the Cosine portion.                      */
        cosarg  = arg * tmpl_LDouble_Bessel_J0_Asym[8] +
                        tmpl_LDouble_Bessel_J0_Asym[6];
        cosarg  = arg * cosarg + tmpl_LDouble_Bessel_J0_Asym[4];
        cosarg  = arg * cosarg + tmpl_LDouble_Bessel_J0_Asym[2];
        cosarg  = arg * cosarg + tmpl_LDouble_Bessel_J0_Asym[0];
        cosarg *= tmpl_LDouble_Cos(x - tmpl_Pi_By_Four_L);

        /*  For very large arguments, use the limit (which is zero).          */
        J0_x = (cosarg + sinarg)*tmpl_Sqrt_Two_By_Pi_L;
        J0_x = J0_x / tmpl_LDouble_Sqrt(x);
    }

    /*  For very large arguments, use the limit (which is zero).              */
    else
        J0_x = 0.0L;

    return J0_x;
}
