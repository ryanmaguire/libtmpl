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
 *                       tmpl_copy_kernel_intpolynomial                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Copies the data in one polynomial to another.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Copy_Kernel                                        *
 *  Purpose:                                                                  *
 *      Copies the coefficients of one polynomial into another.               *
 *  Arguments:                                                                *
 *      dest (tmpl_IntPolynomial *):                                          *
 *          A pointer to the "destination" polynomial. src is copied here.    *
 *      src (const tmpl_IntPolynomial *):                                     *
 *          A pointer to the "source" polynomial. This will be copied to dest.*
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          realloc:                                                          *
 *              Resizes an array.                                             *
 *      tmpl_string.h:                                                        *
 *          tmpl_String_Duplicate:                                            *
 *              Duplicates a string. Equivalent to the POSIX function strdup. *
 *      string.h (optional):                                                  *
 *          memcpy:                                                           *
 *              Copies data from one pointer to another.                      *
 *  Method:                                                                   *
 *      Two methods are provided. The simpler one uses a for-loop to copy the *
 *      coefficients from one polynomial to a another. The second method uses *
 *      memcpy to copy the data all at once. Both are nearly identical in     *
 *      regards to performance.                                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library file where realloc is provided.                  *
 *  2.) tmpl_config.h:                                                        *
 *          Header file with the TMPL_USE_MEMCPY macro.                       *
 *  3.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  4.) tmpl_string.h:                                                        *
 *          Header file where tmpl_String_Duplicate is declared.              *
 *  5.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 *  6.) string.h (optional):                                                  *
 *          Standard library file containing memcpy.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 25, 2023                                                *
 ******************************************************************************/

/*  realloc and casting with C vs. C++ compatibility provided here.           */
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/compat/tmpl_realloc.h>

/*  TMPL_USE_MEMCPY macro is here.                                            */
#include <libtmpl/include/tmpl_config.h>

/*  Booleans provided here.                                                   */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_String_Duplicate function found here.                                */
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
tmpl_IntPolynomial_Copy_Kernel(tmpl_IntPolynomial * const dest,
                               const tmpl_IntPolynomial * const src)
{
    /*  If we're not using memcpy, we need a variable to index the loop.      */
#if TMPL_USE_MEMCPY != 1
    size_t n;
#endif

    /*  We'll be copying degree + 1 elements. Set the length to this value.   */
    size_t len = src->degree + 1;

    /*  Check if we need to reallocate the memory for the dest coefficients.  */
    if (dest->degree != src->degree)
    {
        /*  Use realloc to resize the memory for the coefficients array.      */
        void * const tmp = TMPL_REALLOC(dest->coeffs, len);

        /*  Check if realloc failed.                                          */
        if (!tmp)
        {
            dest->error_occurred = tmpl_False;
            dest->error_message =
                "\nError Encountered: libtmpl\n"
                "    tmpl_IntPolynomial_Copy_Kernel\n\n"
                "Realloc failed to resize dest->coeffs.\n\n";

            return;
        }

        /*  Otherwise reset the coefficient array and degree.                 */
        dest->coeffs = TMPL_CAST(tmp, signed int *);
        dest->degree = src->degree;
    }

    /*  If the user requested memcpy, use this to copy the data.              */
#if TMPL_USE_MEMCPY == 1

    /*  memcpy syntax is (void *dest, const void *src, size_t num).           */
    memcpy(dest->coeffs, src->coeffs, len * sizeof(*src->coeffs));

#else
/*  Else for #if TMPL_USE_MEMCPY == 1.                                        */

    /*  Otherwise use a simple for-loop to copy the data term-by-term.        */
    for (n = 0; n < len; ++n)
        dest->coeffs[n] = src->coeffs[n];

#endif
/*  End of #if TMPL_USE_MEMCPY == 1.                                          */

}
/*  End of tmpl_IntPolynomial_Copy_Kernel.                                    */
