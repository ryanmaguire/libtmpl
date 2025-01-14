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
 *                                 tmpl_rgb48                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a typedef for a 48-bit RGB color struct.                     *
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
#ifndef TMPL_TYPES_RGB48_H
#define TMPL_TYPES_RGB48_H

/*  Color struct for 48-bit colors in RGB format.                             */
typedef struct tmpl_RGB48_Def {

    /*  Unsigned short is required to be at least 16 bits wide. It is usually *
     *  exactly this size on most computers. Use an array of three unsigned   *
     *  shorts to represent the three colors. Using an array makes the data   *
     *  contiguous, which is occasionally useful.                             */
    unsigned short int dat[3];
} tmpl_RGB48;

#endif
/*  End of include guard.                                                     */
