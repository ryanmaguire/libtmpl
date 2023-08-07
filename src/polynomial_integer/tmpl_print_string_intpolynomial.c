/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial_integer.h>
#include <stdio.h>
#include <stddef.h>

void tmpl_IntPolynomial_Print_String(FILE *fp, const tmpl_IntPolynomial *poly)
{
    size_t n;
    size_t least_term = (size_t)0;

    if (!poly)
    {
        fputs("", fp);
        return;
    }

    if (poly->error_occurred)
        return;

    if (!poly->coeffs)
    {
        fputs("", fp);
        return;
    }

    while (poly->coeffs[least_term] == 0)
    {
        if (least_term == poly->degree)
            break;

        ++least_term;
    }


    if (least_term == 0UL)
        fprintf(fp, "%d", poly->coeffs[0]);

    else if (least_term == 1UL)
    {
        if (poly->coeffs[least_term] == 1L)
            fprintf(fp, "x");
        else if (poly->coeffs[least_term] == -1L)
            fprintf(fp, "-x");
        else
            fprintf(fp, "%dx", poly->coeffs[least_term]);
    }

    for (n = least_term + 1UL; n <= poly->degree; ++n)
    {
        if (poly->coeffs[n] == 0UL)
            continue;

        if (n == 1UL)
        {
            if (poly->coeffs[n] == 1L)
                fprintf(fp, " + x");
            else if (poly->coeffs[n] == -1L)
                fprintf(fp, " - x");
            else if (poly->coeffs[n] > 0L)
                fprintf(fp, " + %dx", poly->coeffs[n]);
            else
                fprintf(fp, " - %dx", -poly->coeffs[n]);
        }
        else
        {
            if (poly->coeffs[n] == 1L)
                fprintf(fp, " + x^%u", (unsigned int)n);
            else if (poly->coeffs[n] == -1L)
                fprintf(fp, " - x^%u", (unsigned int)n);
            else if (poly->coeffs[n] > 0L)
                fprintf(fp, " + %dx^%u", poly->coeffs[n], (unsigned int)n);
            else
                fprintf(fp, " - %dx^%u", -poly->coeffs[n], (unsigned int)n);
        }
    }
}
