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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 8, 2023                                              *
 ******************************************************************************/

/*  TODO: Add "doc-string" above, description of function, etc.               */

/*  realloc found here.                                                       */
#include <stdlib.h>

/*  Boolean given here.                                                       */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup function provided here.                                       */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for multiplying two polynomials.                                 */
void
tmpl_IntPolynomial_Add(const tmpl_IntPolynomial *P,
                       const tmpl_IntPolynomial *Q,
                       tmpl_IntPolynomial *sum)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    const tmpl_IntPolynomial *first, *second;

    /*  If the output pointer is NULL there's nothing to be done.             */
    if (!sum)
        return;

    /*  If an error occurred before this function was called, abort.          */
    if (sum->error_occurred)
        return;

    /*  If either P or Q are NULL, set an error and return.                   */
    if (!P || !Q)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Add\n\n"
            "Input polynomial is NULL. Aborting.\n\n"
        );
        return;
    }

    /*  Similarly if either P or Q have an error.                             */
    if (P->error_occurred || Q->error_occurred)
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Add\n\n"
            "Input polynomial has error_occurred set to true. Aborting.\n\n"
        );
        return;
    }

    /*  Get the polynomial with the larger degree and set to "first".         */
    if (P->degree < Q->degree)
    {
        first = Q;
        second = P;
    }
    else
    {
        first = P;
        second = Q;
    }

    /*  Check if sum needs to be resized.                                     */
    if (sum->degree != first->degree)
    {
        /*  reallocate memory for the sum pointer and copy first to it.       */
        const size_t len = first->degree + (size_t)1;
        void *tmp = realloc(sum->coeffs, sizeof(*sum->coeffs)*len);

        /*  Check if realloc failed.                                          */
        if (!tmp)
        {
            sum->error_occurred = tmpl_True;
            sum->error_message = tmpl_strdup(
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_Add\n\n"
                "realloc failed. Aborting.\n\n"
            );

            return;
        }
        else
        {
            sum->coeffs = tmp;
            sum->degree = first->degree;
        }
    }

    /*  Compute the sum term by term.                                         */
    for (n = (size_t)0; n <= second->degree; ++n)
        sum->coeffs[n] = first->coeffs[n] + second->coeffs[n];

    /*  Add the coefficients of the smaller polynomial.                       */
    for (n = second->degree + (size_t)1; n <= first->degree; ++n)
        sum->coeffs[n] = first->coeffs[n];

    tmpl_IntPolynomial_Shrink(sum);
}
/*  End of tmpl_IntPolynomial_Add.                                            */
