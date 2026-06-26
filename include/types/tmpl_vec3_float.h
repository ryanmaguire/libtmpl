/******************************************************************************
 *                                 LICENSE                                    *
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
 *                             tmpl_vec3_float                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the definition of a 3D vector at single precision.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 6, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_VEC3_FLOAT_H
#define TMPL_TYPES_VEC3_FLOAT_H

#include <libtmpl/include/types/tmpl_ieee754_float.h>

#if TMPL_HAS_IEEE754_FLOAT == 1

#include <libtmpl/include/helper/tmpl_max.h>
#include <libtmpl/include/helper/tmpl_min.h>

/*  3D Vectors with single precision components and their bit fields.         */
typedef union tmpl_ThreeVectorFloat_Type {
    float dat[3];
    tmpl_IEEE754_Float word[3];
} tmpl_ThreeVectorFloat;

#define TMPL_VEC3_FLOAT_MAX_EXP(p)  \
    TMPL_MAX3(                      \
        (p).word[0].bits.expo,      \
        (p).word[1].bits.expo,      \
        (p).word[2].bits.expo       \
    )

#define TMPL_VEC3_FLOAT_PTR_MAX_EXP(p)  \
    TMPL_MAX3(                          \
        (p)->word[0].bits.expo,         \
        (p)->word[1].bits.expo,         \
        (p)->word[2].bits.expo          \
    )

#define TMPL_VEC3_FLOAT_MIN_EXP(p)  \
    TMPL_MIN3(                      \
        (p).word[0].bits.expo,      \
        (p).word[1].bits.expo,      \
        (p).word[2].bits.expo       \
    )

#define TMPL_VEC3_FLOAT_PTR_MIN_EXP(p)  \
    TMPL_MIN3(                          \
        (p)->word[0].bits.expo,         \
        (p)->word[1].bits.expo,         \
        (p)->word[2].bits.expo          \
    )

#else

/*  3D Vectors with single precision components.                              */
typedef struct tmpl_ThreeVectorFloat_Type {
    float dat[3];
} tmpl_ThreeVectorFloat;

#endif

#endif
/*  End of include guard.                                                     */
