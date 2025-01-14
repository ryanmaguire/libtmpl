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
 *                                 tmpl_rgb30                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a typedef for a 30-bit RGB color struct.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/01/13: Ryan Maguire                                                  *
 *      Moved this typedef to its own file.                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_RGB30_H
#define TMPL_TYPES_RGB30_H

/*  Color struct for 30-bit colors. Common in HDR images.                     */
typedef struct tmpl_RGB30_Def {

    /*  Unsigned int is required to be at least 16 bits long. We can create   *
     *  a 30-bit color using a bit field with 3 10-bit integers. Note, the    *
     *  compiler will almost surely pad the struct with two bits to create a  *
     *  single 32-bit object, but that's fine.                                */
    unsigned int red : 10;
    unsigned int green : 10;
    unsigned int blue : 10;
} tmpl_RGB30;

#endif
/*  End of include guard.                                                     */
