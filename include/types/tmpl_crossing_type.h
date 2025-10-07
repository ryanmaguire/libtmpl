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
 *                             tmpl_crossing_type                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a data type for working with crossings in a knot diagram.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 13, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/10/07: Ryan Maguire                                                  *
 *      Moved this typedef to the types directory. Changed from enum type to  *
 *      unsigned char to avoid warnings about using arithmetic with enum.     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_CROSSING_TYPE_H
#define TMPL_TYPES_CROSSING_TYPE_H

/*  Both virtual and classical knot diagrams have a notion of under crossing  *
 *  and over crossing. This is used in both signed and unsigned Gauss codes.  *
 *  We use the smallest unsigned integer data type for this since we only     *
 *  need a single bit. Intermediate Boolean computations may need up to 3     *
 *  bits, but unsigned char is required to be at least 8 bits so this is safe.*/
typedef unsigned char tmpl_CrossingType;

/*  Macros for consistently assigning crossing types to a knot diagram.      */
#define TMPL_UNDER_CROSSING (0x00U)
#define TMPL_OVER_CROSSING (0x01U)

#endif
/*  End of include guard.                                                     */
