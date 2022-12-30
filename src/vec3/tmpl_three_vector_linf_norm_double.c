/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Absolute value function found here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing the L-Infinity norm of a 3D vector.                */
double tmpl_3DDouble_LInf_Norm(tmpl_ThreeVectorDouble P)
{
    const double absx = tmpl_Double_Abs(P.dat[0]);
    const double absy = tmpl_Double_Abs(P.dat[1]);
    const double absz = tmpl_Double_Abs(P.dat[2]);

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
/*  End of tmpl_3DDouble_LInf_Norm.                                           */
