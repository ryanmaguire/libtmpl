#include <stdio.h>
#include <math.h>

#ifndef PI
#define PI 3.141592653589793
#endif

#ifndef TWO_BY_PI
#define TWO_BY_PI 0.6366197723675814
#endif

/*  1023 / 2 pi.                                                              */
#define GRADIENT_FACTOR 162.81550678300894

/*  Struct for dealing with complex numbers.                                  */
struct complex_number {
    double real, imag;
};

/*  Struct for dealing with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;
};

/*  Function for writing a color to a PPM file.                               */
static void write_color(FILE *fp, struct color c)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}
/*  End of write_color.                                                       */

/*  Function for computing the argument of a complex number.                  */
static double complex_arg(struct complex_number z)
{
    return atan2(z.imag, z.real);
}

/*  Function for computing the modulus, or magnitude, of a complex number.    */
static double complex_abs(struct complex_number z)
{
    return sqrt(z.real*z.real + z.imag*z.imag);
}

/*  Function for dividing complex numbers.                                    */
static struct complex_number
complex_divide(struct complex_number z, struct complex_number w)
{
    /*  Declare a variable for the quotient.                                  */
    struct complex_number quot;

    /*  The quotient z/w can be written as z * (1/w). Use this.               */
    double denom = 1.0 / (w.real*w.real + w.imag*w.imag);

    quot.real = (z.real*w.real + z.imag*w.imag)*denom;
    quot.imag = (z.imag*w.real - z.real*w.imag)*denom;
    return quot;
}
/*  End of complex_division.                                                  */

/*  Function for scaling the intensity of a color by a real number.           */
static struct color scale_color(struct color c, double t)
{
    struct color out;
    out.red   = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue  = (unsigned char)(t * (double)c.blue);
    return out;
}
/*  End of scale_color.                                                       */

/*  Function for creating a continuous gradient of color in the RGB spectrum. */
static struct color get_color(struct complex_number z)
{
    /*  Declare an output struct for the color we're computing.               */
    struct color out;
    const double arg = complex_arg(z);
    const double abs = complex_abs(z);
    const double t   = TWO_BY_PI * atan(5.0*abs);
    double val = (arg + PI)*GRADIENT_FACTOR;

    /*  Split [0, 1023] into four parts, [0, 255], [256, 511], [512, 767],    *
     *  and [768, 1023]. Create a blue-to-red rainbow gradient from this.     *
     *  The first interval corresponds to blue to blue-green.                 */
    if (val < 256.0)
    {
        out.red   = (unsigned char)0;
        out.green = (unsigned char)(val);
        out.blue  = (unsigned char)255;
    }

    /*  Next we do blue-green to green.                                       */
    else if (val < 512.0)
    {
        /*  Subtract 256 from val so that val lies in [0, 255], which are the *
         *  allowed values for an 8-bit unsigned char.                        */
        val -= 256.0;
        out.red   = (unsigned char)0;
        out.green = (unsigned char)255;
        out.blue  = (unsigned char)(256.0 - val);
    }

    /*  Next is green to yellow.                                              */
    else if (val < 768.0)
    {
        /*  Subtract by 512 to get val in [0, 255].                           */
        val -= 512.0;
        out.red   = (unsigned char)(val);
        out.green = (unsigned char)255;
        out.blue  = (unsigned char)0;
    }

    /*  Finally, yellow to red.                                               */
    else
    {
        /*  Subtract by 768 to get val in the range [0, 255].                 */
        val -= 768.0;
        out.red   = (unsigned char)255;
        out.green = (unsigned char)(256.0 - val);
        out.blue  = (unsigned char)0;
    }

    return scale_color(out, t);
}
/*  End of rainbow_gradient.                                                  */

static struct complex_number f(struct complex_number z)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number numer, denom;

    /*  Compute z^3, and then subtract 1 from the real part.                  */
    numer.real = z.real*z.real*z.real - 3.0*z.real*z.imag*z.imag - 1.0;
    numer.imag = 3.0*z.real*z.real*z.imag - z.imag*z.imag*z.imag;
    denom.real = 3.0*(z.real*z.real - z.imag*z.imag);
    denom.imag = 6.0*z.real*z.imag;

    return complex_divide(numer, denom);
}

int main(void)
{
    const unsigned int width = 1024U;
    const unsigned int height = 1024U;
    const double xmin = -2.0;
    const double xmax =  2.0;
    const double ymin = -2.0;
    const double ymax =  2.0;
    double _X = 0.0;
    unsigned int x, y;
    struct complex_number z;
    struct color current_color;
    const double xfactor = (xmax - xmin) / (double)(width - 1U);
    const double yfactor = (ymax - ymin) / (double)(height - 1U);
    FILE *fp = fopen("complex_plot_z3_minus_1_over_3z2.ppm", "w");
    fprintf(fp, "P6\n%u %u\n255\n", width, height);

    printf("%f\n", _X);
    for (y = 0U; y < height; ++y)
    {
        z.imag = ymax - (double)y * yfactor;
        for (x = 0U; x < width; ++x)
        {
            z.real = xmin + (double)x * xfactor;
            current_color = get_color(f(z));
            write_color(fp, current_color);
        }
    }
    fclose(fp);
    return 0;
}


