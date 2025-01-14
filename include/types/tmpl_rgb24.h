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
 *                                 tmpl_rgb24                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a typedef for a 24-bit RGB color struct.                     *
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
#ifndef TMPL_TYPES_RGB24_H
#define TMPL_TYPES_RGB24_H

/*  Standard color struct for 24-bit colors using three color channels.       */
typedef struct tmpl_RGB24_Def {

    /*  Unsigned is required to be at least 8 bits by the standard. It is     *
     *  usually 8 bits exactly on nearly every computer imaginable. Use an    *
     *  array with three unsigned chars representing "red", "green", and      *
     *  "blue", in that order. The array ensures that the data is contiguous. */
    unsigned char dat[3];
} tmpl_RGB24;

#endif
/*  End of include guard.                                                     */
