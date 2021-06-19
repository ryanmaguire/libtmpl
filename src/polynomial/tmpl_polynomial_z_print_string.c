
/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial.h>
#include <stdio.h>

void tmpl_PolynomialZ_Print_String(FILE *fp, tmpl_PolynomialZ *poly)
{
    unsigned long int n;
    unsigned long int least_term = 0UL;

    if (poly == NULL)
        return;

    if (poly->error_occurred)
        return;

    if (poly->coeffs == NULL)
        return;

    while (poly->coeffs[least_term] == 0L)
    {
        if (least_term == poly->degree)
            break;

        ++least_term;
    }


    if (least_term == 0UL)
        fprintf(fp, "%ld", poly->coeffs[0]);
    else if (least_term == 1UL)
    {
        if (poly->coeffs[least_term] == 1L)
            fprintf(fp, "x");
        else if (poly->coeffs[least_term] == -1L)
            fprintf(fp, "-x");
        else
            fprintf(fp, "%ldx", poly->coeffs[least_term]);
    }
    else
    {
        if (poly->coeffs[least_term] == 1L)
            fprintf(fp, "x^%ld", least_term);
        else if (poly->coeffs[least_term] == -1L)
            fprintf(fp, "-x^%ld", least_term);
        else if (poly->coeffs[least_term] > 0L)
            fprintf(fp, "%ldx^%ld", poly->coeffs[least_term], least_term);
        else
            fprintf(fp, "-%ldx^%ld", -poly->coeffs[least_term], least_term);
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
                fprintf(fp, " + %ldx", poly->coeffs[n]);
            else
                fprintf(fp, " - %ldx", -poly->coeffs[n]);
        }
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
}
