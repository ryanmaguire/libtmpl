/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                       tmpl_cyl_fresnel_psi_deg_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Cylindrical Fresnel kernel at single precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Cyl_Fresnel_Psi_Deg                                        *
 *  Purpose:                                                                  *
 *      Computes the cylindrical Fresnel kernel at single precision with all  *
 *      angles in degrees. The lengths may be in whatever units, but they     *
 *      must be in the same units.                                            *
 *  Arguments:                                                                *
 *      k (float):                                                            *
 *          The wavenumber, in the reciprocal of the units of r.              *
 *      r (float):                                                            *
 *          The "dummy" radius, usually a variable that is integrated over.   *
 *      r0 (float):                                                           *
 *          The radius of the point of interest.                              *
 *      phi (float):                                                          *
 *          The "dummy" azimuthal angle, often integrated over.               *
 *      phi0 (float):                                                         *
 *          The azimuthal angle of the point of interest.                     *
 *      B (float):                                                            *
 *          The opening angle of the plane. For planetary ring systems this   *
 *          is the ring opening angle of the rings with respect to Earth.     *
 *      D (float):                                                            *
 *          The distance from the observer to the point in the plane.         *
 *  Outputs:                                                                  *
 *      psi (float):                                                          *
 *          The cylindrical Fresnel kernel as a function of the inputs.       *
 *  Called Functions:                                                         *
 *      tmpl_Float_Cosd (tmpl_math.h):                                        *
 *          Computes cosine, in degrees.                                      *
 *      tmpl_Float_Sqrt (tmpl_math.h):                                        *
 *          Computes the square root of a positive number.                    *
 *  Method:                                                                   *
 *      Following Marouf, Tyler, and Rosen (1986), appeal to equations        *
 *      (4a), (4b), and (4c) to compute the Fresnel kernel.                   *
 *  Notes:                                                                    *
 *      Angles must be in degrees. Lengths can be in whatever units, but they *
 *      must be the same units.                                               *
 *  References:                                                               *
 *      1.) Profiling Saturn's Rings, Marouf, Tyler, Rosen 1986, Icarus 68.   *
 *      2.) Introduction to Fourier Optics, Joseph Goodman, 2005.             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with cosine and sqrt.                                 *
 *  2.) tmpl_cyl_fresnel_optics.h:                                            *
 *          Header file where the prototype is given.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 20, 2023                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/03/20: Ryan Maguire                                                  *
 *      Created file, edited from double version.                             *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Function for computing the cylindrical Fresnel kernel.                    */
float
tmpl_Float_Cyl_Fresnel_Psi_Deg(float k, float r, float r0, float phi,
                               float phi0, float B, float D)
{
    /*  Compute 1/D and it's square to save the number of divisions we need   *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const float rcpr_D = 1.0F / D;
    const float rcpr_D_squared = rcpr_D * rcpr_D;

    /*  Precompute cosines and sines to save on computations.                 */
    const float cos_B = tmpl_Float_Cosd(B);
    const float cos_phi = tmpl_Float_Cosd(phi);
    const float cos_phi0 = tmpl_Float_Cosd(phi0);
    const float cos_phi_phi0 = tmpl_Float_Cosd(phi - phi0);

    /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).        */
    const float xi = (cos_B * rcpr_D) * (r * cos_phi - r0 * cos_phi0);
    const float eta = (r0*r0 + r*r - 2.0F*r*r0*cos_phi_phi0) * rcpr_D_squared;

    /* Sign of xi swapped from MTR86.                                         */
    return k * D * (tmpl_Float_Sqrt(1.0F + eta - 2.0F*xi) + xi - 1.0F);
}
/*  End of tmpl_Float_Cyl_Fresnel_Psi_Deg.                                    */
