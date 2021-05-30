#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_ppm.h>

tmpl_PPM_Color tmpl_RGB_Scaled_Gradient(double val)
{
    /*  Declare variables for the color. We'll compute the color in RGB       *
     *  format, hence the need for these three variables.                     */
    double scaled;

    scaled = tmpl_Double_Arctan(val);
    scaled += tmpl_Pi_By_Two;
    scaled = scaled / tmpl_One_Pi;

    return tmpl_RGB_Linear_Gradient(scaled, 0.0, 1.0);
}
