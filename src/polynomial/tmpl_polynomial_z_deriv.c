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
 *                         tmpl_polynomials_z_deriv                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for computing the derivative of a polynomial in Z[x].            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialZ_Deriv                                                *
 *  Purpose:                                                                  *
 *      Computes the derivative of a polynomial in Z[x].                      *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to the polynomial.                                      *
 *      deriv (tmpl_PolynomialZ *):                                           *
 *          A pointer to the resulting derivative of poly.                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      malloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory.                  *
 *      realloc (stdlib.h):                                                   *
 *          Standard library function for re-allocating memory.               *
 *  Method:                                                                   *
 *      Sum n*a_n x^{n-1} for appropriate n.                                  *
 *  Notes:                                                                    *
 *      It is assumed none of the polynomial pointers are NULL. If they       *
 *      are, nothing is done. If malloc fails, the error_occurred Boolean is  *
 *      set to true. Similarly with realloc.                                  *
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

/*  tmpl_strdup declared here.                                                */
#include <libtmpl/include/tmpl_string.h>

/*  Function prototype is here.                                               */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc and realloc found here.                                            */
#include <stdlib.h>

/*  Function for computing the derivative of a polynomial in Z[x].            */
void tmpl_PolynomialZ_Deriv(tmpl_PolynomialZ *poly, tmpl_PolynomialZ *deriv)
{
    /*  Temporary variable in case realloc is needed.                         */
    signed long int *tmp;

    /*  Variable for indexing.                                                */
    unsigned long int n;

    /*  If poly and deriv are the same pointer, when realloc is called we     *
     *  may lose the very last element of poly->coeffs. So save this for      *
     *  later.                                                                */
    signed long int last;

    /*  If deriv is NULL, nothing can be done.                                */
    if (deriv == NULL)
        return;

    /*  Similarly, if error_occurred is set to true it may not be safe to     *
     *  proceed. Abort the computation.                                       */
    if (deriv->error_occurred)
        return;

    /*  If poly is NULL, raise an error.                                      */
    if (poly == NULL)
    {
        deriv->error_occurred = tmpl_True;
        deriv->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Deriv\n\n"
            "Input polynomial is NULL.\n"
        );
        return;
    }

    /*  Similarly if the error_occurred Boolean is true.                      */
    if (poly->error_occurred)
    {
        deriv->error_occurred = tmpl_True;
        deriv->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Deriv\n\n"
            "Input polynomial has error_occurred Boolean set to true.\n"
        );
        return;
    }

    /*  If poly->coeffs is NULL, the derivative is NULL.                      */
    if (poly->coeffs == NULL)
    {
        /*  If deriv->coeffs was already NULL, we can simply return.          */
        if (deriv->coeffs == NULL)
            return;

        /*  Otherwise we need to free the memory already allocated.           */
        else
        {
            free(deriv->coeffs);
            deriv->coeffs = NULL;
            return;
        }
    }

    /*  If poly is a zero degree polynomial, the derivative is zero.          */
    if (poly->degree == 0UL)
    {
        /*  If the coeffs pointer is NULL, allocate memory for it.            */
        if (deriv->coeffs == NULL)
        {
            deriv->degree = 0UL;
            deriv->coeffs = malloc(sizeof(*deriv->coeffs));

            /*  Check if malloc failed.                                       */
            if (deriv->coeffs == NULL)
            {
                deriv->error_occurred = tmpl_True;
                deriv->error_message = tmpl_strdup(
                    "Error Encountered: libtmpl\n"
                    "\r\ttmpl_PolynomialZ_Deriv\n\n"
                    "malloc failed to allocate memory for deriv->coeffs.\n"
                );
                return;
            }
        }

        /*  Otherwise, reallocate memory for the coeffs pointer.              */
        else if (deriv->degree != 0UL)
        {
            deriv->degree = 0UL;
            tmp = realloc(deriv->coeffs, sizeof(*deriv->coeffs));

            /*  Check if realloc failed.                                      */
            if (tmp == NULL)
            {
                deriv->error_occurred = tmpl_True;
                deriv->error_message = tmpl_strdup(
                    "Error Encountered: libtmpl\n"
                    "\r\ttmpl_PolynomialZ_Deriv\n\n"
                    "realloc failed to allocate memory for deriv->coeffs.\n"
                );
                return;
            }

            /*  If realloc was successful, set coeffs to tmp.                 */
            else
                deriv->coeffs = tmp;
        }

        /*  The derivative is zero, so simply set the coefficient to this.    */
        deriv->coeffs[0] = 0L;
    }

    /*  Otherwise, use the power rule and linearity to compute.               */
    else
    {
        /*  Set the value of last before calling realloc to avoid losing it.  */
        last = poly->coeffs[poly->degree];

        /*  If the coeffs pointer is NULL, allocate memory for it.            */
        if (deriv->coeffs == NULL)
        {
            /*  The derivative of a degree N polynomial has degree N-1.       */
            deriv->degree = poly->degree - 1UL;
            deriv->coeffs = malloc(sizeof(*deriv->coeffs)*(deriv->degree+1UL));

            /*  Check if malloc failed.                                       */
            if (deriv->coeffs == NULL)
            {
                deriv->error_occurred = tmpl_True;
                deriv->error_message = tmpl_strdup(
                    "Error Encountered: libtmpl\n"
                    "\r\ttmpl_PolynomialZ_Deriv\n\n"
                    "malloc failed to allocate memory for deriv->coeffs.\n"
                );
                return;
            }
        }

        /*  Otherwise, if deriv->degree != poly->degree - 1, resize the       *
         *  coeffs pointer with realloc.                                      */
        else if (deriv->degree != poly->degree - 1UL)
        {
            deriv->degree = poly->degree - 1UL;

            /*  Reallocate memory with realloc.                               */
            tmp = realloc(deriv->coeffs,
                          sizeof(*deriv->coeffs)*(deriv->degree+1UL));

            /*  Check if realloc failed.                                      */
            if (tmp == NULL)
            {
                deriv->error_occurred = tmpl_True;
                deriv->error_message = tmpl_strdup(
                    "Error Encountered: libtmpl\n"
                    "\r\ttmpl_PolynomialZ_Deriv\n\n"
                    "realloc failed to allocate memory for deriv->coeffs.\n"
                );
                return;
            }

            /*  If realloc was successful, set coeffs to tmp.                 */
            else
                deriv->coeffs = tmp;
        }

        /*  Loop over the coefficients and compute using the power rule.      */
        for (n = 0UL; n < deriv->degree; ++n)
            deriv->coeffs[n] = (signed long int)(n + 1UL)*poly->coeffs[n + 1UL];

        /*  Compute the last coefficient.                                     */
        deriv->coeffs[deriv->degree] = 
            (signed long int)(deriv->degree + 1UL) * last;
    }
}
/*  End of tmpl_PolynomialZ_Deriv.                                            */
