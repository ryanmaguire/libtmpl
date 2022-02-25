/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  iunder the terms of the GNU General Public License as published by        *
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
 ******************************************************************************/

/*  Needed for the FILE data type and fprintf function.                       */
#include <stdio.h>

/*  Square root function found here.                                          */
#include <math.h>

/*  A simple structure for dealing with vectors. Vectors are treated as rays  *
 *  of light moving under the influence of the gravity of a black hole.       */
struct tmpl_simple_vector {

    /*  A vector will be defined by it's Euclidean components, x, y, z.       */
    double x, y, z;

    /*  Empty constructor for the tmpl_simple_vector.                         */
    tmpl_simple_vector(void)
    {
        return;
    }

    /*  Simple method for creating a vector. Simply set the x, y, and z parts *
     *  to the values a, b, and c, respectively.                              */
    tmpl_simple_vector(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    /*  This operator represents vector addition.                             */
    tmpl_simple_vector operator + (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x + r.x, y + r.y, z + r.z);
    }

    tmpl_simple_vector operator - (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x - r.x, y - r.y, z - r.z);
    }

    /*  And here we have scalar multiplication.                               */
    tmpl_simple_vector operator * (double r)
    {
        return tmpl_simple_vector(x*r, y*r, z*r);
    }

    /*  This operator will denote the Euclidean dot product of two vectors.   */
    double operator % (tmpl_simple_vector r)
    {
        return x*r.x + y*r.y + z*r.z;
    }

    /*  A method for computing the Euclidean norm of a vector.                */
    double norm(void)
    {
        return sqrt(*this % *this);
    }

    /*  A method for computing the square of the Euclidean norm of a vector.  *
     *  This is computationally useful since it avoids redundant square roots.*/
    double normsq(void)
    {
        return *this % *this;
    }

    tmpl_simple_vector unit_vector(void)
    {
        return *this * (1.0 / (*this).norm());
    }

};
/*  End of definition of tmpl_simple_vector.                                  */

struct tmpl_simple_color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

tmpl_simple_color sky_color(double zenith)
{
    tmpl_simple_color out;
    double factor;
    if (zenith < 0.1745)
    {
        out.red = 255U;
        out.green = 255U;
        out.blue = 0U;
        return out;
    }

    out.blue = 255U;

    factor = cos(zenith);
    out.red = (unsigned char)(factor * 135.0);
    out.green = (unsigned char)(factor * 206.0);
    return out;
}

void color(tmpl_simple_color c, FILE *fp)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}

static const double Inner_Radius = 1.0;
static const double Outer_Radius = 2.0;
static const unsigned int max_iters = 1E5;
static const double threshold = 0.01;

double torus_implicit(tmpl_simple_vector p)
{
    double a = sqrt(p.x*p.x + p.y*p.y) - Outer_Radius;
    return a*a + p.z*p.z - Inner_Radius*Inner_Radius;
}

tmpl_simple_vector torus_gradient(tmpl_simple_vector p)
{
    tmpl_simple_vector out;
    double rho = sqrt(p.x*p.x + p.y*p.y);
    double factor = 2.0*(rho - Outer_Radius) / rho;

    out.x = factor * p.x;
    out.y = factor * p.y;
    out.z = 2*p.z;
    return out;
}

tmpl_simple_color sampler(tmpl_simple_vector p, tmpl_simple_vector v, double dt)
{
    tmpl_simple_color out;
    tmpl_simple_vector grad_p;
    double rho;
    unsigned int iters = 0U;

    while ((iters < max_iters) && (p.z > -Inner_Radius))
    {
        if (fabs(torus_implicit(p)) < threshold)
        {
            grad_p = torus_gradient(p);
            grad_p = grad_p.unit_vector();
            v = v - (grad_p * 2.0*(v % grad_p));
            p = p + v*(4.0*dt);

            out = sampler(p, v, dt);
            out.red   = (unsigned char)(0.5 * out.red);
            out.green = (unsigned char)(0.5 * out.green);
            out.blue  = (unsigned char)(0.5 * out.blue);

            return out;
        }
        else
            p = p + v*dt;

        ++iters;
    }

    if (v.z <= 0.0)
    {
        double t = -(p.z - Inner_Radius) / v.z;
        tmpl_simple_vector intesect = p + v*t;
        if ((int)(ceil(intesect.x) + ceil(intesect.y)) & 1)
        {
            out.red = 255U;
            out.green = 255U;
            out.blue = 255U;
        }
        else
        {
            out.red   = 255U;
            out.green = 0U;
            out.blue  = 0U;
        }
    }
    else
    {
        double rho = sqrt(v.x*v.x + v.y*v.y);
        double zenith = M_PI_2 - atan(v.z / rho);
        out = sky_color(zenith);
    }
    return out;
}

/*  Main function for performing the raytracing.                              */
int main(void)
{
    /*  The vector v represents the initial velocity vector of a particle of  *
     *  light. Since our light rays are being directed downwards, this vector *
     *  should be (0, 0, -c), where c is the speed of light. We can take this *
     *  to be 1 for simplicity. Adjusting this value would be equivalent to   *
     *  adjusting the strength of Gravity. Smaller values mean stronger       *
     *  gravity, and larger values mean weaker gravity.                       */
    tmpl_simple_vector v  = tmpl_simple_vector(0.0, -1.0, -1.0);
    tmpl_simple_vector u1 = tmpl_simple_vector(0.0,  1.0, -1.0);
    tmpl_simple_vector u0 = tmpl_simple_vector(1.0,  0.0,  0.0);
    tmpl_simple_vector p, dir, eye;
    unsigned int x, y, size;
    double factor, start, end;
    eye = v*(-11.);

    u0 = u0 * (1.0 / u0.norm());
    v  = v  * (1.0 / v.norm());

    /*  Set the values for the size of the detector. I've chosen the square   *
     *  [-10, 10]^2.                                                          */
    start = -2.0;
    end   =  2.0;

    /*  Set the number of pixels in the detector.                             */
    size = 2048U;

    /*  And compute the factor that allows us to convert between a pixel      *
     *  and the corresponding point on the detector.                          */
    factor = (end - start) / (double)size;

    /*  Open the file "black.ppm" and give it write permissions.              */
    FILE *fp = fopen("black_hole.ppm", "w");

    /*  If fopen fails it returns NULL. Check that this didn't happen.        */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Print the preamble to the PPM file. A PPM file wants Pn followed by   *
     *  three numbers. P6 means we're encoding an RGB image in binary format. *
     *  The first two numbers are the number of pixels in the x and y axes.   *
     *  The last number is the size of our color spectrum, which is 255.      */
    fprintf(fp, "P6\n%u %u\n255\n", size, size);

    /*  We can NOT do parallel processing with the creation of our PPM file   *
     *  since the order the values are computed is essential.                 */
    for (y = 0U; y<size; ++y)
    {
        for (x = 0U; x<size; ++x)
        {
            /*  We're incrementing p across our detector.                     */
            p = u0*(start + x*factor) + u1*(start + y*factor) - v*10.0;
            dir = p-eye;
            color(sampler(p, dir * (1.0 / dir.norm()), 0.01), fp);
        }
        if ((y % 20) == 0)
            fprintf(stderr, "Progress: %.4f%%\r", 100.0*y / size);
    }

    fclose(fp);
    return 0;
}
/*  End of main.                                                              */

