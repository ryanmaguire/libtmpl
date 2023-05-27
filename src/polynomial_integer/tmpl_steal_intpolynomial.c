

#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_string.h>
#include <libtmpl/include/tmpl_polynomial_integer.h>

void
tmpl_IntPolynomial_Steal(size_t cut_start, size_t cut_end,
                         tmpl_IntPolynomial *dest,
                         const tmpl_IntPolynomial *src)
{
    if (!dest)
        return;

    if (dest->error_occurred)
        return;

    if (!src)
    {
        tmpl_IntPolynomial_Make_Empty(dest);
        return;
    }

    if (src->error_occurred)
    {
        dest->error_occurred = tmpl_True;
        dest->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Steal\n\n"
            "src has error_occurred set to true. Aborting.\n\n"
        );

        return;
    }

    if (cut_start > cut_end)
    {
        const size_t tmp = cut_start;
        cut_start = cut_end;
        cut_end = tmp;
    }

    if (cut_start > src->degree)
    {
        tmpl_IntPolynomial_Make_Empty(dest);
        return;
    }

    if (cut_end > src->degree)
        cut_end = src->degree;

    dest->degree = cut_end - cut_start;
    dest->coeffs = src->coeffs + cut_start;
}
