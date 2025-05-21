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
 *                   tmpl_ideal_cyl_fresnel_psi_deg_ldouble                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Cylindrical Fresnel kernel at long double precision      *
 *      assuming ideal geometry.                                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Ideal_Cyl_Fresnel_Psi_Deg                                *
 *  Purpose:                                                                  *
 *      Computes the cylindrical Fresnel kernel at long double precision with *
 *      all angles in degrees. The lengths may be in whatever units, but they *
 *      must be in the same units. It is assumed that the geometry satisfies  *
 *      the description found in the Marouf, Tyler, and Rosen paper. In       *
 *      particular the vector from the ring intercept point to the observer   *
 *      must be perpendicular to the y axis.                                  *
 *  Arguments:                                                                *
 *      k (long double):                                                      *
 *          The wavenumber, in the reciprocal of the units of rho.            *
 *      rho (long double):                                                    *
 *          The "dummy" radius, usually a variable that is integrated over.   *
 *      rho0 (long double):                                                   *
 *          The radius of the point of interest.                              *
 *      phi (long double):                                                    *
 *          The "dummy" azimuthal angle, often integrated over.               *
 *      phi0 (long double):                                                   *
 *          The azimuthal angle of the point of interest.                     *
 *      B (long double):                                                      *
 *          The opening angle of the plane. For planetary ring systems this   *
 *          is the ring opening angle of the rings with respect to Earth.     *
 *      D (long double):                                                      *
 *          The distance from the observer to the point in the plane.         *
 *  Outputs:                                                                  *
 *      psi (long double):                                                    *
 *          The cylindrical Fresnel kernel as a function of the inputs.       *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Cosd:                                                *
 *              Computes cosine, in degrees.                                  *
 *          tmpl_LDouble_Sqrt:                                                *
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
 *          the non-ideal version (tmpl_LDouble_Cyl_Fresnel_Psi).             *
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
long double
tmpl_LDouble_Ideal_Cyl_Fresnel_Psi_Deg(long double k,
                                       long double rho, long double rho0,
                                       long double phi, long double phi0,
                                       long double B, long double D)
{
    /*  Compute 1 / D and its square to save the number of divisions we need  *
     *  to compute. Multiplication is usually ~10 times faster.               */
    const long double rcpr_D = 1.0L / D;
    const long double rcpr_D_squared = rcpr_D * rcpr_D;

    /*  Compute all of the cosines we need for the expressions.               */
    const long double cos_B = tmpl_LDouble_Cosd(B);
    const long double cos_phi = tmpl_LDouble_Cosd(phi);
    const long double cos_phi0 = tmpl_LDouble_Cosd(phi0);
    const long double cos_phi_phi0 = tmpl_LDouble_Cosd(phi - phi0);

    /*  Compute xi variable (MTR86 Equation 4b) and eta (Equation 4c).        */
    const long double xi = cos_B * rcpr_D * (rho * cos_phi - rho0 * cos_phi0);
    const long double eta =
        (rho0*rho0 + rho*rho - 2.0L*rho*rho0*cos_phi_phi0) * rcpr_D_squared;

    /* Sign of xi swapped from MTR86.                                         */
    return k * D * (tmpl_LDouble_Sqrt(1.0L + eta - 2.0L * xi) + xi - 1.0L);
}
/*  End of tmpl_LDouble_Ideal_Cyl_Fresnel_Psi_Deg.                            */
