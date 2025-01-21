#include <libtmpl/include/constants/tmpl_math_constants.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_special_functions_real.h>
#include <libtmpl/include/tmpl_special_functions_complex.h>

/*  Define the first 25 coefficients of the Taylor series.                    */
#define tmpl_BESSEL_I0_TAYLOR_00 1.0
#define tmpl_BESSEL_I0_TAYLOR_01 0.25
#define tmpl_BESSEL_I0_TAYLOR_02 1.56250e-2
#define tmpl_BESSEL_I0_TAYLOR_03 4.34027777777777777777777777778e-4
#define tmpl_BESSEL_I0_TAYLOR_04 6.78168402777777777777777777778e-6
#define tmpl_BESSEL_I0_TAYLOR_05 6.78168402777777777777777777778e-8
#define tmpl_BESSEL_I0_TAYLOR_06 4.70950279706790123456790123457e-10
#define tmpl_BESSEL_I0_TAYLOR_07 2.40280754952443940539178634417e-12
#define tmpl_BESSEL_I0_TAYLOR_08 9.38596699032984142731166540690e-15
#define tmpl_BESSEL_I0_TAYLOR_09 2.89690339207711155163940290337e-17
#define tmpl_BESSEL_I0_TAYLOR_10 7.24225848019277887909850725841e-20
#define tmpl_BESSEL_I0_TAYLOR_11 1.49633439673404522295423703686e-22
#define tmpl_BESSEL_I0_TAYLOR_12 2.59780277210771740096221707789e-25
#define tmpl_BESSEL_I0_TAYLOR_13 3.84290350903508491266600159451e-28
#define tmpl_BESSEL_I0_TAYLOR_14 4.90166263907536340901275713585e-31
#define tmpl_BESSEL_I0_TAYLOR_15 5.44629182119484823223639681761e-34
#define tmpl_BESSEL_I0_TAYLOR_16 5.31864435663559397679335626720e-37
#define tmpl_BESSEL_I0_TAYLOR_17 4.60090342269515049895619054256e-40
#define tmpl_BESSEL_I0_TAYLOR_18 3.55007980146230748376249270259e-43
#define tmpl_BESSEL_I0_TAYLOR_19 2.45850401763317692781336059736e-46
#define tmpl_BESSEL_I0_TAYLOR_20 1.53656501102073557988335037335e-49
#define tmpl_BESSEL_I0_TAYLOR_21 8.71068600351890918301219032512e-53
#define tmpl_BESSEL_I0_TAYLOR_22 4.49932128280935391684513963074e-56
#define tmpl_BESSEL_I0_TAYLOR_23 2.12633330945621640682662553438e-59
#define tmpl_BESSEL_I0_TAYLOR_24 9.22887721118149482129611777074e-63

/*  And the first 7 terms of the asymptotic series.                           */
#define tmpl_BESSEL_I0_ASYM_00 1.0
#define tmpl_BESSEL_I0_ASYM_01 0.1250
#define tmpl_BESSEL_I0_ASYM_02 0.07031250
#define tmpl_BESSEL_I0_ASYM_03 0.07324218750
#define tmpl_BESSEL_I0_ASYM_04 0.1121520996093750
#define tmpl_BESSEL_I0_ASYM_05 0.2271080017089843750
#define tmpl_BESSEL_I0_ASYM_06 0.5725014209747314453125

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
        bessel_I0 = tmpl_CDouble_Multiply_Real(tmpl_BESSEL_I0_TAYLOR_24, arg);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_23, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_22, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_21, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_20, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_19, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_18, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_17, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_16, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_15, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_14, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_13, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_12, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_11, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_10, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_09, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_08, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_07, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_06, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_05, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_04, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_03, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_02, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_01, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_TAYLOR_00, bessel_I0);
    }

    /*  For larger values, use the asymptotic expansion.                      */
    else if (abs_z_real < tmpl_Max_Double_Base_E)
    {
        /*  The asymptotic expansion is in terms of 1/z.                      */
        arg = tmpl_CDouble_Reciprocal(z);
        bessel_I0 = tmpl_CDouble_Multiply_Real(tmpl_BESSEL_I0_ASYM_06, arg);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_ASYM_05, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_ASYM_04, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_ASYM_03, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_ASYM_02, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_ASYM_01, bessel_I0);
        bessel_I0 = tmpl_CDouble_Multiply(arg, bessel_I0);
        bessel_I0 = tmpl_CDouble_Add_Real(tmpl_BESSEL_I0_ASYM_00, bessel_I0);

        /*  Multiply by the coefficient factor and return.                    */
        arg = tmpl_CDouble_Multiply_Real(tmpl_Double_Two_Pi, z);
        exp_arg = tmpl_CDouble_Exp(z);
        sqrt_arg = tmpl_CDouble_Sqrt(arg);
        arg = tmpl_CDouble_Divide(exp_arg, sqrt_arg);
        bessel_I0 = tmpl_CDouble_Multiply(bessel_I0, arg);
    }

    /*  For very large inputs, return infinity.                               */
    else
        bessel_I0 = TMPL_CINFINITY;

    return bessel_I0;
}

/*  Undefine all of the macros.                                               */
#undef tmpl_BESSEL_I0_TAYLOR_00
#undef tmpl_BESSEL_I0_TAYLOR_01
#undef tmpl_BESSEL_I0_TAYLOR_02
#undef tmpl_BESSEL_I0_TAYLOR_03
#undef tmpl_BESSEL_I0_TAYLOR_04
#undef tmpl_BESSEL_I0_TAYLOR_05
#undef tmpl_BESSEL_I0_TAYLOR_06
#undef tmpl_BESSEL_I0_TAYLOR_07
#undef tmpl_BESSEL_I0_TAYLOR_08
#undef tmpl_BESSEL_I0_TAYLOR_09
#undef tmpl_BESSEL_I0_TAYLOR_10
#undef tmpl_BESSEL_I0_TAYLOR_11
#undef tmpl_BESSEL_I0_TAYLOR_12
#undef tmpl_BESSEL_I0_TAYLOR_13
#undef tmpl_BESSEL_I0_TAYLOR_14
#undef tmpl_BESSEL_I0_TAYLOR_15
#undef tmpl_BESSEL_I0_TAYLOR_16
#undef tmpl_BESSEL_I0_TAYLOR_17
#undef tmpl_BESSEL_I0_TAYLOR_18
#undef tmpl_BESSEL_I0_TAYLOR_19
#undef tmpl_BESSEL_I0_TAYLOR_20
#undef tmpl_BESSEL_I0_TAYLOR_21
#undef tmpl_BESSEL_I0_TAYLOR_22
#undef tmpl_BESSEL_I0_TAYLOR_23
#undef tmpl_BESSEL_I0_TAYLOR_24
#undef tmpl_BESSEL_I0_ASYM_00
#undef tmpl_BESSEL_I0_ASYM_01
#undef tmpl_BESSEL_I0_ASYM_02
#undef tmpl_BESSEL_I0_ASYM_03
#undef tmpl_BESSEL_I0_ASYM_04
#undef tmpl_BESSEL_I0_ASYM_05
#undef tmpl_BESSEL_I0_ASYM_06
