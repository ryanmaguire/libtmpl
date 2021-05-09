/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                              tmpl_infinity                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide a portable means of representing positive infinity.           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *      Header file where all of these constants are declared.                *
 *  2.) math.h                                                                *
 *      Location of the HUGE_VAL macro.                                       *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 7, 2021                                                   *
 ******************************************************************************/

#include <math.h>

const double tmpl_Infinity = HUGE_VAL;

#ifdef HUGE_VALF
const float tmpl_Infinity_F = HUGE_VALF;
#else
const float tmpl_Infinity_F = (float)HUGE_VAL;
#endif

#ifdef HUGE_VALL
const long double tmpl_Infinity_L = HUGE_VALL;
#else
const long double tmpl_Infinity_L = (long double)HUGE_VAL;
#endif

