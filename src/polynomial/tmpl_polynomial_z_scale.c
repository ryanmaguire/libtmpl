/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                          tmpl_polynomials_z_add                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for adding two elements of Z[x].                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialZ_Add                                                  *
 *  Purpose:                                                                  *
 *      Add two polynomials in Z[x].                                          *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to the first polynomial.                                *
 *      scale (signed long int):                                              *
 *          An integer.                                                       *
 *      prod (tmpl_PolynomialZ *):                                            *
 *          A pointer to the resulting product of poly and scale.             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      malloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory.                  *
 *      realloc (stdlib.h):                                                   *
 *          Standard library function for re-allocating memory.               *
 *  Method:                                                                   *
 *      Multiply the coefficients term by term.                               *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) tmpl_string.h:                                                        *
 *          Header file where tmpl_strdup is declared. This is a clone of     *
 *          strdup function, which is a part of the POSIX C standard, but not *
 *          part of the C standard library.                                   *
 *  2.) tmpl_polynomial.h:                                                    *
 *          Header file containing the definition of polynomials and the      *
 *          functions prototype.                                              *
 *  3.) stdlib.h:                                                             *
 *          C Standard library header file containing malloc and realloc.     *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       June 22, 2021                                                 *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_stdup function declared here.                                        */
#include <libtmpl/include/tmpl_string.h>

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc and realloc are found here.                                        */
#include <stdlib.h>

/*  Function for multiplying a polynomial in Z[x] by an integer.              */
void
tmpl_PolynomialZ_Scale(tmpl_PolynomialZ *poly,
                       signed long int scale,
                       tmpl_PolynomialZ *prod)
{
    /*  Declare a variable for indexing.                                      */
    unsigned long int n;

    /*  Temporary variable used in case realloc is needed.                    */
    signed long int *tmp;

    /*  If prod is NULL, nothing can be done.                                 */
    if (prod == NULL)
        return;

    /*  Similarly if the prod pointer has error_occurred set to true, abort.  */
    if (prod->error_occurred)
        return;

    /*  If poly is NULL, nothing can be done. Store an error                  *
     *  message in sum.                                                       */
    if (poly == NULL)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Scale\n\n"
            "Input polynomial is NULL. Aborting.\n"
        );
        return;
    }

    /*  If poly has a NULL coeffs pointer, nothing can be done.               */
    if (poly->coeffs == NULL)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Scale\n\n"
            "The input has a NULL coeffs pointer. Aborting.\n"
        );
        return;
    }

    /*  Lastly, if one of the inputs has error_occurred set to true it may    *
     *  not be safe to proceed. Check for this.                               */
    if (poly->error_occurred)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Scale\n\n"
            "The input has its error_occurred Boolean set to true.\n"
        );
        return;   
    }

    /*  If the prod coeffs pointer is NULL, allocate memory for it.           */
    if (prod->coeffs == NULL)
    {
        prod->degree = poly->degree;
        prod->coeffs = malloc(sizeof(*prod->coeffs) * (prod->degree + 1UL));

        /*  Check if malloc failed.                                           */
        if (prod->coeffs == NULL)
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Scale\n\n"
                "malloc failed to allocate memory for prod->coeffs.\n"
            );
            return;  
        }
    }

    /*  If prod does not have the correct size for it's degree, reallocate    *
     *  the coeffs pointer to be the max of the two others.                   */
    else if (prod->degree != poly->degree)
    {
        prod->degree = poly->degree;
        tmp = realloc(prod->coeffs, sizeof(*prod->coeffs)*(prod->degree + 1UL));

        /*  Check if realloc failed.                                          */
        if (tmp == NULL)
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Scale\n\n"
                "realloc failed to allocate memory for prod->coeffs.\n"
            );
            return;
        }

        /*  If realloc did not fail, have the coeffs pointer set to tmp.      */
        else
            prod->coeffs = tmp;
    }

    /*  For zero up to the degree of the smaller polynomial, polynomial       *
     *  addition is done component-wise.                                      */
    for (n = 0UL; n <= prod->degree; ++n)
        prod->coeffs[n] = scale * poly->coeffs[n];

    return;
}
/*  End of tmpl_PolynomialZ_Add.                                              */
