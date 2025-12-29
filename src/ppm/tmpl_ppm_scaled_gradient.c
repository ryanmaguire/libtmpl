#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_ppm.h>

tmpl_PPM_Color tmpl_PPM_Scaled_Gradient(double val)
{
    /*  Declare variables for the color. We'll compute the color in RGB       *
     *  format, hence the need for these three variables.                     */
    double scaled;

    if (tmpl_Double_Is_NaN(val))
        return tmpl_PPM_Black;

    scaled = tmpl_double_pi_by_two + tmpl_Double_Arctan(val);

    return tmpl_PPM_Linear_Gradient(scaled * tmpl_Double_Rcpr_Pi, 0.0, 1.0);
}
