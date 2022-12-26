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
 ******************************************************************************/

#ifndef TMPL_QUADRUPLE_H
#define TMPL_QUADRUPLE_H

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Use a bit-field to implement 128-bit quadruple precision. Unsigned int is *
 *  required to be at least 16 bits wide, so we can safely and portably       *
 *  create this struct. The IEEE format specify 112 bits for the mantissa, 15 *
 *  bits for the exponent, and 1 bit for the sign.                            */
typedef struct tmpl_Quadruple_Def {
    unsigned int mant1 : 16;
    unsigned int mant2 : 16;
    unsigned int mant3 : 16;
    unsigned int mant4 : 16;
    unsigned int mant5 : 16;
    unsigned int mant6 : 16;
    unsigned int mant7 : 16;
    unsigned int exponent : 15;
    unsigned int sign: 1;
} tmpl_Quadruple;

extern const tmpl_Quadruple tmpl_Quadruple_Inf;
extern const tmpl_Quadruple tmpl_Quadruple_Neg_Inf;
extern const tmpl_Quadruple tmpl_Quadruple_NaN;

TMPL_EXPORT extern tmpl_Bool tmpl_Quaduple_Is_Zero(tmpl_Quadruple x);
TMPL_EXPORT extern tmpl_Bool tmpl_Quadruple_Is_Inf(tmpl_Quadruple x);
TMPL_EXPORT extern tmpl_Bool tmpl_Quadruple_Is_NaN(tmpl_Quadruple x);
TMPL_EXPORT extern tmpl_Bool tmpl_Quadruple_Is_Positive(tmpl_Quadruple x);
TMPL_EXPORT extern tmpl_Bool tmpl_Quadruple_Is_Negative(tmpl_Quadruple x);

TMPL_EXPORT extern tmpl_Quadruple tmpl_Quadruple_Add(tmpl_Quadruple x, tmpl_Quadruple y);
#endif
