#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_ppm.h>

tmpl_PPM_Color tmpl_PPM_Scaled_Color_Wheel(double val)
{
    /*  Declare variables for the color. We'll compute the color in RGB       *
     *  format, hence the need for these three variables.                     */
    double scaled;

    if (tmpl_Double_Is_NaN(val))
        return tmpl_PPM_Black;

    scaled = (tmpl_Pi_By_Two + tmpl_Double_Arctan(val)) / tmpl_One_Pi;

    return tmpl_PPM_Linear_Gradient(scaled, 0.0, 1.0);
}
