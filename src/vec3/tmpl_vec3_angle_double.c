#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_vec3.h>

double
tmpl_3DDouble_Angle(const tmpl_ThreeVectorDouble * const P,
                    const tmpl_ThreeVectorDouble * const Q)
{
    /*  To avoid overflows, or undeflows, normalize the inputs.               */
    const tmpl_ThreeVectorDouble Pn = tmpl_3DDouble_Normalize(P);
    const tmpl_ThreeVectorDouble Qn = tmpl_3DDouble_Normalize(Q);

    /*  From vector geometry, ||PxQ|| = ||P|| ||Q|| sin(theta). Computing     *
     *  the norm of ||PxQ|| gives us a formula for the angle.                 */
    const tmpl_ThreeVectorDouble cross = tmpl_3DDouble_Cross_Product(&Pn, &Qn);
    const double norm_cross = tmpl_3DDouble_L2_Norm(&cross);

    /*  Also from vector geometry, ||P.Q|| = ||P|| ||Q|| cos(theta). By       *
     *  keeping track of the sign, we can get "oriented" angles.              */
    const double dot = tmpl_3DDouble_Dot_Product(&Pn, &Qn);

    /*  tan(theta) is the ratio of ||PxQ|| and P.Q. The angle can be computed *
     *  using the arctan2 function in the plane.                              */
    return tmpl_Double_Arctan2(norm_cross, dot);
}
/*  End of tmpl_3DDouble_Angle.                                               */
