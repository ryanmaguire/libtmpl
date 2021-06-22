

#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_special_functions.h>

/*  Compute the Bessel I_0 function for a complex value z. This               *
 *  returns double precision, maximum error ~1.e-9.                           */
tmpl_ComplexDouble
tmpl_CDouble_Bessel_I0(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ComplexDouble bessel_I0, arg, exp_arg, sqrt_arg;
    double abs_z, abs_z_real, z_real, z_imag, real_bessel;

    /*  Extract the real part of z.                                           */
    z_real = tmpl_CDouble_Real_Part(z);

    /*  Compute the magnitude of z and the absolute value of its real part.   */
    abs_z = tmpl_CDouble_Abs(z);

    /*  If the real part is zero we obtain the Bessel J0 function.            */
    if (z_real == 0)
    {
        /*  Compute the imaginary part of z and use this to compute Bessel J0.*/
        z_imag = tmpl_CDouble_Imag_Part(z);
        real_bessel = tmpl_Double_Bessel_J0(z_imag);

        /*  The output is I0 = J0 + 0*Imaginary_Unit.                         */
        bessel_I0 = tmpl_CDouble_Rect(real_bessel, 0.0);
        return bessel_I0;
    }

    /*  If z is negative, flip z. That is, negative z so that it lies in the  *
     *  right-half of the complex plane. I0 is even so negation does not      *
     *  change the output, however the asymptotic expansion requires z to lie *
     *  in the right part of the plane.                                       */
    if (z_real < 0.0)
        z = tmpl_CDouble_Multiply_Real(-1.0, z);

    /*  The magnitude of the real part determines if we can use the           *
     *  asymptotic expansion or not. Large real parts result in float         *
     *  overflow, giving us infinity.                                         */
    abs_z_real = tmpl_Double_Abs(z_real);

    /*  For small arguments, use a Taylor series to approximate I_0.          */
    if (abs_z < 16.0)
    {
        /*  The series is in powers of z^2, so use Horner's method with that. */
        arg = tmpl_CDouble_Multiply(z, z);
        bessel_I0 =tmpl_CDouble_Poly_Real_Coeffs(tmpl_Double_Bessel_I0_Taylor,
                                                 24, arg);

    }

    /*  For larger values, use the asymptotic expansion. MAX_DOUBLE_BASE_E is *
     *  defined in rss_ringoccs_math.h, it's the largest value for a double   *
     *  which won't return INFINITY for exp(x).                               */
    else if (abs_z_real < tmpl_Max_Double_Base_E)
    {
        /*  The asymptotic expansion is in terms of 1/z.                      */
        arg = tmpl_CDouble_Reciprocal(z);
        bessel_I0 =
            tmpl_CDouble_Poly_Real_Coeffs(tmpl_Double_Bessel_I0_Asym, 6, arg);

        /*  Multiply by the coefficient factor and return.                    */
        arg = tmpl_CDouble_Multiply_Real(tmpl_Two_Pi, z);
        exp_arg = tmpl_CDouble_Exp(z);
        sqrt_arg = tmpl_CDouble_Sqrt(arg);
        arg = tmpl_CDouble_Divide(exp_arg, sqrt_arg);
        bessel_I0 = tmpl_CDouble_Multiply(bessel_I0, arg);
    }

    /*  For very large inputs, return INFINITY. INFINITY is standard in C99,  *
     *  and provided in rss_ringoccs_math.h otherwise.                        */
    else
        bessel_I0 = tmpl_CDouble_Infinity;

    return bessel_I0;
}


