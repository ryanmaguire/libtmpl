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
 *                            tmpl_planetary_rings                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides functions for working with planetary rings, particularly the *
 *      rings of Uranus and Saturn.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 20, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_PLANETARY_RINGS_H
#define TMPL_PLANETARY_RINGS_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Effecting_Ring_Opening_Angle                              *
 *  Purpose:                                                                  *
 *      Computes the effective ring opening angle given the azimuth angle of  *
 *      the ring intercept point and the regular opening angle of the rings   *
 *      with respect to the line-of-sight for the observer.                   *
 *  Arguments:                                                                *
 *      opening (const double):                                               *
 *          The ring opening angle, in radians.                               *
 *      azimuth (const double):                                               *
 *          The azimuth angle for the ring intercept point, in radians. This  *
 *          is the angle made by the ring intercept point and the positive x  *
 *          axis, which is assumed to lie in the ring plane.                  *
 *  Outputs:                                                                  *
 *      effective_opening (double):                                           *
 *          The effective ring opening angle.                                 *
 *  Notes:                                                                    *
 *      1.) Float and long double precisions also provided.                   *
 *      2.) All angles are assumed to be in radians.                          *
 *      3.) No checks for NaN or infinity are performed.                      *
 ******************************************************************************/
extern float
tmpl_Float_Effecting_Ring_Opening_Angle(const float opening,
                                        const float azimuth);

extern double
tmpl_Double_Effecting_Ring_Opening_Angle(const double opening,
                                         const double azimuth);

extern long double
tmpl_LDouble_Effecting_Ring_Opening_Angle(const long double opening,
                                          const long double azimuth);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Optical_Depth_Enhancement                                 *
 *  Purpose:                                                                  *
 *      Computes the optical depth enhancement factor for a ring system.      *
 *  Arguments:                                                                *
 *      opening (const double):                                               *
 *          The ring opening angle, in radians.                               *
 *      azimuth (const double):                                               *
 *          The azimuth angle for the ring intercept point, in radians. This  *
 *          is the angle made by the ring intercept point and the positive x  *
 *          axis, which is assumed to lie in the ring plane.                  *
 *  Outputs:                                                                  *
 *      beta (double):                                                        *
 *          The optical depth enhancement factor.                             *
 *  Notes:                                                                    *
 *      1.) Float and long double precisions also provided.                   *
 *      2.) All angles are assumed to be in radians.                          *
 *      3.) No checks for NaN or infinity are performed.                      *
 ******************************************************************************/
extern float
tmpl_Float_Optical_Depth_Enhancement(const float opening,
                                     const float azimuth);

extern double
tmpl_Double_Optical_Depth_Enhancement(const double opening,
                                      const double azimuth);

extern long double
tmpl_LDouble_Optical_Depth_Enhancement(const long double opening,
                                       const long double azimuth);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
