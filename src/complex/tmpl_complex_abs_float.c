/*  Header file containing basic math functions.                              */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are given and where complex types are defined.       */
#include <libtmpl/include/tmpl_complex.h>

/*  If the user has not requested tmpl algorithms, use functions from math.h. */
#if TMPL_USE_MATH_ALGORITHMS != 1
#include <math.h>

/*  Set macros for the square root and absolute value functions for later.    *
 *  this avoids more checks for TMPL_USE_MATH_ALGORITHMS in the code.         */
#define square_root sqrtf
#define absolute_value fabsf

#else
/*  Else for #if TMPL_USE_MATH_ALGORITHMS != 1                                */

/*  If the user requested tmpl algorithms, alias the appropriate functions.   */
#define square_root tmpl_Float_Sqrt
#define absolute_value tmpl_Float_Abs

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

/*  The values 2^64 and 2^-64, to single precision, stored as macros.         */
#define BIG_SCALE 1.8446744073709552E+19F
#define RCPR_BIG_SCALE 5.4210108624275222E-20F

/*  Function for computing the magnitude, or modulus, of a complex number.    */
float tmpl_CFloat_Abs(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Float w;

    /*  Given z = x + iy = (x, y), compute |x| and |y|.                       */
    float x = absolute_value(z.dat[0]);
    float y = absolute_value(z.dat[1]);

    /*  Compute the maximum of |x| and |y| and store it in the float          *
     *  part of the tmpl_IEEE754_Float union w. This syntax from the C        *
     *  language is a bit strange. a = (b < c ? c : b) says if b is less than *
     *  c, set a to c, otherwise set a to b.                                  */
    w.r = (x < y ? y : x);

    /*  We want to check if the exponent is less than 64, which is 0x40 in    *
     *  hexidecimal. The exponent of a float is offset by a bias. To check    *
     *  if the exponent is less than 64, check if the exponent part of the    *
     *  float is less than 64 plus the bias.                                  */
    if (w.bits.expo < TMPL_FLOAT_BIAS + 0x40U)
    {
        /*  If both exponents are greater than -64, then both |x| and         *
         *  |y| lie between 2^-64 and 2^64 meaning neither of the             *
         *  values x^2 or y^2 overflow or underflow. It is possible           *
         *  the maximum of |x| and |y| has exponent slightly greater than     *
         *  -64, but the other value has exponent slightly less. To ensure    *
         *  accuracy to 16 decimals, check if the exponent is greater than    *
         *  -52. If the difference in the exponents of |x| and |y| is         *
         *  greater than 10, then to at least 16 decimals we have             *
         *  |z| = max(|x|, |y|).                                              */
        if (w.bits.expo > 0x4BU)
            return square_root(x*x + y*y);

        /*  Both |x| and |y| are small. To avoid underflow scale by 2^512.    */
        x *= BIG_SCALE;
        y *= BIG_SCALE;

        /*  |z| can now be computed as 2^-512 * sqrt(x^2 + y^2)               *
         *  without the risk of underflow. Return this.                       */
        return RCPR_BIG_SCALE * square_root(x*x + y*y);
    }

    /*  Both |x| and |y| are large. To avoid overflow scale by 2^-512.        */
    x *= RCPR_BIG_SCALE;
    y *= RCPR_BIG_SCALE;

    /*  |z| can now be computed as |z| = 2^512 * sqrt(x^2 + y^2) without      *
     *  the risk of overflow. Return this.                                    */
    return BIG_SCALE * square_root(x*x + y*y);
}
/*  End of tmpl_CFloat_Abs.                                                   */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef BIG_SCALE
#undef RCPR_BIG_SCALE

#else
/*  #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1        */

/*  Lacking IEEE-754 support, we can use the standard trick to avoid          *
 *  underflows and overflows that is used in the hypot (hypotenuse) functions.*
 *  This is about 1.4x slower than the method above, but is portable. The     *
 *  reason for the slowness is above we multiply by constants, whereas this   *
 *  algorithm requires divisions and multiplications by non-constants.        */

/*  Function for computing the magnitude, or modulus, of a complex number.    */
float tmpl_CFloat_Abs(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float rcpr_t;

    /*  Given z = x + iy = (x, y), compute |x| and |y|.                       */
    float x = absolute_value(z.dat[0]);
    float y = absolute_value(z.dat[1]);

    /*  Compute the maximum of |x| and |y| and store it in the double         *
     *  part of the tmpl_IEEE754_Double union w. This syntax from the C       *
     *  language is a bit strange. a = (b < c ? c : b) says if b is less than *
     *  c, set a to c, otherwise set a to b.                                  */
    const float t = (x < y ? y : x);

    /*  Division by zero is generally viewed as bad. If the max of |x| and    *
     *  |z| is zero, |z| = 0. Return this.                                    */
    if (t == 0.0F)
        return 0.0F;

    /*  Precompute 1/t to turn 2 divisions into 1 division and 2 products.    */
    rcpr_t = 1.0F / t;

    /*  Scale x and y by 1/t.                                                 */
    x *= rcpr_t;
    y *= rcpr_t;

    /*  |z| can safely be computed as |z| = t * sqrt((x/t)^2 + (y/t)^2)       *
     *  without risk of underflow or overflow.                                */
    return t * square_root(x*x + y*y);
}
/*  End of tmpl_CFloat_Abs.                                                   */

#endif
/*  #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1        */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef square_root
#undef absolute_value
