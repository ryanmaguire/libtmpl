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
 *                              tmpl_gauss_tuple                              *
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
 *      Moved this typedef to the types directory.                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_GAUSS_TUPLE_H
#define TMPL_TYPES_GAUSS_TUPLE_H

/*  tmpl_CrossingSign typedef provided here, used to sign the crossings.      */
#include <libtmpl/include/types/tmpl_crossing_sign.h>

/*  tmpl_CrossingType given here, used to represent over and under crossings. */
#include <libtmpl/include/types/tmpl_crossing_type.h>

/*  Extended Gauss code is a finite sequence of ordered triples, which are    *
 *  the "Gauss tuples." These triples are of the form (n, t, s), where n is   *
 *  the crossing number, which is the index for the crossing, t is the type,  *
 *  over or under, and s is the sign, positive or negative.                   */
typedef struct tmpl_GaussTuple_Def {

    /*  The crossing number of the crossing. That is, the index used to label *
     *  the given crossing. Note, we label the crossings in an N crossing     *
     *  knot diagram from 0 to N - 1, and not 1 to N.                         */
    unsigned long int crossing_number;

    /*  The crossing type (over or under) of this crossing.                   */
    tmpl_CrossingType crossing_type;

    /*  And the crossing sign (positive or negative).                         */
    tmpl_CrossingSign crossing_sign;
} tmpl_GaussTuple;

#endif
/*  End of include guard.                                                     */
