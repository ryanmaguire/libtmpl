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
 ******************************************************************************/

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  fprintf and FILE data type found here.                                    */
#include <stdio.h>

/*  size_t typedef given here.                                                */
#include <stddef.h>

/*  Prints a polynomial to a file. No newline is appended.                    */
void tmpl_IntPolynomial_Print(FILE *fp, const tmpl_IntPolynomial *poly)
{
    const size_t zero = (size_t)0;
    const size_t one = (size_t)1;
    size_t n;
    size_t least_term = zero;

    /*  Check for a valid pointer.                                            */
    if (!poly)
        return;

    /*  Also check if the polynomial is flawed.                               */
    if (poly->error_occurred)
        return;

    /*  The empty polynomial is treated as empty. Print 0.                    */
    if (!poly->coeffs)
    {
        fprintf(fp, "0");
        return;
    }

    /*  Otherwise find the smallest non-zero coefficient.                     */
    while (poly->coeffs[least_term] == 0)
    {
        /*  Don't go beyond the bounds of the coefficients. Check this.       */
        if (least_term == poly->degree)
            break;

        ++least_term;
    }

    /*  If all coefficients are zero, print zero and return.                  */
    if (least_term == poly->degree && poly->coeffs[least_term] == 0)
    {
        fprintf(fp, "0");
        return;
    }

    /*  If the least term is degree 0, print a instead of ax^0.               */
    if (least_term == zero)
    {
        fprintf(fp, "%d", poly->coeffs[0]);

        /*  If the polynomial is a constant, we can exit the function.        */
        if (poly->degree == zero)
            return;

        /*  Otherwise print the degree 1 term as well.                        */
        least_term++;

        /*  Only need to print this if the coefficient is non-zero.           */
        if (poly->coeffs[one] != 0)
        {
            /*  Don't print a coefficient of 1. Just print "x".               */
            if (poly->coeffs[one] == 1)
                fprintf(fp, " + x");

            /*  Similarly for negative 1, just print "-x".                    */
            else if (poly->coeffs[one] == -1)
                fprintf(fp, " - x");

            /*  For positive coefficients print "+ ax".                       */
            else if (poly->coeffs[one] > 0)
                fprintf(fp, " + %dx", poly->coeffs[one]);

            /*  And for negative print "- abs(a)x".                           */
            else
                fprintf(fp, " - %dx", -poly->coeffs[one]);
        }

        /*  If the polynomial is degree 1, we can exit the function.          */
        if (poly->degree == one)
            return;
    }

    /*  Similarly if the least term is 1, print ax instead of ax^1.           */
    else if (least_term == one)
    {
        /*  No coefficient needs to be printed if the value is "1".           */
        if (poly->coeffs[one] == 1)
            fprintf(fp, "x");

        /*  For minus 1, just print the negative symbol.                      */
        else if (poly->coeffs[one] == -1)
            fprintf(fp, "-x");

        /*  For all other values print the coefficient.                       */
        else
            fprintf(fp, "%dx", poly->coeffs[one]);
    }

    /*  Lastly, print ax^n for the first non-zero term.                       */
    else
    {
        /*  No coefficient needs to be printed if the value is "1".           */
        if (poly->coeffs[least_term] == 1)
            fprintf(fp, "x^%u", (unsigned int)least_term);

        /*  For minus 1, just print the negative symbol.                      */
        else if (poly->coeffs[least_term] == -1)
            fprintf(fp, "-x^%u", (unsigned int)least_term);

        /*  For all other values print the coefficient.                       */
        else
            fprintf(fp, "%dx^%u",
                    poly->coeffs[least_term], (unsigned int)least_term);
    }

    /*  Loop over all other terms of the polynomial.                          */
    for (n = least_term + one; n <= poly->degree; ++n)
    {
        if (poly->coeffs[n] == 0)
            continue;

        if (poly->coeffs[n] == 1)
            fprintf(fp, " + x^%u", (unsigned int)n);

        else if (poly->coeffs[n] == -1)
            fprintf(fp, " - x^%u", (unsigned int)n);

        else if (poly->coeffs[n] > 0)
            fprintf(fp, " + %dx^%u", poly->coeffs[n], (unsigned int)n);

        else
            fprintf(fp, " - %dx^%u", -poly->coeffs[n], (unsigned int)n);
    }
}
/*  End of tmpl_IntPolynomial_Print.                                          */
