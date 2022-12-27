/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Absolute value function found here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing the L-Infinity norm of a 3D vector.                */
long double tmpl_3DLDouble_LInf_Norm(tmpl_ThreeVectorLongDouble P)
{
    const long double absx = tmpl_LDouble_Abs(P.dat[0]);
    const long double absy = tmpl_LDouble_Abs(P.dat[1]);
    const long double absz = tmpl_LDouble_Abs(P.dat[2]);

    if (absx < absy)
    {
        if (absy < absz)
            return absz;
        else
            return absy;
    }
    else
    {
        if (absx < absz)
            return absz;
        else
            return absx;
    }
}
/*  End of tmpl_3DLDouble_LInf_Norm.                                          */
