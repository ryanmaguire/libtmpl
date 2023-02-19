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

/*  realloc and free functions are declared here.                             */
#include <stdlib.h>

/*  TMPL_USE_MEMCPY macro is here.                                            */
#include <libtmpl/include/tmpl_config.h>

/*  tmpl_strdup function found here.                                          */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototypes given here.                   */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  On some computers memcpy may be faster than copying the data with a       *
 *  for-loop. On the devices I've tested the for-loop is slightly faster,     *
 *  however. To use memcpy build libtmpl with USE_MEMCPY=1 set.               */
#if TMPL_USE_MEMCPY == 1
#include <string.h>
#endif

/*  Function for copying the coefficients of one polynomial to another.       */
void
tmpl_IntPolynomial_Copy(tmpl_IntPolynomial *dest,
                        const tmpl_IntPolynomial *src)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t len;

    /*  If we're not using memcpy, we need another variable to index the loop.*/
#if TMPL_USE_MEMCPY != 1
    size_t n;
#endif

    /*  If the destination pointer is NULL, there's nothing to be done.       */
    if (!dest)
        return;

    /*  Similarly if the error_occurred Boolean is true. Return to caller.    */
    if (dest->error_occurred)
        return;

    /*  If src and dest are the same pointer, abort. Nothing to copy.         */
    if (dest == src)
        return;

    /*  If the src pointer is NULL there is nothing to copy. This should be   *
     *  considered an error (the user shouldn't pass a NULL pointer here).    */
    if (!src)
    {
        /*  Set the error_occurred Boolean and add an error message.          */
        dest->error_occurred = tmpl_True;
        dest->error_message = tmpl_strdup(
            "\nError Encountered: libtmpl\n"
            "    tmpl_IntPolynomial_Copy\n\n"
            "src pointer is NULL. Aborting.\n\n"
        );
        return;
    }

    /*  If the src pointer is flawed in some manner, consider this an error   *
     *  too. Check the error_occurred Boolean for this.                       */
    if (src->error_occurred)
    {
        /*  As above, set the error_occurred Boolean and add an error message.*/
        dest->error_occurred = tmpl_True;
        dest->error_message = tmpl_strdup(
            "\nError Encountered: libtmpl\n"
            "    tmpl_IntPolynomial_Copy\n\n"
            "src pointer has error_occurred set to True. Aborting.\n\n"
        );
        return;
    }

    /*  If the src coefficients are NULL, this is the empty polynomial. Set   *
     *  the dest polynomial to be empty as well.                              */
    if (!src->coeffs)
    {
        /*  To avoid memory leaks, check to see if dest already has           *
         *  coefficients. If it does, free them.                              */
        if (dest->coeffs)
            free(dest->coeffs);

        /*  Set the coefficients to NULL and the degree to zero, then return. */
        dest->coeffs = NULL;
        dest->degree = (size_t)0;
        return;
    }

    /*  Otherwise we will be copying degree + 1 elements from src to dest     *
     *  where degree is the degree of the src polynomial.                     */
    len = src->degree + (size_t)1;

    /*  Check if we need to reallocate the memory for the dest coefficients.  */
    if (dest->degree != src->degree)
    {
        /*  Use realloc to resize the memory for the coefficients array.      */
        void *tmp;
        tmp = realloc(dest->coeffs, len);

        /*  If realloc succeeded, set the dest coefficients to the new memory.*
         *  Also reset the degree variable to the new size.                   */
        if (tmp)
        {
            dest->coeffs = tmp;
            dest->degree = src->degree;
        }

        /*  Otherwise abort with an error message.                            */
        else
        {
            dest->error_occurred = tmpl_False;
            dest->error_message = tmpl_strdup(
                "\nError Encountered: libtmpl\n"
                "    tmpl_IntPolynomial_Copy\n\n"
                "Realloc failed to resize dest->coeffs. Aborting.\n\n"
            );
            return;
        }
    }

    /*  If the user requested memcpy, use this to copy the data.              */
#if TMPL_USE_MEMCPY == 1

    /*  memcpy syntax is (void *dest, const void *src, size_t num).           */
    memcpy(dest->coeffs, src->coeffs, len*sizeof(*src->coeffs));

#else
/*  Else for #if TMPL_USE_MEMCPY == 1.                                        */

    /*  Otherwise use a simple for-loop to copy the data term by term.        */
    for (n = (size_t)0; n < len; ++n)
        dest->coeffs[n] = src->coeffs[n];

#endif
/*  End of #if TMPL_USE_MEMCPY == 1.                                          */

}
/*  End of tmpl_IntPolynomial_Copy.                                           */
