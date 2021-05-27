/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *  Purpose:                                                                  *
 *      Use the algorithm by Hubbard, Schleicher, and Sutherland to find all  *
 *      roots of a complex polynomial, rather than precomputing them.         *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as part of libtmpl.       *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 26, 2021                                                  *
 ******************************************************************************/

/*  The fopen, fprintf, and FILE data type are here.                          */
#include <stdio.h>
#include <math.h>
#include <complex.h>

/*  Struct for dealing with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;
};

/*  Function for evaluating a polynomial at a complex number z given the      *
 *  coefficients of the polynomial. This uses Horner's method.                */
static complex double
poly_eval(complex double z, complex double *arr, unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    complex double out;
    unsigned int n;

    /*  Initialize out to the coefficient of z^deg.                           */
    out = arr[0];

    /*  Loop over the coefficients and apply Horner's method.                 */
    for (n = 1U; n <= deg; ++n)
        out = z*out + arr[n];

    return out;
}
/*  End of poly_eval.                                                         */

/*  Function for computing the derivative of a polynomial using               *
 *  Horner's method.                                                          */
static complex double
poly_prime_eval(complex double z, complex double *arr, unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    complex double out;
    const double factor = (double)deg;
    unsigned int n;

    /*  Intialize the output to the coefficient of z^deg times deg. This is   *
     *  because the derivative of z^deg is deg*z^(deg-1).                     */
    out = factor*arr[0];

    /*  Loop over the coefficients and perform Horner's method.               */
    for (n = 1U; n < deg; ++n)
        out = z*out + factor*arr[n];

    return out;
}
/*  End of poly_prime_eval.                                                   */

/*  Compute the second derivative of a polynomial using Horner's method.      */
static complex double
poly_2prime_eval(complex double z, complex double *arr, unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    complex double out;
    const double factor = (double)deg * ((double)deg - 1.0);
    unsigned int n;

    /*  Initialize the output.                                                */
    out = factor*arr[0];

    /*  Loop over the coefficients and perform Horner's method.               */
    for (n = 1; n < deg-1; ++n)
        out = z*out + factor*arr[n];

    return out;
}
/*  End of poly_2prime_eval.                                                  */

/*  Function for writing a color to a PPM file.                               */
static void write_color(FILE *fp, struct color c)
{
    fputc(c.red,   fp);
    fputc(c.green, fp);
    fputc(c.blue,  fp);
}
/*  End of write_color.                                                       */

/*  Function for scaling the intensitity of a color by a real number.         */
static struct color scale_color(struct color c, double t)
{
    struct color out;
    out.red   = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue  = (unsigned char)(t * (double)c.blue);
    return out;
}
/*  End of scale_color.                                                       */

/*  Function for computing the factor that occurs in Halley's method.         */
static complex double
halley_factor(complex double z, complex double *arr, unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    const complex double f_of_z              = poly_eval(z, arr, deg);
    const complex double f_prime_of_z        = poly_prime_eval(z, arr, deg);
    const complex double f_double_prime_of_z = poly_2prime_eval(z, arr, deg);
    complex double numer, denom;

    /*  The numerator is f(z)f'(z) and the denominator is                     *
     *  f'(z)^2 - 0.5 f(z)f''(z). Return this.                                */
    numer = f_of_z * f_prime_of_z;
    denom = f_prime_of_z*f_prime_of_z - 0.5*f_of_z*f_double_prime_of_z;
    return numer / denom;
}
/*  End of halley_factor.                                                     */

/*  Function for drawing the Halley fractal for z^10 - 1.                     */
int main(void)
{
    /*  Variable for the width of the PPM file.                               */
    const unsigned int width = 2048U;

    /*  And a variable for the height of the PPM.                             */
    const unsigned int height = 2048U;

    /*  Maximum number of iterations allowed in Halley's method and the       *
     *  maximum number of iterations allowed in the                           *
     *  Hubbard-Schleicher-Sutherland algorithm for finding the roots.        */
    const unsigned char MaxIters = 0x10U;

    /*  The coefficients of the polynomial we're using. This is z^10 - 1.     */
    complex double arr[11] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1};

    /*  Variable for the roots of this polynomial. The fundamental theorem of *
     *  algebra tells us there are at most 10 since the polynomial is degree  *
     *  10. For z^10 - 1, there are exactly 10.                               */
    complex double roots[sizeof(arr)/sizeof(arr[0]) - 1U];

    /*  Variable for the degree of the polynomial.                            */
    const unsigned int deg = sizeof(roots) / sizeof(roots[0]);

    /*  Variables used in Halley's method.                                    */
    complex double f_z;

    /*  Values for the min and max of the x and y axes.                       */
    const double x_min = -1.0;
    const double x_max =  1.0;
    const double y_min = -1.0;
    const double y_max =  1.0;

    /*  Factor used in the root-finding algorithm.                            */
    const double s_double = ceil(0.26632*log((double)deg));
    const double N_double = ceil(8.32547*(double)deg*log((double)deg));

    const unsigned int s = (unsigned int)s_double;
    const unsigned int N = (unsigned int)N_double;

    /*  These three factors occur in the root-finding algorithm.              */
    const double factor_1     = 2.4142135623730951;
    const double factor_2     = ((double)deg - 1.0) / (double)deg;
    const double theta_factor = 6.283185307179586 / (double)N;
    const double r_factor     = 0.25 / (double)s;

    /*  Factor for converting from pixel to point in the plane.               */
    const double factor_x = (x_max - x_min)/(double)width;
    const double factor_y = (y_max - y_min)/(double)height;

    /*  Factor for giving the image a gradient.                               */
    double factor = 1.0 / (double)MaxIters;

    /* Dummy variables to loop over.                                          */
    unsigned char iters;
    unsigned int ind, x, y;

    /*  Variables for the tolerance of finding a root.                        */
    const double toler = 1.0E-4;
    const double EPS   = 1.0E-8;

    /*  Variables for the real and imaginary parts of a complex number.       */
    double z_x, z_y;
    complex double z;

    /*  Scale factor for giving a gradient to the image.                      */
    double scale;

    unsigned int m, n, ell, n_roots;
    double r, theta, min, temp;

    struct color current_color;
    const struct color black = {0x00U, 0x00U, 0x00U};
    const struct color colors[14] = {
        {0xFFU, 0x00U, 0x1FU},  /*  Red.           */
        {0x00U, 0xFFU, 0x1FU},  /*  Green.         */
        {0x00U, 0x1FU, 0xFFU},  /*  Blue.          */
        {0xFFU, 0xFFU, 0x33U},  /*  Yellow.        */
        {0x80U, 0xD4U, 0xFFU},  /*  Light Blue.    */
        {0xFFU, 0x1DU, 0xCCU},  /*  Magenta.       */
        {0x00U, 0x80U, 0x80U},  /*  Teal.          */
        {0xFFU, 0x00U, 0xFFU},  /*  Purple.        */
        {0xFFU, 0x55U, 0x00U},  /*  Orange.        */
        {0x4DU, 0xFFU, 0xC3U},  /*  Turquoise.     */
        {0x00U, 0x80U, 0x6AU},  /*  Pine.          */
        {0xFFU, 0xBFU, 0xB3U},  /*  Melon.         */
        {0xFFU, 0xB3U, 0xE6U},  /*  Mauve.         */
        {0x66U, 0x43U, 0x66U}   /*  Midnight blue. */
    };

    /*  Declare a variable for the output file and give it write permission.  */
    FILE *fp = fopen("halley_fractal.ppm", "w");

    /*  Check if fopen failed.                                                */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    n_roots = 0;
    for (m = 0U; m < s; ++m)
    {
        if (n_roots >= deg)
            break;

        r = factor_1 + pow(factor_2, (2.0*m + 1.0) * r_factor);

        for (n = 0U; n < N; ++n)
        {
            if (n_roots >= deg)
                break;

            theta = theta_factor * (double)n;
            z   = r * (cos(theta) + (complex double)_Complex_I*sin(theta));
            f_z = poly_eval(z, arr, deg);
            iters = 0x00U;

            /*  Allow MaxIters number of iterations of Newton-Raphson.        */
            while ((cabs(f_z) > EPS) && (iters < MaxIters))
            {
                /*  Perfrom Halley's Method on the polynomial f.              */
                z = z - halley_factor(z, arr, deg);

                /*  Update f_z and increment iters.                           */
                f_z = poly_eval(z, arr, deg);
                ++iters;
            }

            if (cabs(f_z) < EPS)
            {
                if (n_roots == 0)
                {
                    n_roots += 1;
                    roots[0] = z;
                }
                else
                {
                    min = cabs(z - roots[0]);
                    for (ell = 1U; ell < n_roots; ++ell)
                    {
                        temp = cabs(z - roots[ell]);
                        if (temp < min)
                            min = temp;
                    }
                    if (min >= toler)
                    {
                        roots[n_roots] = z;
                        n_roots += 1;
                    }
                }
            }
        }
    }

    if (n_roots == 0)
    {
        puts("Failed to find the roots. Aborting.");
        return -1;
    }

    printf("Number of roots: %d\n", n_roots);
    for (n = 0U; n < n_roots; ++n)
        printf("\troot %d: %f + i%f\n", n, creal(roots[n]), cimag(roots[n]));

    fprintf(fp, "P6\n%d %d\n255\n", width, height);

    for (y = 0U; y < height; ++y)
    {
        z_y = y_max - (double)y * factor_y;

        for (x = 0U; x < width; ++x)
        {
            z_x = x_min + (double)x * factor_x;
            z = z_x + (complex double)_Complex_I*z_y;
            f_z = poly_eval(z, arr, deg);
            iters = 0x00U;

            /*  Allow MaxIters number of iterations of Newton-Raphson.        */
            while ((cabs(f_z) > EPS) && (iters < MaxIters))
            {
                /*  Perfrom Halley's Method on the polynomial f.              */
                z = z - halley_factor(z, arr, deg);

                /*  Update f_z and increment iters.                           */
                f_z = poly_eval(z, arr, deg);
                ++iters;
            }

            /*  Find which roots the final iteration is closest too.          */
            min = cabs(z-roots[0]);
            ind = 0;

            for (n=1; n<n_roots; ++n)
            {
                temp = cabs(z - roots[n]);
                if (temp < min)
                {
                    min = temp;
                    ind = n;
                }
            }

            if (min > 0.1)
                current_color = black;
            else
            {
                scale = 1.0 - factor*(double)iters;
                current_color = scale_color(colors[ind], scale);
            }
            write_color(fp, current_color);
        }
    }
    return 0;
}

