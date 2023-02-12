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
 *                       tmpl_sparse_polynomial_integer                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide data types for sparse polynomials with integer coefficients.  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) stdio.h:                                                              *
 *          Standard C header file containing the FILE data type.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 10, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/02/01: Ryan Maguire                                                  *
 *      Getting rid of -Wreserved-identifier warnings with clang.             *
 *  2022/02/15: Ryan Maguire                                                  *
 *      Changing overall layout of polynomials.                               *
 *  2023/02/01: Ryan Maguire                                                  *
 *      Moved integer data type to own file. Added more data types (int etc.).*
 *  2023/02/10: Ryan Maguire                                                  *
 *      Moved sparse polynomials here from regular polynomials.               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SPARSE_POLYNOMIAL_INTEGER_H
#define TMPL_SPARSE_POLYNOMIAL_INTEGER_H

/*  If using with C++ (and not C) we need to wrap the entire header file in   *
 *  an extern "C" statement. Check if C++ is being used with __cplusplus.     */
#ifdef __cplusplus
extern "C" {
#endif

/*  Macro indicating whether libtmpl has long long support found here.        */
#include <libtmpl/include/tmpl_inttype.h>

/*  Booleans located here.                                                    */
#include <libtmpl/include/tmpl_bool.h>

/*  The size_t data type is found here.                                       */
#include <stddef.h>

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  Data type for working with elements of Z[x] that are of a high degree     *
 *  where most of the coefficients are zero. This method saves on memory.     */
typedef struct tmpl_SparseIntPolynomial_Def {

    /*  A pointer to all of the terms. The degree of the terms is stored in   *
     *  the next pointer.                                                     */
    signed long int *terms;

    /*  A pointer for the degrees of all of the terms.                        */
    size_t *degree_of_term;

    /*  The number of non-zero terms.                                         */
    size_t number_of_terms;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_SparseIntPolynomial;

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
