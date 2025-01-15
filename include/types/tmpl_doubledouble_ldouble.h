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
 *                          tmpl_doubledouble_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a long double precision double-double data type.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 24, 2024                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/01/13: Ryan Maguire                                                  *
 *      Moved this typedef to the types directory.                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_DOUBLEDOUBLE_LDOUBLE_H
#define TMPL_DOUBLEDOUBLE_LDOUBLE_H

/*  Long double precision double-double data type for extended precision.     */
typedef struct tmpl_LongDoubleDouble_Def {

    /*  We mimic other types (like complex numbers or 2-vectors) and use an   *
     *  array of two long doubles. This ensures the data is contiguous.       */
    long double dat[2];
} tmpl_LongDoubleDouble;

#endif
/*  End of include guard.                                                     */
