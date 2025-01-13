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
 *                            tmpl_complex_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a double precision complex data type.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 2, 2021                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/01/13: Ryan Maguire                                                  *
 *      Moved this typedef to the types directory.                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_COMPLEX_DOUBLE_H
#define TMPL_TYPES_COMPLEX_DOUBLE_H

/*  The GNU Scientific Library (GSL) v2.6 defines complex variables via a     *
 *  data structure containing a single array double dat[2];. If you are using *
 *  the GSL v2.6, you can use libtmpl functions with that library. That is,   *
 *  if you have a pointer tmpl_ComplexDouble *z; and another pointer          *
 *  gsl_complex *w; you can safely cast via:                                  *
 *      z = (tmpl_ComplexDouble *)w;                                          *
 *  And similarly you can do w = (gsl_complex *)z;                            */
typedef struct tmpl_ComplexDouble_Def {

    /*  The zeroth element is the real part and the first element is the      *
     *  imaginary part. By using an array we ensure the data is contiguous.   */
    double dat[2];
} tmpl_ComplexDouble;

/*  Helper macros for the complex double struct. Real and imaginary parts.    */
#define TMPL_CDOUBLE_REAL_PART(z) ((z).dat[0])
#define TMPL_CDOUBLE_IMAG_PART(z) ((z).dat[1])

/*  Helper macros for a pointer to a complex double struct.                   */
#define TMPL_CDOUBLE_PTR_REAL_PART(z) ((z)->dat[0])
#define TMPL_CDOUBLE_PTR_IMAG_PART(z) ((z)->dat[1])

#endif
/*  End of include guard.                                                     */
