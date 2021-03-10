/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of KissVG.                                              *
 *                                                                            *
 *  KissVG is free software: you can redistribute it and/or modify it         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  KissVG is distributed in the hope that it will be useful,                 *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with KissVG.  If not, see <https://www.gnu.org/licenses/>.          *
 ******************************************************************************/

/*  Needed for creating the output file.                                      */
#include <stdio.h>

/*  Malloc is defined here.                                                   */
#include <stdlib.h>
#include <string.h>

/*  Math functions and complex variables provided by libtmpl.                 */
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>

/*  The number of pixels in the x and y axes.                                 */
const unsigned int size = 4U * 1024U;

/*  Allowed error in computation of a root.                                   */
const double root_eps = 1.0e-8;

/*  Smallest distance allowed for two points to be considered the same root.  */
const double root_dist = 1.0e-5;

#define MAX_DEG 11

/*  Maximum number of iterations allowed before giving up on the root finding *
 *  algorithm. If no roots are found, the computation aborts.                 */
const unsigned int root_finder_max_iter = 200U;

/*  Function for setting colors that can be used in a drawing.                */
const unsigned char colors[15][3] = {
    /*  Red (255, 0, 30)           */
    {0xFF, 0x00, 0x1E},

    /*  Green (0, 255, 30)         */
    {0x00, 0xFF, 0x1E},

    /*  Blue (0, 255, 30)          */
    {0x00, 0x1E, 0xFF},

    /*  Yellow (255, 255, 51)      */
    {0xFF, 0xFF, 0x33},

    /*  Light Blue (128, 212, 255} */
    {0x80, 0xD4, 0xFF},

    /*  Magenta. (255, 29, 206)    */
    {0xFF, 0x1D, 0xCE},

    /*  Teal (0, 128, 128)         */
    {0x00, 0x80, 0x80},

    /*  Purple (255, 0, 255)        */
    {0xFF, 0x00, 0xFF},

    /*  Orange (255, 85, 0)         */
    {0xFF, 0x55, 0x00},

    /*  Turquoise (77, 255, 195)    */
    {0x4D, 0xFF, 0xC3},

    /*  Pine (0, 128, 106)          */
    {0x00, 0x80, 0x6A},

    /*  Melon (255, 191, 179)       */
    {0x00, 0xBF, 0xB3},

    /*  Mauve (255, 179, 230)       */
    {0xFF, 0xB3, 0xE6},

    /*  Midnight Blue (102, 51, 102)*/
    {0x66, 0x33, 0x66},

    /*  Black (0, 0, 0)             */
    {0x00, 0x00, 0x00}
};

/*  We'll need the following data types for planar and spherical points.      */
typedef struct root_struct {
    tmpl_ComplexDouble *roots;
    unsigned int n_roots;
} root_struct;

static root_struct *get_roots(double coeffs[MAX_DEG], unsigned int deg)
{
    root_struct *out;
    tmpl_ComplexDouble root, f, f_prime, quotient;
    unsigned int m, n, ell, iter, s, N, n_roots;
    double r, theta, factor_1, factor_2, temp, min;
    char *poly_str = malloc(80);

    out = malloc(sizeof(*out));
    out->roots = malloc(sizeof(*(out->roots)) * deg);

    s = (unsigned int)ceil(0.26632*log(deg));
    N = (unsigned int)ceil(8.32547*deg*log(deg));
    n_roots = 0U;

    factor_1 = 1.0 + tmpl_Sqrt_Two;
    factor_2 = (deg - 1.0) / deg;

    for (m = 0U; m < s; ++m)
    {
        if (n_roots >= deg)
            break;

        r = factor_1*pow(factor_2, (2.0*m+1.0) / (4.0*s));

        for (n=0U; n<N; ++n)
        {
            if (n_roots >= deg)
                break;

            theta = tmpl_Two_Pi*(double)n / (double)N;
            root = tmpl_CDouble_Polar(r, theta);

            f = tmpl_CDouble_Poly_Real_Coeffs(coeffs, deg, root);
            f_prime = tmpl_CDouble_Poly_Deriv_Real_Coeffs(coeffs, deg, 1, root);

            for (iter = 0U; iter < root_finder_max_iter; ++iter)
            {
                if (tmpl_CDouble_Abs(f) < root_eps)
                    break;

                quotient = tmpl_CDouble_Divide(f, f_prime);
                root     = tmpl_CDouble_Subtract(root, quotient);
                f        = tmpl_CDouble_Poly_Real_Coeffs(coeffs, deg, root);
                f_prime  = tmpl_CDouble_Poly_Deriv_Real_Coeffs(coeffs, deg,
                                                               1, root);
            }

            if (tmpl_CDouble_Abs(f) <= root_eps)
            {
                if (n_roots == 0)
                {
                    n_roots += 1;
                    out->roots[0] = root;
                }
                else
                {
                    min = tmpl_CDouble_Dist(root, out->roots[0]);
                    for (ell = 1U; ell < n_roots; ++ell)
                    {
                        temp = tmpl_CDouble_Dist(root, out->roots[ell]);
                        if (temp < min)
                            min = temp;
                    }
                    if (min >= root_dist)
                    {
                        out->roots[n_roots] = root;
                        n_roots += 1;
                    }
                }
            }
        }
    }

    if (n_roots == 0)
    {
        puts("\nError:");
        puts("\tFailed to find the roots. Aborting.\n");
        exit(0);
    }
    else
        out->n_roots = n_roots;

    for (n = 0; n < deg; ++n)
    {
        if (coeffs[n] == 0)
            continue;

        if (n == 0)
            sprintf(&poly_str[strlen(poly_str)], "%.1f + ", coeffs[n]);
        else
            sprintf(&poly_str[strlen(poly_str)], "%.1fz^%u + ", coeffs[n], n);
    }
    sprintf(&poly_str[strlen(poly_str)], "%.1fz^%u", coeffs[n], n);

    puts(poly_str);
    free(poly_str);

    for (n = 0; n < n_roots; ++n)
        printf("Root %u: %f + i%f\n", n,
               tmpl_CDouble_Real_Part(out->roots[n]),
               tmpl_CDouble_Imag_Part(out->roots[n]));
    return out;
}

static void color_pixels(FILE *fp, const unsigned char rgb[3])
{
    fputc(rgb[0], fp);
    fputc(rgb[1], fp);
    fputc(rgb[2], fp);
}

int main(void)
{
    /*  Declare a variable for the output file and give it write permission.  */
    FILE **fp = malloc(sizeof(*fp) * 4);

    /* Dummy variables to loop over.                                          */
    unsigned int iters, ind, n, m;

    /*  Maximum number of iterations for the Newton-Raphson method. This must *
     *  less than 255, otherwise we'll run out of colors.                     */
    const unsigned char MaxIters[4] = {0x20, 0x30, 0x40, 0x80};

    /*  Factor for giving the image a gradient.                               */
    const unsigned char factors[4] = {0x07, 0x05, 0x03, 0x01};
    const unsigned int degs[4] = {3U, 4U, 8U, 10U};
    double coeffs[4][11] = {

        /*  z^3 - 1  */
        {-1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},

        /*  z^4 - 1  */
        {-1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},

        /*  z^8 - 1  */
        {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0},

        /*  z^10 - 1 */
        {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}
    };

    /*  Struct for the roots.                                                 */
    root_struct **roots;

    /*  Values for the min and max of the x and y axes.                       */
    const double x_min = -1.0;
    const double x_max =  1.0;
    const double y_min = -1.0;
    const double y_max =  1.0;

    /*  More dummy variables to loop over.                                    */
    unsigned int x, y;
    double z_x, z_y, min, temp, scale;
    tmpl_ComplexDouble z, w, f, f_prime, quotient;

    /*  Colors for the roots (Red, Green, Blue).                              */
    unsigned char brightness[3];

    roots = malloc(sizeof(*roots) * 4);
    roots[0] = get_roots(coeffs[0], degs[0]);
    roots[1] = get_roots(coeffs[1], degs[1]);
    roots[2] = get_roots(coeffs[2], degs[2]);
    roots[3] = get_roots(coeffs[3], degs[3]);

    /*  Open the files and give them write permission.s                       */
    fp[0] = fopen("newton_fractal_cubic.ppm", "w");
    fp[1] = fopen("newton_fractal_quartic.ppm", "w");
    fp[2] = fopen("newton_fractal_octic.ppm", "w");
    fp[3] = fopen("newton_fractal_decic.ppm", "w");

    /*  Add the preambles to the .ppm files.                                  */
    fprintf(fp[0], "P6\n%d %d\n255\n", size, size);
    fprintf(fp[1], "P6\n%d %d\n255\n", size, size);
    fprintf(fp[2], "P6\n%d %d\n255\n", size, size);
    fprintf(fp[3], "P6\n%d %d\n255\n", size, size);

    for (y=0; y<size; ++y)
    {
        z_y = y * (y_max - y_min)/(size - 1) + y_min;
        z_y = -z_y;

        for (x=0; x<size; ++x)
        {
            z_x = x * (x_max - x_min)/(size - 1) + x_min;

            /*  Allow MaxIters number of iterations of Newton-Raphson.        */
            for (n=0; n<4; ++n)
            {
                z = tmpl_CDouble_Rect(z_x, z_y);
                for (iters=0; iters<MaxIters[n]; ++iters)
                {
                    /*  Perfrom Newton-Raphson on the polynomial f.           */
                    f = tmpl_CDouble_Poly_Real_Coeffs(coeffs[n], degs[n], z);
                    f_prime = tmpl_CDouble_Poly_Deriv_Real_Coeffs(coeffs[n],
                                                                  degs[n],
                                                                  1U, z);
                    quotient = tmpl_CDouble_Divide(f, f_prime);
                    w = tmpl_CDouble_Subtract(z, quotient);

                    /*  Checks for convergence.                               */
                    if (tmpl_CDouble_Dist(w, z) < root_eps)
                        break;

                    z = w;
                }

                /*  Find which roots the final iteration is closest too.      */
                min = tmpl_CDouble_Dist(w, (roots[n])->roots[0]);
                ind = 0;

                for (m=1; m<(roots[n])->n_roots; ++m)
                {
                    temp = tmpl_CDouble_Dist(w, (roots[n])->roots[m]);
                    if (temp < min)
                    {
                        min = temp;
                        ind = m;
                    }
                }
                if (min >= root_dist)
                    color_pixels(fp[n], colors[15]);
                else
                {
                    scale = (255.0-factors[n]*iters)/255.0;
                    for (m=0; m<3; ++m)
                        brightness[m] = (unsigned char)(scale * colors[ind][m]);

                    /*  Color the current pixel.                              */
                    color_pixels(fp[n], brightness);
                }
            }
        }
    }

    for (n=0; n<4; ++n)
    {
        fclose(fp[n]);
        free((roots[n])->roots);
        free(roots[n]);
    }

    free(roots);
    free(fp);
    return 0;
}
