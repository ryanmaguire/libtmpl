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
 *                                 tmpl_rgba30                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a typedef for a 30-bit RGBA color struct.                    *
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
#ifndef TMPL_TYPES_RGBA30_H
#define TMPL_TYPES_RGBA30_H

/*  Color struct for 30-bit colors with alpha compositing.                    */
typedef struct tmpl_RGBA30_Def {

    /*  Mimic the tmpl_RGB30 struct, use a bit field for the color channels.  */
    unsigned int red : 10;
    unsigned int green : 10;
    unsigned int blue : 10;

    /*  Real number for alpha compositing (should be between 0 and 1).        */
    double alpha;
} tmpl_RGBA30;

#endif
/*  End of include guard.                                                     */
