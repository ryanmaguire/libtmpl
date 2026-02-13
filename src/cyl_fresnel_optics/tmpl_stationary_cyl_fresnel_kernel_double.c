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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2025                                                 *
 ******************************************************************************/

/*  The cylindrical Fresnel geometry struct.                                  */
#include <libtmpl/include/types/tmpl_cyl_fresnel_geometry_double.h>

/*  Hypot3 and the absolute value function are provided here.                 */
#include <libtmpl/include/tmpl_math.h>

/*  2D vector functions found here.                                           */
#include <libtmpl/include/tmpl_vec2.h>

/*  Complex functions and data types found here.                              */
#include <libtmpl/include/tmpl_complex.h>

/*  Forward declaration / function prototype.                                 */
#include <libtmpl/include/tmpl_cyl_fresnel_optics.h>

/*  Function for computing the full stationary Fresnel kernel.                */
tmpl_ComplexDouble
tmpl_Double_Stationary_Cyl_Fresnel_Kernel(
    double k,
    const tmpl_CylFresnelGeometryDouble * const geo,
    double eps,
    unsigned int max_iters
)
{
    double weight, psi;

    tmpl_Double_Stationary_Cyl_Fresnel_Phase_And_Weight(
        k, geo, eps, max_iters, &weight, &psi
    );

    /*  The Fresnel kernel is the scale factor times exp(i psi). The          *
     *  stationary phase also contains exp(-i pi / 4), which rotates the      *
     *  result. This is equivalent to multiplying by (1 - i) / sqrt(2).       */
    return tmpl_CDouble_Polar(weight, psi);
}
/*  End of tmpl_Double_Stationary_Cyl_Fresnel_Psi.                            */
