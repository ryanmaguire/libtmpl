#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_vec2.h>
#include <libtmpl/include/tmpl_vec3.h>
#include <libtmpl/include/tmpl_spherical_geometry.h>

tmpl_TwoVector
tmpl_Stereographic_Projection_Torus(double u, double v, double r, double R)
{
    double cos_u, sin_u, cos_v, sin_v, t, x, y, Px, Py, Qx, Qy;

    sin_u = tmpl_Double_Sin(u);

    if (sin_u == 1.0)
    {
        x = TMPL_INFINITY;
        y = TMPL_INFINITY;
    }
    else
    {
        t = 1.0 / (1.0-sin_u);
        cos_u = tmpl_Double_Cos(u);
        cos_v = tmpl_Double_Cos(v);
        sin_v = tmpl_Double_Sin(v);

        Qx = R*cos_v;
        Qy = R*sin_v;

        Px = cos_v*(R + r*cos_u);
        Py = sin_v*(R + r*cos_u);

        x = t*Px + (1.0 - t)*Qx;
        y = t*Py + (1.0 - t)*Qy;
    }

    return tmpl_2DDouble_Rect(x, y);
}
