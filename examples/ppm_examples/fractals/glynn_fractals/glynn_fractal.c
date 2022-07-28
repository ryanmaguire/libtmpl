#include <stdio.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_ppm.h>

static tmpl_ComplexDouble
glynn_func(tmpl_ComplexDouble z, tmpl_ComplexDouble e, tmpl_ComplexDouble mu)
{
    tmpl_ComplexDouble out;


    out = tmpl_CDouble_Pow(z, e);
    out = tmpl_CDouble_Add(out, mu);
    return out;
}

int main(void)
{
    /*  Declare a variable for the output file and give it write permission.  */
    FILE *fp;
    unsigned int x, y, n;
    double z_x, z_y, norm;
    double rcp_factor;
    unsigned int maxIterations = 512;
    tmpl_ComplexDouble z, e, mu;

    const unsigned int size = 1024U;

    const double x_min = 0.065;
    const double x_max = 0.425;
    const double y_min = -0.67;
    const double y_max = -0.31;

    double radius = 4.0;

    e  = tmpl_CDouble_Rect(1.5, 0.0);
    mu = tmpl_CDouble_Rect(-0.2, 0.0);

    fp = fopen("glynn_fractal.ppm", "w");
    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    rcp_factor = 1.0/(size-1.0);

    /*  Loop through each pixel.                                              */
    for (y=0; y<size; ++y)
    {
        /*  We want to center z_y so scale and shift. This makes the output   *
         *  picture lie in the box [x_min, x_max] x [y_min, y_max].           */
        z_y = (y - 1.0) * (y_max - y_min) * rcp_factor + y_min;

        for (x=0; x<size; ++x)
        {
            /*  Similarly, center z_x.                                        */
            z_x = x * (x_max - x_min) * rcp_factor + x_min;

            /*  Compute the complex number z_x + i z_y.                       */
            z = tmpl_CDouble_Rect(z_x, z_y);

            /*  Start the iteration process.                                  */
            for(n = 0; n < maxIterations; ++n)
            {

                /*  Calculate real and imaginary parts.                       */
                z = glynn_func(z, e, mu);

                /*  Check for divergence.                                     */
                norm = tmpl_CDouble_Abs(z);

                if(norm > radius)
                    break;
            }

            tmpl_PPM_Write_Color(fp, tmpl_PPM_Linear_Gradient((double)n, 0, maxIterations-1));
        }
    }
    return 0;
}
