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
 *                        tmpl_polynomial_z_get_string                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Gets the string representation of a polymomial.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialZ_Get_String                                           *
 *  Purpose:                                                                  *
 *      Gets the representation of a polynomial as a string.                  *
 *  Arguments:                                                                *
 *      P (tmpl_PolynomialZ *):                                               *
 *          A pointer to the polynomial.                                      *
 *  Output:                                                                   *
 *      str (char *):                                                         *
 *          The string representing the input polynomial.                     *
 *  Called Functions:                                                         *
 *      malloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory.                  *
 *      realloc (stdlib.h):                                                   *
 *          Standard library function for re-allocating memory.               *
 *      free (stdlib.h):                                                      *
 *          Standard library function for freeing memory allocated with       *
 *          malloc, calloc, and realloc.                                      *
 *      strcpy (string.h):                                                    *
 *          Standard library function for copying the contents of one string  *
 *          into another.                                                     *
 *      strcat (string.h):                                                    *
 *          Standard library function for concatenating two strings.          *
 *      sprintf (stdio.h):                                                    *
 *          Standard library function for printing a string literal into a    *
 *          char array.                                                       *
 *  Method:                                                                   *
 *      Parse the coefficients array and append a_nx^n for appropriate n.     *
 *  Notes:                                                                    *
 *      If the input pointer is NULL, if its coeff pointer is NULL, or if     *
 *      malloc or realloc fail, this function returns NULL.                   *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_polynomial.h:                                                    *
 *          Header file containing the definition of polynomials and the      *
 *          functions prototype.                                              *
 *  2.) stdlib.h:                                                             *
 *          C Standard library header file containing malloc and realloc.     *
 *  3.) string.h:                                                             *
 *          C Standard library header file containing strcpy and strcat.      *
 *  4.) stdio.h:                                                              *
 *          C Standard library header file containing sprintf.                *
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

/*  malloc and realloc are found here.                                        */
#include <stdlib.h>

/*  strcat and strcpy are here.                                               */
#include <string.h>

/*  And lastly, sprintf is found here.                                        */
#include <stdio.h>

/*  Function for getting the string representation of a polynomial.           */
char *tmpl_PolynomialZ_Get_String(tmpl_PolynomialZ *poly)
{
    /*  char pointer for the output.                                          */
    char *str;

    /*  Temporary pointer for checking if functions fail.                     */
    char *tmp;

    /*  char array that will be used as a buffer for adding on to the string. *
     *  The largest string possible for 64-bit coefficients and 64-bit        *
     *  degrees is 19 + 19 + 3 + 2 + 1 = 44. 19 is the number of digits in    *
     *  the largest 64 bit number, 3 is for " + " or " - ", 2 is for "x^",    *
     *  and the 1 is for the null terminator. If you have larger than 64-bit  *
     *  integers, and somehow have enough memory to store a polynomial with   *
     *  more than 2^64 coefficients, change this value.                       */
    char buffer[48];

    /*  Integer for testing if sprintf succeeds.                              */
    int success;

    /*  Variable for indexing.                                                */
    unsigned long int n = 0UL;

    /*  If poly is NULL, the string should be empty. Return NULL.             */
    if (poly == NULL)
        return NULL;

    /*  If the error_occurred Boolean is true, it may not be safe to parse    *
     *  the contents of poly. Return NULL.                                    */
    if (poly->error_occurred)
        return NULL;

    /*  If the coefficients pointer is also NULL, the string should be empty. *
     *  Return NULL in this case as well.                                     */
    if (poly->coeffs == NULL)
        return NULL;

    /*  Loop through the coefficients array and find the first non-zero term. */
    while (poly->coeffs[n] == 0UL)
    {
        if (n == poly->degree)
            break;

        ++n;
    }

    /*  If all terms are zero, simply return zero.                            */
    if (poly->coeffs[n] == 0L)
    {
        /*  Allocate memory for "0" and the null terminator.                  */
        str = malloc(sizeof(*str) * 2);

        /*  Check if malloc failed.                                           */
        if (str == NULL)
            return NULL;

        /*  Otherwise, copy "0" into the string and return.                   */
        strcpy(str, "0");
        return str;
    }

    /*  If the first term is the zeroth term, the string does not have x^0    *
     *  at the end, we simply write out the constant term.                    */
    if (n == 0UL)
        success = sprintf(buffer, "%ld", poly->coeffs[n]);

    /*  If the first non-zero term is the linear factor, write x, not x^1.    */
    else if (n == 1UL)
    {
        /*  If the coefficient is 1, write x instead of 1x.                   */
        if (poly->coeffs[n] == 1L)
            success = sprintf(buffer, "x");

        /*  If the coefficient is -1, write -x instead of -1x.                */
        else if (poly->coeffs[n] == -1L)
            success = sprintf(buffer, "-x");

        /*  For all other coefficients, write ax.                             */
        else
            success = sprintf(buffer, "%ldx", poly->coeffs[n]);
    }

    /*  If the first non-zero term has degree greater than 1, write ax^n      *
     *  where a is the coefficients and n is the degree.                      */
    else
    {
        /*  If the coefficient is 1, write x^n instead of 1x^n.               */
        if (poly->coeffs[n] == 1L)
            success = sprintf(buffer, "x^%lu", n);

        /*  If the coefficient is -1, write -x^n instead of -1x^n.            */
        else if (poly->coeffs[n] == -1L)
            success = sprintf(buffer, "-x^%lu", n);

        /*  Otherwise, write ax^n.                                            */
        else
            success = sprintf(buffer, "%ldx^%lu", poly->coeffs[n], n);
    }

    /*  Check if sprintf failed.                                              */
    if (success < 0)
        return NULL;

    /*  If sprintf was successful, allocate memory for the output string.     */
    str = malloc(sizeof(*str) * (strlen(buffer) + 1UL));

    /*  Check if malloc failed.                                               */
    if (str == NULL)
        return NULL;

    /*  Copy the contents of the buffer into the string.                      */
    strcpy(str, buffer);

    /*  Loop through the rest of the coefficients.                            */
    for (n = n + 1UL; n <= poly->degree; ++n)
    {
        /*  Do not print out coefficients that are zero.                      */
        if (poly->coeffs[n] == 0L)
            continue;

        /*  In the case that the degree is one, print ax instead of ax^1.     */
        if (n == 1UL)
        {
            if (poly->coeffs[n] == 1L)
                success = sprintf(buffer, " + x");
            else if (poly->coeffs[n] == -1L)
                success = sprintf(buffer, " - x");
            else if (poly->coeffs[n] > 0L)
                success = sprintf(buffer, " + %ldx", poly->coeffs[n]);
            else
                success = sprintf(buffer, " - %ldx", -poly->coeffs[n]);
        }

        /*  Otherwise, print ax^n.                                            */
        else
        {
            if (poly->coeffs[n] == 1L)
                success = sprintf(buffer, " + x^%ld", n);
            else if (poly->coeffs[n] == -1L)
                success = sprintf(buffer, " - x^%ld", n);
            else if (poly->coeffs[n] > 0L)
                success = sprintf(buffer, " + %ldx^%ld", poly->coeffs[n], n);
            else
                success = sprintf(buffer, " - %ldx^%ld", -poly->coeffs[n], n);
        }

        /*  Check if sprintf failed.                                          */
        if (success < 0)
        {
            /*  free the memory allocated to str and return NULL.             */
            free(str);
            return NULL;
        }

        /*  Otherwise, increase the size of memory allocated to str so we     *
         *  can append the new part of the string to it.                      */
        tmp = realloc(str, sizeof(*str) * (strlen(str) + strlen(buffer) + 1UL));

        /*  Check if realloc failed.                                          */
        if (tmp == NULL)
        {
            /*  Free the memory allocated to str and return NULL.             */
            free(str);
            return NULL;
        }

        /*  If realloc was successful, have str point to tmp.                 */
        str = tmp;

        /*  Append the new part of the string on to str.                      */
        strcat(str, buffer);
    }

    return str;
}
/*  End of tmpl_PolynomialZ_Get_String.                                       */
