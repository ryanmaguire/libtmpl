
/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_stdup function declared here.                                        */
#include <libtmpl/include/tmpl_string.h>

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc and calloc are found here.                                         */
#include <stdlib.h>

#include <string.h>
#include <stdio.h>

char *tmpl_PolynomialZ_Get_String(tmpl_PolynomialZ *poly)
{
    char *str, buffer[1024];
    unsigned long int n;
    unsigned long int least_term = 0UL;

    if (poly == NULL)
        return NULL;

    if (poly->error_occurred)
        return NULL;

    if (poly->coeffs == NULL)
        return NULL;

    while (poly->coeffs[least_term] == 0UL)
    {
        if (least_term == poly->degree)
            break;

        ++least_term;
    }

    if (least_term == 0UL)
        sprintf(buffer, "%ld", poly->coeffs[least_term]);
    else if (least_term == 1UL)
    {
        if (poly->coeffs[least_term] == 1L)
            sprintf(buffer, "x");
        else if (poly->coeffs[least_term] == -1L)
            sprintf(buffer, "-x");
        else
            sprintf(buffer, "%ldx", poly->coeffs[least_term]);
    }
    else
    {
        if (poly->coeffs[least_term] == 1L)
            sprintf(buffer, "x^%ld", least_term);
        else if (poly->coeffs[least_term] == -1L)
            sprintf(buffer, "x^%ld", least_term);
        else if (poly->coeffs[least_term] > 0L)
            sprintf(buffer, "%ldx^%ld", poly->coeffs[least_term], least_term);
        else
            sprintf(buffer, "%ldx^%ld", poly->coeffs[least_term], least_term);
    }

    str = malloc(sizeof(*str) * (strlen(buffer) + 1UL));
    strcpy(str, buffer);

    for (n = least_term + 1UL; n <= poly->degree; ++n)
    {
        if (poly->coeffs[n] == 0L)
            continue;

        if (n == 1UL)
        {
            if (poly->coeffs[n] == 1L)
                sprintf(buffer, " + x");
            else if (poly->coeffs[n] == -1L)
                sprintf(buffer, " - x");
            else if (poly->coeffs[n] > 0L)
                sprintf(buffer, " + %ldx", poly->coeffs[n]);
            else
                sprintf(buffer, " - %ldx", -poly->coeffs[n]);
        }
        else
        {
            if (poly->coeffs[n] == 1L)
                sprintf(buffer, " + x^%ld", n);
            else if (poly->coeffs[n] == -1L)
                sprintf(buffer, " - x^%ld", n);
            else if (poly->coeffs[n] > 0L)
                sprintf(buffer, " + %ldx^%ld", poly->coeffs[n], n);
            else
                sprintf(buffer, " - %ldx^%ld", -poly->coeffs[n], n);
        }

        str = realloc(str, sizeof(*str) * (strlen(str) + strlen(buffer)));
        strcat(str, buffer);
    }
    return str;
}
