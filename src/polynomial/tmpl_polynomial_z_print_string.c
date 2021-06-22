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
 *                      tmpl_polynomial_z_print_string                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Prints the string representation of a polymomial to a file.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialZ_Print_String                                         *
 *  Purpose:                                                                  *
 *      Prints a polynomial to a file.                                        *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          A pointer to the file the polynomial will be printed to.          *
 *      P (tmpl_PolynomialZ *):                                               *
 *          A pointer to the polynomial.                                      *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      fprintf (stdio.h):                                                    *
 *          Standard library function for printing a string literal into to   *
 *          a FILE pointer.                                                   *
 *  Method:                                                                   *
 *      Parse the coefficients array and print a_nx^n for appropriate n.      *
 *  Notes:                                                                    *
 *      If the input pointer is NULL or if if its coeff pointer is NULL,      *
 *      nothing is done.                                                      *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_polynomial.h:                                                    *
 *          Header file containing the definition of polynomials and the      *
 *          functions prototype.                                              *
 *  2.) stdio.h:                                                              *
 *          C Standard library header file containing fprintf.                *
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
 *  Date:       June 21, 2021                                                 *
 ******************************************************************************/

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial.h>

/*  fprintf is found here.                                                    */
#include <stdio.h>

/*  Function for printing a polynomial to a FILE pointer.                     */
void tmpl_PolynomialZ_Print_String(FILE *fp, tmpl_PolynomialZ *poly)
{
    /*  Variable for indexing.                                                */
    unsigned long int n = 0UL;

    /*  If poly is NULL, don't print anything.                                */
    if (poly == NULL)
        return;

    /*  Similarly if the error_occurred Boolean is set to true.               */
    if (poly->error_occurred)
        return;

    /*  If the coefficients pointer is NULL, don't print anything.            */
    if (poly->coeffs == NULL)
        return;

    /*  Find the first non-zero term.                                         */
    while (poly->coeffs[n] == 0L)
    {
        if (n == poly->degree)
            break;

        ++n;
    }

    /*  If all coefficients are zero, print this and return.                  */
    if (poly->coeffs[n] == 0L)
    {
        fprintf(fp, "0");
        return;
    }

    /*  If the first non-zero coefficient is the zeroth one, print the        *
     *  coefficient by itself and don't add x^0.                              */
    if (n == 0UL)
        fprintf(fp, "%ld", poly->coeffs[0]);

    /*  If the first non-zero term is the linear one, print x and not x^1.    */
    else if (n == 1UL)
    {
        /*  If the coefficient is 1, print x instead of 1x.                   */
        if (poly->coeffs[n] == 1L)
            fprintf(fp, "x");

        /*  If the coefficient is -1, print -x instead of -1x.                */
        else if (poly->coeffs[n] == -1L)
            fprintf(fp, "-x");

        /*  Otherwise, print ax.                                              */
        else
            fprintf(fp, "%ldx", poly->coeffs[n]);
    }

    /*  Otherwise, print ax^n where n is the degree of the term.              */
    else
    {
        /*  If the coefficient is 1, print x^n instead of 1x^n.               */
        if (poly->coeffs[n] == 1L)
            fprintf(fp, "x^%ld", n);

        /*  If the coefficient is -1, print -x^n instead of -1x^n.            */
        else if (poly->coeffs[n] == -1L)
            fprintf(fp, "-x^%ld", n);

        /*  Otherwise, print ax^n.                                            */
        else
            fprintf(fp, "%ldx^%ld", poly->coeffs[n], n);
    }

    /*  Loop through the remaining coefficients and print them.               */
    for (n = n + 1UL; n <= poly->degree; ++n)
    {
        /*  If the coefficient is zero, do not print.                         */
        if (poly->coeffs[n] == 0UL)
            continue;

        /*  If the degree is 1, print ax instead of ax^1.                     */
        if (n == 1UL)
        {
            if (poly->coeffs[n] == 1L)
                fprintf(fp, " + x");
            else if (poly->coeffs[n] == -1L)
                fprintf(fp, " - x");
            else if (poly->coeffs[n] > 0L)
                fprintf(fp, " + %ldx", poly->coeffs[n]);
            else
                fprintf(fp, " - %ldx", -poly->coeffs[n]);
        }

        /*  Otherwise, print ax^n.                                            */
        else
        {
            if (poly->coeffs[n] == 1L)
                fprintf(fp, " + x^%ld", n);
            else if (poly->coeffs[n] == -1L)
                fprintf(fp, " - x^%ld", n);
            else if (poly->coeffs[n] > 0L)
                fprintf(fp, " + %ldx^%ld", poly->coeffs[n], n);
            else
                fprintf(fp, " - %ldx^%ld", -poly->coeffs[n], n);
        }
    }
    /*  End of for-loop printing polynomial coefficients.                     */
}
/*  End of tmpl_PolynomialZ_Print_String.                                     */
