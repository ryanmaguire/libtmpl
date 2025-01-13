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
 *                          tmpl_complex_path_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the function type double -> complex double.                  *
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
#ifndef TMPL_TYPES_COMPLEX_PATH_DOUBLE_H
#define TMPL_TYPES_COMPLEX_PATH_DOUBLE_H

/*  Double precision complex numbers provided here.                           */
#include "tmpl_complex_double.h"

/*  Function pointer for double precision complex paths.                      */
typedef tmpl_ComplexDouble (*tmpl_ComplexDoublePath)(double);

#endif
/*  End of include guard.                                                     */
