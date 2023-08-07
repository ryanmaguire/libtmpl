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
 *                          tmpl_empty_intpolynomial                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an empty polynomial with all variables set to NULL or zero.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Empty                                              *
 *  Purpose:                                                                  *
 *      Create an empty polynomial with pointers set to NULL and variables    *
 *      set to their default zero values.                                     *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Outputs:                                                                  *
 *      poly (tmpl_IntPolynomial):                                            *
 *          The empty polynomial.                                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Set all variables to their zero values.                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard library file where NULL is provided.                     *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  3.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 25, 2023                                                *
 ******************************************************************************/

/*  size_t data type and NULL are defined here.                               */
#include <stddef.h>

/*  Booleans declared here.                                                   */
#include <libtmpl/include/tmpl_bool.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for creating an empty polynomial with all variables initialized. */
tmpl_IntPolynomial tmpl_IntPolynomial_Empty(void)
{
    /*  Declare a variable for the output.                                    */
    tmpl_IntPolynomial poly;

    /*  Set the pointers to NULL. Many functions check if the pointers        *
     *  are NULL before trying to free them or access their data. Having them *
     *  initialized to NULL helps prevent double free's and seg faults.       */
    poly.coeffs = NULL;
    poly.error_message = NULL;

    /*  Set the remaining variables to their zero values.                     */
    poly.degree = (size_t)0;
    poly.error_occurred = tmpl_False;
    return poly;
}
/*  End of tmpl_IntPolynomial_Empty.                                          */
