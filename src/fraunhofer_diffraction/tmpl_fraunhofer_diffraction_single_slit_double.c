/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of rss_ringoccs.                                        *
 *                                                                            *
 *  rss_ringoccs is free software: you can redistribute it and/or modify it   *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  rss_ringoccs is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with rss_ringoccs.  If not, see <https://www.gnu.org/licenses/>.    *
 ******************************************************************************
 *              rss_ringoccs_one_slit_fraunhofer_diffraction                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the Fraunhofer diffraction modeling of   *
 *      a single slit.                                                        *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) rss_ringoccs_math.h:                                                  *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       November 27, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/27 (Ryan Maguire):                                                *
 *      Frozen for v1.3.                                                      *
 ******************************************************************************/

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  The Fresnel integrals are found here.                                     */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Header file containing the prototypes for the functions.                  */
#include <libtmpl/include/tmpl_fraunhofer_diffraction.h>

double
tmpl_Double_Fraunhofer_Diffraction_Single_Slit(double x, double z, double a)
{
    double result;

    /*  If z is zero we'll return 0.0. Sinc(x) tends to zero for both         *
     *  x -> +infinity and x -> -infinity.                                    */
    if (z == 0.0)
        return 0.0;

    /*  Single slit is computed in terms of the sinc function.                */
    result = tmpl_Double_Sinc(a*x/z);
    return result*result;
}
