/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                         tmpl_vec3_divide_by_float                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for performing the Hadamard quotient.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_DivideBy                                                 *
 *  Purpose:                                                                  *
 *      Computes the Hadamard quotient of at single precision.                *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorFloat * const):                               *
 *          A pointer to a vector in R^3. The quotient will be stored here.   *
 *      source (const tmpl_ThreeVectorFloat * const):                         *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of Hadamard division. If p = (px, py, pz) and      *
 *      q = (qx, qy, qz), then the quotient has coordinates:                  *
 *                                                                            *
 *          x = px / qx                                                       *
 *          y = py / qy                                                       *
 *          z = pz / qz                                                       *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *                                                                            *
 *      2.) No checks for Null pointers are performed.                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_ALWAYS_INLINE macro.                         *
 *  2.) tmpl_vec3.h:                                                          *
 *          tmpl_ThreeVectorFloat and function prototype provided here.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 13, 2024                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/07/17: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes.          *
 ******************************************************************************/

/*  The TMPL_ALWAYS_INLINE macro is provided here.                            */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef and function prototype found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for performing the Hadamard quotient in R^3.                     */
TMPL_ALWAYS_INLINE
void
tmpl_3DFloat_DivideBy(tmpl_ThreeVectorFloat * const target,
                      const tmpl_ThreeVectorFloat * const source)
{
    /*  The Hadamard quotient is performed component-wise.                    */
    target->dat[0] /= source->dat[0];
    target->dat[1] /= source->dat[1];
    target->dat[2] /= source->dat[2];
}
/*  End of tmpl_3DFloat_DivideBy.                                             */
