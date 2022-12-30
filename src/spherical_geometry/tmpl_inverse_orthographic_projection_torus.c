#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_vec2.h>
#include <libtmpl/include/tmpl_vec3.h>
#include <libtmpl/include/tmpl_spherical_geometry.h>

tmpl_ThreeVector
tmpl_Inverse_Orthographic_Projection_Torus(tmpl_TwoVector P, double r, double R)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    double x, y, z, threshold;

    /*  Extract the X and Y components from the point P.                      */
    x = P.dat[0];
    y = P.dat[1];

    threshold = tmpl_Double_Sqrt(x*x + y*y) - R;
    threshold = r*r - threshold*threshold;

    if (threshold < 0.0)
        return tmpl_3DDouble_Rect(TMPL_NAN, TMPL_NAN, TMPL_NAN);

    z = tmpl_Double_Sqrt(threshold);
    return tmpl_3DDouble_Rect(x, y, z);
}
