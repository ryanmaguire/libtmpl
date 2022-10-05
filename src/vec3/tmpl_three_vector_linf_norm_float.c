/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Absolute value function found here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing the L-Infinity norm of a 3D vector.                */
float tmpl_3DFloat_LInf_Norm(tmpl_ThreeVectorFloat P)
{
    const float absx = tmpl_Float_Abs(P.dat[0]);
    const float absy = tmpl_Float_Abs(P.dat[1]);
    const float absz = tmpl_Float_Abs(P.dat[2]);

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
/*  End of tmpl_3DFloat_LInf_Norm.                                            */
