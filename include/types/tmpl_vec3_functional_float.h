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
 *                         tmpl_vec3_functional_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the function type float vec3 -> float.                       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 7, 2024                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/04/14: Ryan Maguire                                                  *
 *      Moved this typedef to the types directory.                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_VEC3_FUNCTIONAL_FLOAT_H
#define TMPL_TYPES_VEC3_FUNCTIONAL_FLOAT_H

/*  Single precision 3D vectors provided here.                                */
#include "tmpl_vec3_float.h"

/*  Function pointer for single precision 3D functionals.                     */
typedef float (*tmpl_ThreeVectorFloatFunctional)(tmpl_ThreeVectorFloat);

#endif
/*  End of include guard.                                                     */
