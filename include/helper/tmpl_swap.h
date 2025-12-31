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
 *                                  tmpl_swap                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a helper macro for swapping two variables.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 16, 2025                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_HELPER_SWAP_H
#define TMPL_HELPER_SWAP_H

/*  Swaps two variables, a becomes b, and b becomes a.                        */
#define TMPL_SWAP(type, a, b)                                                  \
    do {                                                                       \
        const type tmpl_swap_tmp = a;                                          \
        a = b;                                                                 \
        b = tmpl_swap_tmp;                                                     \
    } while(0)

#endif
/*  End of include guard.                                                     */
