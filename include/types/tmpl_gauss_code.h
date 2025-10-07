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
 *                              tmpl_gauss_code                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a data type for working with knots and virtual knots.        *
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
#ifndef TMPL_TYPES_GAUSS_CODE_H
#define TMPL_TYPES_GAUSS_CODE_H

/*  Booleans provided here, used as an error indicator.                       */
#include <libtmpl/include/tmpl_bool.h>

/*  Gauss tuples, which are the entries for the Gauss code.                   */
#include <libtmpl/include/types/tmpl_gauss_tuple.h>

/*  Struct for Gauss code, which is a finite sequence of Gauss tuples.        */
typedef struct tmpl_GaussCode_Def {

    /*  The length of the Gauss code, which is the number of entries in the   *
     *  sequence. This is twice the number of crossings in the knot diagram.  */
    unsigned long int length;

    /*  The number of crossings in the knot diagram. This is half the length  *
     *  of the tuples array. It is commonly needed so the functions that      *
     *  create a tmpl_GaussCode struct will initialize this member too.       */
    unsigned long int number_of_crossings;

    /*  A pointer to an array of Gauss tuples, representing the Gauss code of *
     *  the knot diagram. This array has "length" number of elements.         */
    tmpl_GaussTuple *gauss_code;

    /*  A string with an error message that can be set if something goes      *
     *  wrong. This is set to NULL by default, meaning no error has occurred. */
    const char *error_message;

    /*  A Boolean indicating if something went wrong in a computation. This   *
     *  should always be checked before using.                                */
    tmpl_Bool error_occurred;
} tmpl_GaussCode;

#endif
/*  End of include guard.                                                     */
