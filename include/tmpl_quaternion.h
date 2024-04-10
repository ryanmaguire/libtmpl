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
 *                              tmpl_quaternion                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides routines for working with quaternions.                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 9, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_QUATERNION_H
#define TMPL_QUATERNION_H

/*  If using with C++ (and not C) we need to wrap the entire header file in   *
 *  an extern "C" statement. Check if C++ is being used with __cplusplus.     */
#ifdef __cplusplus
extern "C" {
#endif

/*  Booleans defined here. Needed for the compare routines.                   */
#include <libtmpl/include/tmpl_bool.h>

/*  The macro TMPL_USE_INLINE is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

typedef struct tmpl_QuaternionDouble_Def {
    double dat[4];
} tmpl_QuaternionDouble;

/*  Define single and long double precision equivalents.                      */
typedef struct tmpl_QuaternionFloat_Def {
    float dat[4];
} tmpl_QuaternionFloat;

/*  Long double precision quaternion numbers.                                 */
typedef struct tmpl_QuaternionLongDouble_Def {
    long double dat[4];
} tmpl_QuaternionLongDouble;

/*  For the sake of ease, tmpl_Quaternion is an alternative alias for double  *
 *  precision quaternion. You can use this for cleaner declarations.          */
typedef tmpl_QuaternionDouble tmpl_Quaternion;

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
