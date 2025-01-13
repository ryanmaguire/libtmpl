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
 *                            tmpl_complex_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a long double precision complex data type.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 2, 2021                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/01/13: Ryan Maguire                                                  *
 *      Moved this typedef to the type directory.                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_COMPLEX_LDOUBLE_H
#define TMPL_TYPES_COMPLEX_LDOUBLE_H

/*  Long double precision complex number data type.                           */
typedef struct tmpl_ComplexLongDouble_Def {

    /*  The zeroth element is the real part and the first element is the      *
     *  imaginary part. By using an array we ensure the data is contiguous.   */
    long double dat[2];
} tmpl_ComplexLongDouble;

/*  Helper macros for complex long doubles. Real and imaginary parts.         */
#define TMPL_CLDOUBLE_REAL_PART(z) ((z).dat[0])
#define TMPL_CLDOUBLE_IMAG_PART(z) ((z).dat[1])

/*  Helper macros for a pointer to a complex long double struct.              */
#define TMPL_CLDOUBLE_PTR_REAL_PART(z) ((z)->dat[0])
#define TMPL_CLDOUBLE_PTR_IMAG_PART(z) ((z)->dat[1])

#endif
/*  End of include guard.                                                     */
