#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_vec3.h>

long double
tmpl_3DLDouble_Angle(const tmpl_ThreeVectorLongDouble * const P,
                     const tmpl_ThreeVectorLongDouble * const Q)
{
    /*  To avoid overflows, or undeflows, normalize the inputs.               */
    const tmpl_ThreeVectorLongDouble Pn = tmpl_3DLDouble_Normalize(P);
    const tmpl_ThreeVectorLongDouble Qn = tmpl_3DLDouble_Normalize(Q);

    /*  From vector geometry, ||PxQ|| = ||P|| ||Q|| sin(theta). Computing     *
     *  the norm of ||PxQ|| gives us a formula for the angle.                 */
    const tmpl_ThreeVectorLongDouble
        cross = tmpl_3DLDouble_Cross_Product(&Pn, &Qn);
    const long double norm_cross = tmpl_3DLDouble_L2_Norm(&cross);

    /*  Also from vector geometry, ||P.Q|| = ||P|| ||Q|| cos(theta). By       *
     *  keeping track of the sign, we can get "oriented" angles.              */
    const long double dot = tmpl_3DLDouble_Dot_Product(&Pn, &Qn);

    /*  tan(theta) is the ratio of ||PxQ|| and P.Q. The angle can be computed *
     *  using the arctan2 function in the plane.                              */
    return tmpl_LDouble_Arctan2(norm_cross, dot);
}
/*  End of tmpl_3DLDouble_Angle.                                              */
