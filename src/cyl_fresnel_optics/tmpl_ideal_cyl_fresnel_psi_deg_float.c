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
 *                    tmpl_ideal_cyl_fresnel_psi_deg_float                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Cylindrical Fresnel kernel at single precision assuming  *
 *      ideal geometry.                                                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Ideal_Cyl_Fresnel_Psi_Deg                                  *
 *  Purpose:                                                                  *
 *      Computes the cylindrical Fresnel kernel at single precision with all  *
 *      angles in degrees. The lengths may be in whatever units, but they     *
 *      must be in the same units. It is assumed that the geometry satisfies  *
 *      the description found in the Marouf, Tyler, and Rosen paper. In       *
 *      particular the vector from the ring intercept point to the observer   *
 *      must be perpendicular to the y axis.                                  *
 *  Arguments:                                                                *
 *      k (float):                                                            *
 *          The wavenumber, in the reciprocal of the units of rho.            *
 *      rho (float):                                                          *
 *          The "dummy" radius, usually a variable that is integrated over.   *
 *      rho0 (float):                                                         *
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
 *      src/math/                                                             *
 *          tmpl_Float_Cosd:                                                  *
 *              Computes cosine, in degrees.                                  *
 *          tmpl_Float_Sqrt:                                                  *
 *              Computes the square root of a positive number.                *
 *  Method:                                                                   *
 *      Following Marouf, Tyler, and Rosen (1986), appeal to equations        *
 *      (4a), (4b), and (4c) to compute the Fresnel kernel. These use the     *
 *      auxiliary parameters xi and eta, given by:                            *
 *                                                                            *
 *          xi = [rho cos(phi) - rho0 cos(phi0)] cos(B) / D                   *
 *          eta = [rho^2 + rho0^2 - 2 rho rho0 cos(phi - phi0)] / D^2         *
 *                                                                            *
 *      With this the Fresnel kernel is given by:                             *
 *                                                                            *
 *          psi = k D [sqrt(1 + eta - 2 xi) + xi - 1]                         *
 *                                                                            *
 *      Note, we define xi to be negative the xi found in the MTR paper.      *
 *  Notes:                                                                    *
 *      1.) Angles must be in degrees.                                        *
 *      2.) Lengths can be in whatever units, but they must be the same units.*
 *      3.) It is also assumed that the vector from the ring intercept point  *
 *          to the observer is perpendicular to the y axis. This is why this  *
 *          function is called "ideal". For real geometry this may be         *
 *          slightly off. For accurate computations in these scenarios, use   *
 *          the non-ideal version (tmpl_Float_Cyl_Fresnel_Psi).               *
 *  References:                                                               *
 *      1.) Marouf, E., Tyler, G., Rosen, P. (June 1986)                      *
 *          Profiling Saturn's Rings by Radio Occultation                     *
 *          Icarus Vol. 68, Pages 120-166.                                    *
 *                                                                            *
 *          This paper describes the theory of diffraction as applied to      *
 *          planetary ring systems. The Fresnel kernel is described here.     *
 *                                                                            *
 *      2.) Goodman, J. (2005)                                                *
 *          Introduction to Fourier Optics                                    *
 *          McGraw-Hill Series in Electrical and Computer Engineering.        *
 *                                                                            *
 *          Covers most of the theory behind diffraction and the application  *
 *          of Fourier analysis to optics. The Fresnel transform is given an  *
 *          in-depth treatise in this book.                                   *
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
 *      Created file. Edited from radian version.                             *
 *  2025/05/20: Ryan Maguire                                                  *
 *      Changed function name to "Ideal" since this assumes the ideal         *
 *      geometry given in the MTR86 paper. The non-ideal function now uses    *
 *      the geometry of an arbitrary coordinate system with z axis            *
 *      perpendicular to the ring plane.                                      *
 ******************************************************************************/

/*  Trig functions and square root found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Function for computing the cylindrical Fresnel kernel.                    */
float
tmpl_Float_Ideal_Cyl_Fresnel_Psi_Deg(float k,
                                     float rho, float rho0,
                                     float phi, float phi0,
                                     float B, float D)
{
    /*  Compute 1 / D and its square to save the number of divisions we need  *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const float rcpr_D = 1.0F / D;
    const float rcpr_D_squared = rcpr_D * rcpr_D;

    /*  Compute all of the cosines we need for the expressions.               */
    const float cos_B = tmpl_Float_Cosd(B);
    const float cos_phi = tmpl_Float_Cosd(phi);
    const float cos_phi0 = tmpl_Float_Cosd(phi0);
    const float cos_phi_phi0 = tmpl_Float_Cosd(phi - phi0);

    /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).        */
    const float xi = cos_B * rcpr_D * (rho * cos_phi - rho0 * cos_phi0);
    const float eta =
        (rho0*rho0 + rho*rho - 2.0F*rho*rho0*cos_phi_phi0) * rcpr_D_squared;

    /* Sign of xi swapped from MTR86.                                         */
    return k * D * (tmpl_Float_Sqrt(1.0F + eta - 2.0F * xi) + xi - 1.0F);
}
/*  End of tmpl_Float_Ideal_Cyl_Fresnel_Psi_Deg.                              */
