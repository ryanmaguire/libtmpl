#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_vec3.h>

float
tmpl_3DFloat_Angle(const tmpl_ThreeVectorFloat * const P,
                   const tmpl_ThreeVectorFloat * const Q)
{
    /*  To avoid overflows, or undeflows, normalize the inputs.               */
    const tmpl_ThreeVectorFloat Pn = tmpl_3DFloat_Normalize(P);
    const tmpl_ThreeVectorFloat Qn = tmpl_3DFloat_Normalize(Q);

    /*  From vector geometry, ||PxQ|| = ||P|| ||Q|| sin(theta). Computing     *
     *  the norm of ||PxQ|| gives us a formula for the angle.                 */
    const tmpl_ThreeVectorFloat cross = tmpl_3DFloat_Cross_Product(&Pn, &Qn);
    const float norm_cross = tmpl_3DFloat_L2_Norm(&cross);

    /*  Also from vector geometry, ||P.Q|| = ||P|| ||Q|| cos(theta). By       *
     *  keeping track of the sign, we can get "oriented" angles.              */
    const float dot = tmpl_3DFloat_Dot_Product(&Pn, &Qn);

    /*  tan(theta) is the ratio of ||PxQ|| and P.Q. The angle can be computed *
     *  using the arctan2 function in the plane.                              */
    return tmpl_Float_Arctan2(norm_cross, dot);
}
/*  End of tmpl_3DFloat_Angle.                                                */
