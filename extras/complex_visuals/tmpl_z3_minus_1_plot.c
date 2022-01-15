/*  Microsoft "deprecated" the fopen function in favor of the fopen_s         *
 *  function. The actual working group for the C language has not deprecated  *
 *  fopen, and fopen_s was only introduced in the C11 standard, so I will     *
 *  still use fopen. To avoid a "deprecated" warning on Microsoft's MSVC,     *
 *  first check that the user is running windows, then define this macro.     *
 *  Unix-based (GNU, Linux, macOS, FreeBSD, etc.) platforms yield no warnings.*/
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  fprintf, FILE, and more found here.                                       */
#include <stdio.h>

/*  Basic math routines here.                                                 */
#include <math.h>

/*  Some implementations of math.h provide a PI macro. Some don't. Check this.*/
#ifndef PI
#define PI 3.141592653589793
#endif

struct complex_number {
    double real, imag;
};

struct color {
    unsigned char red, green, blue;
};

static void write_color(struct color c, FILE *fp)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}

static double complex_arg(struct complex_number z)
{
    return atan2(z.imag, z.real);
}

static double complex_abs(struct complex_number z)
{
    return sqrt(z.real*z.real + z.imag*z.imag);
}

static struct color rainbow_gradient(double val)
{
    /*  Declare an output struct for the color we're computing.               */
    struct color out;
    val = (val + M_PI)*1023.0/(2.0*M_PI);

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

    return out;
}
/*  End of rainbow_gradient.                                                  */

static struct color scale_color(struct color c, double t)
{
    struct color out;
    out.red   = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue  = (unsigned char)(t * (double)c.blue);
    return out;
}

static struct color get_color(struct complex_number z)
{
    double arg = complex_arg(z);
    double abs = complex_abs(z);
    double t = 2.0/M_PI * atan(5.0*abs);
    struct color out = rainbow_gradient(arg);
    out = scale_color(out, t);
    return out;
}

static struct complex_number f(struct complex_number z)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number out;

    /*  Compute z^3, and then subtract 1 from the real part.                  */
    out.real = z.real*z.real*z.real - 3.0*z.real*z.imag*z.imag - 1.0;
    out.imag = 3.0*z.real*z.real*z.imag - z.imag*z.imag*z.imag;
    return out;
}

int main(void)
{
    const unsigned int width = 1024U;
    const unsigned int height = 1024U;
    const double xmin = -2.0;
    const double xmax =  2.0;
    const double ymin = -2.0;
    const double ymax =  2.0;
    unsigned int x, y;
    struct complex_number z;
    struct color current_color;
    const double xfactor = (xmax - xmin) / (double)(width - 1U);
    const double yfactor = (ymax - ymin) / (double)(height - 1U);
    FILE *fp = fopen("complex_plot_z3_minus_1.ppm", "w");
    fprintf(fp, "P6\n%u %u\n255\n", width, height);

    for (y = 0U; y < height; ++y)
    {
        z.imag = ymax - (double)y * yfactor;
        for (x = 0U; x < width; ++x)
        {
            z.real = xmin + (double)x * xfactor;
            current_color = get_color(f(z));
            write_color(current_color, fp);
        }
    }
    fclose(fp);
    return 0;
}
