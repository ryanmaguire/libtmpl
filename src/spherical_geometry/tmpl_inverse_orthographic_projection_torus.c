#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>
#include <libtmpl/include/tmpl_spherical_geometry.h>

tmpl_ThreeVector
tmpl_Inverse_Orthographic_Projection_Torus(tmpl_TwoVector P, double r, double R)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    double x, y, z, threshold;
    tmpl_ThreeVector out;

    /*  Extract the X and Y components from the point P.                      */
    x = tmpl_TwoVector_X(P);
    y = tmpl_TwoVector_Y(P);

    threshold = tmpl_Double_Sqrt(x*x + y*y) - R;
    threshold = r*r - threshold*threshold;

    if (threshold < 0.0)
        out = tmpl_ThreeVector_Rect(tmpl_NaN, tmpl_NaN, tmpl_NaN);

    else
    {
        z = tmpl_Double_Sqrt(threshold);
        out = tmpl_ThreeVector_Rect(x, y, z);
    }

    return out;
}
