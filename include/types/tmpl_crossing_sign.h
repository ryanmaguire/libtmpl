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
 *                             tmpl_crossing_sign                             *
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
#ifndef TMPL_TYPES_CROSSING_SIGN_H
#define TMPL_TYPES_CROSSING_SIGN_H

/*  Oriented knot diagrams have a notion of sign for a crossing. For one      *
 *  component knots this is independent of the choice of orientation, but for *
 *  multi-component links this is indeed senstive to the chosen orientation.  *
 *  libtmpl adopts the following convention for crossing signs:               *
 *                                                                            *
 *       3          2         3          2                                    *
 *      \  \      /  /       \  \      /  /                                   *
 *       \  \    /  /         \  \    /  /                                    *
 *        \  \  /  /           \  \  /  /                                     *
 *         \  \/  /             \  \/  /                                      *
 *          \  \ /               \ /  /                                       *
 *           \  \     -           /  /     +                                  *
 *          / \  \               /  / \                                       *
 *         /  /\  \             /  /\  \                                      *
 *        /  /  \  \           /  /  \  \                                     *
 *       /  /    \  \         /  /    \  \                                    *
 *      /  /      \  \       /  /      \  \                                   *
 *       0          1         0          1                                    *
 *                                                                            *
 *  where the numbers are used to indicate the orientation. The arrows point  *
 *  in the direction of increasing labels. The "-" sign indicates a negative  *
 *  crossing, and the "+" denotes a positive one.                             */
typedef unsigned char tmpl_CrossingSign;

/*  Macros for consistently assigning crossing signs to a knot diagram.       */
#define TMPL_NEGATIVE_CROSSING (0x00U)
#define TMPL_POSITIVE_CROSSING (0x01U)

#endif
/*  End of include guard.                                                     */
