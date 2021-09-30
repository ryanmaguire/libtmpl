/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *  This file creates a complex plot of (z^3 - 1)/(3z^2). The color is given  *
 *  by the argument, and the intensity is given by the modulus. This function *
 *  was chosen to try and better understand the dynamics of the Newton        *
 *  for z^3-1. The iterative step is z_{n+1} = z_{n} - (z_{n}^3-1)/(3z_{n}^2) *
 *  hence the choice of this function.                                        *
 *                                                                            *
 *  This file is compliant with the C89 standard and does not use C99         *
 *  features (basic complex number struct is provided here). The only         *
 *  dependencies are math.h and stdio.h, two standard library headers.        *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2021/09/30                                                        *
 ******************************************************************************/

/*  fprintf, FILE, and more found here.                                       */
#include <stdio.h>

/*  Basic math routines here.                                                 */
#include <math.h>

/*  Some implementations of math.h provide a PI macro. Some don't. Check this.*/
#ifndef PI
#define PI 3.141592653589793
#endif

/*  This shouldn't be defined, but check anyways.                             */
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
    const double denom = 1.0 / (w.real*w.real + w.imag*w.imag);

    quot.real = (z.real*w.real + z.imag*w.imag)*denom;
    quot.imag = (z.imag*w.real - z.real*w.imag)*denom;
    return quot;
}
/*  End of complex_division.                                                  */

/*  Function for scaling the intensity of a color by a real number.           */
static struct color scale_color(struct color c, double t)
{
    struct color out;
    out.red = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue = (unsigned char)(t * (double)c.blue);
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
    const double t = TWO_BY_PI * atan(5.0*abs);
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

    /*  Scale the color by |z| to differentiate complex numbers by intensity. */
    return scale_color(out, t);
}
/*  End of rainbow_gradient.                                                  */

/*  The rational function (z^3 - 1)/(3z^2).                                   */
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

/*  Function for plotting f.                                                  */
int main(void)
{
    /*  The width and height of the image, in pixels.                         */
    const unsigned int width = 1024U;
    const unsigned int height = 1024U;

    /*  The box [x0, x1]x[y0, y1] that is being plotted in the plane.         */
    const double xmin = -2.0;
    const double xmax =  2.0;
    const double ymin = -2.0;
    const double ymax =  2.0;

    /*  Variables for indexing over the pixels of the image.                  */
    unsigned int x, y;

    /*  Complex number for looping over points in the plane.                  */
    struct complex_number z;

    /*  Color struct to represent a given point in the plane.                 */
    struct color current_color;

    /*  Scale factors to go from pixel in the image to point in the plane.    */
    const double xfactor = (xmax - xmin) / (double)(width - 1U);
    const double yfactor = (ymax - ymin) / (double)(height - 1U);

    /*  Open a file and give it write permission.                             */
    FILE *fp = fopen("complex_plot_z3_minus_1_over_3z2.ppm", "w");

    /*  fopen returned NULL on failure. Check for this.                       */
    if (!fp)
    {
        puts("fopen failed and return NULL. Aborting.");
        return -1;
    }

    /*  Otherwise, print the preamble to the PPM file.                        */
    fprintf(fp, "P6\n%u %u\n255\n", width, height);

    /*  Loop over the y coordinates.                                          */
    for (y = 0U; y < height; ++y)
    {
        /*  Compute the current imaginary part of z.                          */
        z.imag = ymax - (double)y * yfactor;

        /*  Loop over the x coordinates.                                      */
        for (x = 0U; x < width; ++x)
        {
            /*  Compute the real part of z.                                   */
            z.real = xmin + (double)x * xfactor;

            /*  Calculate the color corresponding to f(z).                    */
            current_color = get_color(f(z));

            /*  Write the color to the file.                                  */
            write_color(fp, current_color);
        }
        /*  End of for-loop for x.                                            */
    }
    /*  End of for-loop for y.                                                */

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
