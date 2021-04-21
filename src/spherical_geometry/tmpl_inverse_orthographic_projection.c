#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>
#include <libtmpl/include/tmpl_spherical_geometry.h>

tmpl_ThreeVector
tmpl_Inverse_Orthographic_Projection(tmpl_TwoVector P, tmpl_ThreeVector u)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    double x, y, z, radius;
    tmpl_ThreeVector out, X, Y, u_hat;

    /*  Extract the X and Y components from the point P.                      */
    x = tmpl_TwoVector_X(P);
    y = tmpl_TwoVector_Y(P);

    /*  The radius of the sphere we'll be computing with is just the norm     *
     *  of the input ThreeVector u, so compute this.                          */
    radius = tmpl_ThreeVector_Euclidean_Norm(u);

    /*  If the norm of P is greater than the radius the inverse stereographic *
     *  projection is undefined. We'll return Not-a-Number in this case.      */
    if ((x*x + y*y) > radius)
    {
        out = tmpl_ThreeVector_Rect(tmpl_NaN, tmpl_NaN, tmpl_NaN);
    }
    else
    {
        /*  Normalize the input u vector so that it lies on the sphere.       */
        u_hat = tmpl_ThreeVector_Normalize(u);

        /*  Get a vector orthogonal to u and normalize it.                    */
        X = tmpl_Orthogonal_ThreeVector(u);
        X = tmpl_ThreeVector_Normalize(X);

        /*  Compute the cross product of X and u, giving as an orthonormal    *
         *  basis of three dimensional space: (X, Y, u_hat).                  */
        Y = tmpl_Cross_Product(X, u_hat);

        /*  The z component of our sphere is chosen so that x^2+y^2+z^2=r^2   *
         *  and so that it is positive.                                       */
        z = tmpl_Double_Sqrt(radius*radius - x*x - y*y);

        /*  The point on the sphere now satisfies x*X + y*Y + z*u_hat. We     *
         *  compute this and return.                                          */
        out = tmpl_ThreeVector_Add(
            tmpl_ThreeVector_Add(
                tmpl_ThreeVector_Scale(x, X),
                tmpl_ThreeVector_Scale(y, Y)
            ),
            tmpl_ThreeVector_Scale(z, u_hat)
        );
    }

    return out;
}
